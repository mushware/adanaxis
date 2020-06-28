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
//%Header } P60lrmte+2X1+ZfzbY12zQ


#include "MediaThreadPool.h"

#include "MediaJob.h"

#include "MediaSDL.h"
#include "MediaSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MediaThreadPool);

MediaThreadPool::MediaThreadPool()
{
    if (MushcoreSingleton<MediaThreadPool>::SingletonExists())
    {
        throw(MushcoreLogicFail("Attempt to create a second MediaThreadPool object"));
    }
    m_numThreads = std::min(32, std::max(1, SDL_GetCPUCount() - 1));

    MushcoreLog::Sgl().InfoLog() << "Creating " << m_numThreads << " worker threads" << std::endl;
    SDL_AtomicSet(&m_done, 0);
    m_pJobAvailSem = SDL_CreateSemaphore(0);
    m_pInputQueueMutex = SDL_CreateMutex();
    m_pOutputQueueMutex = SDL_CreateMutex();

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
        SDL_SemPost(m_pJobAvailSem);
    }

    for (U32 i = 0; i < m_threads.size(); ++i) {
        SDL_WaitThread(m_threads[i], NULL);
    }
#ifdef MUSHCORE_DEBUG
    MushcoreLog::Sgl().InfoLog() << "Thread pool exited cleanly" << std::endl;
#endif
}


void MediaThreadPool::InputQueueGive(std::auto_ptr<MediaJob> apJob)
{
    MediaJob *pJob = apJob.release();
    InputQueueGive(&pJob);
}


void MediaThreadPool::InputQueueGive(MediaJob **pJob)
{
    SDL_LockMutex(m_pInputQueueMutex);
    m_inputQueue.push_back(*pJob);
    SDL_UnlockMutex(m_pInputQueueMutex);
    SDL_SemPost(m_pJobAvailSem);
    *pJob = NULL;
}


bool MediaThreadPool::InputQueueTake(MediaJob **pJob)
{
    SDL_LockMutex(m_pInputQueueMutex);
    bool isNotEmpty = !m_inputQueue.empty();
    if (isNotEmpty) {
        *pJob = m_inputQueue.front();
        m_inputQueue.pop_front();
    }
    SDL_UnlockMutex(m_pInputQueueMutex);
    return isNotEmpty;
}


void MediaThreadPool::OutputQueueGive(MediaJob **pJob)
{
    SDL_LockMutex(m_pOutputQueueMutex);
    m_outputQueue.push_back(*pJob);
    SDL_UnlockMutex(m_pOutputQueueMutex);
    *pJob = NULL;
}


bool MediaThreadPool::OutputQueueTake(MediaJob **pJob)
{
    SDL_LockMutex(m_pOutputQueueMutex);
    bool isNotEmpty = !m_outputQueue.empty();
    if (isNotEmpty) {
        *pJob = m_outputQueue.front();
        m_outputQueue.pop_front();
    }
    SDL_UnlockMutex(m_pOutputQueueMutex);
    return isNotEmpty;
}


// Call this somewhere in the main thread loop to handle job completions
void MediaThreadPool::MainThreadPump()
{
    MediaJob *pJob;
    while (OutputQueueTake(&pJob)) {
        if (pJob->Error() != "") {
            MushcoreLog::Sgl().ErrorLog() << "Job " << pJob->Name() << " failed: " << pJob->Error() << std::endl;
            delete pJob;
        } else {
            Mushware::tVal duration = static_cast<Mushware::tVal>(pJob->EndTime() - pJob->StartTime()) / SDL_GetPerformanceFrequency();

            std::ostringstream durationStream;
            durationStream << setprecision(3) << fixed << duration << " s";
            MushcoreLog::Sgl().InfoLog() << "Finished job " << pJob->Name() << " in " << durationStream.str() << std::endl;
            bool reQueue = pJob->MainThreadPostRun();
            if (reQueue) {
                InputQueueGive(&pJob);
            } else {

                delete pJob;
            }
        }
    }
}


int MediaThreadPool::ThreadHandler(void *data) {
    MediaThreadPool* pObj = reinterpret_cast<MediaThreadPool*>(data);

    for (;;) {
        int retVal = SDL_SemWait(pObj->m_pJobAvailSem);
        if (retVal != 0) {
            MushcoreLog::Sgl().ErrorLog() << "Wait for semaphore failed, thread must exit" << std::endl;
            return 0;
        }
        if (SDL_AtomicGet(&pObj->m_done)) {
            return 0;
        }
        MediaJob *pJob;
        if (pObj->InputQueueTake(&pJob)) {
            pJob->StartTimeSet(SDL_GetPerformanceCounter());

#ifdef MUSHCORE_DEBUG
            MushcoreLog::Sgl().InfoLog() << "Starting job " << pJob->Name() << std::endl;
#endif
            try {
                pJob->Run();
                pJob->EndTimeSet(SDL_GetPerformanceCounter());
            }
            catch (std::exception& e) {
                pJob->ErrorSet(e.what());
            }
            pObj->OutputQueueGive(&pJob);
        }
    }
}
