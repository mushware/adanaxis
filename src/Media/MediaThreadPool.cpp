//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaThreadPool.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } pKjj4ZwHY8r5afsBWiCDlA


#include "MediaThreadPool.h"

#include "MediaJob.h"
#include "MediaLock.h"

#include "MediaSDL.h"
#include "MediaSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MediaThreadPool);

MediaThreadPool::MediaThreadPool() :
    m_nextJobId(1),
    m_pJobAvailSem(SDL_CreateSemaphore(0)),
    m_pStateMutex(SDL_CreateMutex()),
    m_stateHasChanged(true)
{
    if (MushcoreSingleton<MediaThreadPool>::SingletonExists())
    {
        throw(MushcoreLogicFail("Attempt to create a second MediaThreadPool object"));
    }
    m_numThreads = std::min(32, std::max(1, SDL_GetCPUCount() - 1));

    MushcoreLog::Sgl().InfoLog() << "Creating " << m_numThreads << " worker threads" << std::endl;
    SDL_AtomicSet(&m_done, 0);

    for (U32 i = 0; i < m_numThreads; ++i) {
        std::ostringstream threadName;
        threadName << "Thread " << i;
        m_threads.push_back(SDL_CreateThread(MediaThreadPool::ThreadHandler, threadName.str().c_str(), this));
    }
}


MediaThreadPool::~MediaThreadPool()
{
    SDL_AtomicSet(&m_done, 1);
    for (U32 i = 0; i < m_threads.size(); ++i) {
        // Wake all threads so they can handle the change in m_done and exit
        SDL_SemPost(m_pJobAvailSem);
    }

    for (U32 i = 0; i < m_threads.size(); ++i) {
        SDL_WaitThread(m_threads[i], NULL);
    }
}


MediaJobId
MediaThreadPool::JobIdTake()
{
    // This is called by the MediaJobs themselves to take the next ID
    MediaLock lock(m_pStateMutex);
    return m_nextJobId++;
}


void
MediaThreadPool::WaitMapGive(std::auto_ptr<MediaJob> apJob)
{
    MediaJob *pJob = apJob.release();
    return WaitMapGive(&pJob);
}


void
MediaThreadPool::WaitMapGive(MediaJob **ppJob)
{
    // This is the usual interface for clients queueing jobs.  Jobs go into the
    // wait map so the ticker can check whether any of their dependent jobs
    // still need to complete, before queueing up the new job.

    // Call PrerequisitesCreate first as it can add dependency jobs
    (*ppJob)->PrerequisitesCreate();

    MediaLock lock(m_pStateMutex);
    m_jobMap[(*ppJob)->JobId()] = *ppJob;
    (*ppJob)->JobStateSet(MediaJob::kJobStateWaiting);
    *ppJob = NULL;
    m_stateHasChanged = true;
}


void
MediaThreadPool::InputQueueGive(std::auto_ptr<MediaJob> apJob)
{
    MediaJob *pJob = apJob.release();
    InputQueueGive(&pJob);
}


void
MediaThreadPool::InputQueueGive(MediaJob **ppJob)
{
    // This will queue a job without checking jobs it depends on, and will
    // start the job without waiting for the next tick if a thread is
    // available.

    MediaLock lock(m_pStateMutex);
    m_inputQueue.push_back(*ppJob);
    (*ppJob)->JobStateSet(MediaJob::kJobStateQueued);
    SDL_SemPost(m_pJobAvailSem);
    *ppJob = NULL;
}


bool
MediaThreadPool::InputQueueTake(MediaJob **pJob)
{
    // Internal method to take jobs off the input queue when they're being
    // given to a thread.

    MediaLock lock(m_pStateMutex);
    bool isNotEmpty = !m_inputQueue.empty();
    if (isNotEmpty) {
        *pJob = m_inputQueue.front();
        m_inputQueue.pop_front();
    }
    return isNotEmpty;
}


void MediaThreadPool::OutputQueueGive(MediaJob **pJob)
{
    // Called by a worker thread and for internal use, puts a job onto the
    // output queue.  The ticker will pick it up on the main thread and take
    // the next steps.

    MediaLock lock(m_pStateMutex);
    m_outputQueue.push_back(*pJob);
    *pJob = NULL;
}


bool MediaThreadPool::OutputQueueTake(MediaJob **pJob)
{
    // Called by the ticker on the main thread to take a job off the output queue.

    MediaLock lock(m_pStateMutex);
    bool isNotEmpty = !m_outputQueue.empty();
    if (isNotEmpty) {
        *pJob = m_outputQueue.front();
        m_outputQueue.pop_front();
    }
    return isNotEmpty;
}


// JobDelete must run on the main thrread only
void MediaThreadPool::JobDelete(MediaJobId jobId)
{
    // Deletes a job from our records, with a few checks to confirm it's still OK.

    MediaLock lock(m_pStateMutex);
    auto jobIter = m_jobMap.find(jobId);
    if (jobIter == m_jobMap.end()) {
        ostringstream messageStream;
        messageStream << "Cannot find job to delete (id=" << jobId << "), suggests double delete";
        throw MushcoreLogicFail(messageStream.str());
    }

    if (jobIter->second->JobMagic() != MediaJob::kJobMagic) {
        ostringstream messageStream;
        messageStream << "Bad value for JobMagic (" << jobIter->second->JobMagic() << "m job ID " << jobId << "), suggests double delete";
        throw MushcoreLogicFail(messageStream.str());
    }
    jobIter->second->JobMagicSet(jobId);
    delete jobIter->second;
    m_jobMap.erase(jobId);
}


// JobStart must run on the main thread only
void MediaThreadPool::JobStart(MediaJobId jobId)
{
    // Used internally, and starts a job from the wait map
    MediaJob *pJob = NULL;
    {
        MediaLock lock(m_pStateMutex);
        auto jobIter = m_jobMap.find(jobId);
        if (jobIter == m_jobMap.end()) {
            ostringstream messageStream;
            messageStream << "Cannot find job to start (id=" << jobId << ")";
            throw MushcoreLogicFail(messageStream.str());
        }

        pJob = jobIter->second;
    }

    pJob->MainThreadPreRun();
    // m_pStateMutex is released here because InputQueueGive needs to take it
    InputQueueGive(&pJob);
}


// Call this somewhere in the main thread loop to handle job completions and starts
void MediaThreadPool::MainThreadPump()
{
    // Handle stuff we need to do on the main thread

    MediaJob *pJob;

    bool stateHasChanged = true;
    // Handle job completions first
    while (OutputQueueTake(&pJob)) {
        stateHasChanged = true;
        if (pJob->Error() != "") {
            MushcoreLog::Sgl().ErrorLog() << "Job " << pJob->Name() << " failed: " << pJob->Error() << std::endl;
            pJob->JobStateSet(MediaJob::kJobStateErrored);
        }
        else {
            Mushware::tVal duration = static_cast<Mushware::tVal>(pJob->EndTime() - pJob->StartTime()) / SDL_GetPerformanceFrequency();

            std::ostringstream durationStream;
            durationStream << setprecision(3) << fixed << duration << " s";
            MushcoreLog::Sgl().InfoLog() << "Finished job " << pJob->Name() << " in " << durationStream.str() << std::endl;
            pJob->MainThreadPostRun();
            if (pJob->JobState() == MediaJob::kJobStateRunning) {
                MushcoreLog::Sgl().ErrorLog() << "Job " << pJob->Name() << " failed to set state on exit, aborting" << std::endl;
                pJob->JobStateSet(MediaJob::kJobStateAbort);
            }
        }
    }

    {
        MediaLock lock(m_pStateMutex);
        stateHasChanged = stateHasChanged || m_stateHasChanged;
        m_stateHasChanged = false;
    }
    if (stateHasChanged) {
        HandleStateChange();
    }
}


void
MediaThreadPool::HandleStateChange()
{
    // Only this method can delete jobs, so any pointers (jobIter is a pointer)
    // we take are safe and will persist unless we delete the jobs they're pointing to

    // Check whether those job completions allow any other jobs to start
    std::vector<std::map<MediaJobId, MediaJob *>::iterator> jobsToTestStartable;
    std::vector<MediaJobId> jobIdsToDelete;
    {
        MediaLock lock(m_pStateMutex);

        // We're holding the mutex so don't do anything complex in here
        for (auto jobIter = m_jobMap.begin(); jobIter != m_jobMap.end(); ++jobIter) {
            switch (jobIter->second->JobState()) {
            case MediaJob::kJobStateWaiting:
                jobsToTestStartable.push_back(jobIter);
                break;

            case MediaJob::kJobStateAbort:
            case MediaJob::kJobStateDone:
            case MediaJob::kJobStateErrored:
                jobIdsToDelete.push_back(jobIter->first);
                break;

            default:
                break;
            }
        }
    }

    for (auto jobIter = jobIdsToDelete.begin(); jobIter != jobIdsToDelete.end(); ++jobIter) {
        // Delete first so that jobs waiting for other jobs can start.  Logic above needs
        // to ensure that jobs are not on both lists
        JobDelete(*jobIter);
    }

    for (auto jobIter = jobsToTestStartable.begin(); jobIter != jobsToTestStartable.end(); ++jobIter) {

        bool canStart = true;
        const std::vector<MediaJobId> jobIdsToWaitFor = (*jobIter)->second->JobIdsToWaitFor();

        {
            MediaLock lock(m_pStateMutex);
            for (U32 i = 0; i < jobIdsToWaitFor.size() && canStart; ++i) {
                auto jobIter = m_jobMap.find(jobIdsToWaitFor[i]);
                if (jobIter != m_jobMap.end()) {
                    switch (jobIter->second->JobState()) {

                    case MediaJob::kJobStateDone:
                        // Done is fine so carry on
                        break;

                    case MediaJob::kJobStateAbort:
                    case MediaJob::kJobStateErrored:
                        MushcoreLog::Sgl().ErrorLog() << "Abandoning job " << jobIter->second->Name() << " because dependency job failed (" << jobIter->second->JobState() << ")" << std::endl;
                        jobIter->second->JobStateSet(MediaJob::kJobStateAbort);
                        break;

                    default:
                        canStart = false;
                    }
                }
            }
        }

        if (canStart && (*jobIter)->second->JobCanStart()) {
            if (jobIdsToWaitFor.size() > 0) {
                MushcoreLog::Sgl().InfoLog() << "Job " << (*jobIter)->second->Name() << " now released because dependency jobs are complete" << std::endl;
            }
            JobStart((*jobIter)->first);
        }
    }
}


int MediaThreadPool::ThreadHandler(void *data) {
    // Code running on the worker threads.  It calls the job's Run method
    // to do the actual work of the thread

    MediaThreadPool* pObj = reinterpret_cast<MediaThreadPool*>(data);

    for (;;) {
        // This semaphore is how jobs wake up when a job is available on the input queue.
        // Otherwise they just block here.
        int retVal = SDL_SemWait(pObj->m_pJobAvailSem);
        if (retVal != 0) {
            MushcoreLog::Sgl().ErrorLog() << "Wait for semaphore failed, thread must exit" << std::endl;
            return 0;
        }
        if (SDL_AtomicGet(&pObj->m_done)) {
            // m_done means the application is quitting so threads should exit
            return 0;
        }
        MediaJob *pJob;
        if (pObj->InputQueueTake(&pJob)) {
            // Now we own the job
            pJob->StartTimeSet(SDL_GetPerformanceCounter());

#ifdef MUSHCORE_DEBUG
            MushcoreLog::Sgl().InfoLog() << "Starting job " << pJob->Name() << std::endl;
#endif
            try {
                pJob->Run();
                pJob->EndTimeSet(SDL_GetPerformanceCounter());
            }
            catch (std::exception& e) {
                // We communicate failures back to the main thread by setting the Error value
                // in the job itself.  The main thread will check it and take action
                pJob->ErrorSet(e.what());
            }
            // Relinquish the job.  It'll be picked up on the main thread
            pObj->OutputQueueGive(&pJob);
        }
    }
}
