//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaJob.cpp
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
//%Header } f2YkyJoaZHUq51md0qBN/g

#include "MediaJob.h"

#include "MediaLock.h"
#include "MediaThreadPool.h"


MediaJob::MediaJob() :
    m_jobMagic(kJobMagic),
    m_jobId(MediaThreadPool::Sgl().JobIdTake()),
    m_pStateMutex(SDL_CreateMutex()),
    m_jobState(kJobStateNew)
{
}


MediaJob::MediaJob(std::string& name) :
    m_jobMagic(kJobMagic),
    m_jobId(MediaThreadPool::Sgl().JobIdTake()),
    m_pStateMutex(SDL_CreateMutex()),
    m_jobState(kJobStateNew),
    m_name(name)
{}


MediaJob::~MediaJob()
{}


MediaJob::tJobState
MediaJob::JobState() const
{
    MediaLock lock(m_pStateMutex);
    return static_cast<tJobState>(m_jobState);
}


void
MediaJob::JobStateSet(tJobState inValue)
{
    MediaLock lock(m_pStateMutex);
    m_jobState = inValue;
}


const std::vector<MediaJobId>
MediaJob::JobIdsToWaitFor() const
{
    // Return a copy, and make it const to discourage callers from adding to it
    // which would have no effect
    MediaLock lock(m_pStateMutex);
    return m_JobIdsToWaitFor;
}


void
MediaJob::JobIdToWaitForAdd(MediaJobId jobId)
{
    MediaLock lock(m_pStateMutex);
    m_JobIdsToWaitFor.push_back(jobId);
}


void
MediaJob::JobIdToWaitForAdd(std::vector<MediaJobId>& jobIds)
{
    MediaLock lock(m_pStateMutex);
    m_JobIdsToWaitFor.insert(m_JobIdsToWaitFor.end(), jobIds.begin(), jobIds.end());
}


bool
MediaJob::JobCanStart() const
{
    // Additonal check a to whether the job can start.  MediaThreadPool will
    // apply the JobIdsToWaitFor constraint in addition to this
    return true;
}


void
MediaJob::PrerequisitesCreate()
{
}


void
MediaJob::MainThreadPreRun()
{
}


void
MediaJob::Run()
{
    MushcoreLog::Sgl().ErrorLog() << "Run method for job " << m_name << " not overriden" << std::endl;
    JobStateSet(kJobStateAbort);
}


void
MediaJob::MainThreadPostRun()
{
}


void MediaJob::RunToCompletionNow()
{
    JobStateSet(kJobStateRunning);
    MainThreadPreRun();

    Mushware::U32 count = 0;
    while (JobState() == kJobStateRunning) {
        Run();
        MainThreadPostRun();
        ++count;
        if (count > 10000) {
            throw MushcoreLogicFail("Overrun in processing job " + m_name);
        }
    }
}


//%outOfLineFunctions {

const char *MediaJob::AutoName(void) const
{
    return "MediaJob";
}

MushcoreVirtualObject *MediaJob::AutoClone(void) const
{
    return new MediaJob(*this);
}

MushcoreVirtualObject *MediaJob::AutoCreate(void) const
{
    return new MediaJob;
}

MushcoreVirtualObject *MediaJob::AutoVirtualFactory(void)
{
    return new MediaJob;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MediaJob", MediaJob::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MediaJob::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "jobMagic=" << m_jobMagic << ", ";
    ioOut << "jobId=" << m_jobId << ", ";
    ioOut << "JobIdsToWaitFor=" << m_JobIdsToWaitFor << ", ";
    ioOut << "jobState=" << m_jobState << ", ";
    ioOut << "name=" << m_name << ", ";
    ioOut << "error=" << m_error << ", ";
    ioOut << "startTime=" << m_startTime << ", ";
    ioOut << "endTime=" << m_endTime;
    ioOut << "]";
}
bool
MediaJob::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "jobMagic")
    {
        ioIn >> m_jobMagic;
    }
    else if (inTagStr == "jobId")
    {
        ioIn >> m_jobId;
    }
    else if (inTagStr == "JobIdsToWaitFor")
    {
        ioIn >> m_JobIdsToWaitFor;
    }
    else if (inTagStr == "jobState")
    {
        ioIn >> m_jobState;
    }
    else if (inTagStr == "name")
    {
        ioIn >> m_name;
    }
    else if (inTagStr == "error")
    {
        ioIn >> m_error;
    }
    else if (inTagStr == "startTime")
    {
        ioIn >> m_startTime;
    }
    else if (inTagStr == "endTime")
    {
        ioIn >> m_endTime;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MediaJob::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("jobMagic");
    ioOut << m_jobMagic;
    ioOut.TagSet("jobId");
    ioOut << m_jobId;
    ioOut.TagSet("JobIdsToWaitFor");
    ioOut << m_JobIdsToWaitFor;
    ioOut.TagSet("jobState");
    ioOut << m_jobState;
    ioOut.TagSet("name");
    ioOut << m_name;
    ioOut.TagSet("error");
    ioOut << m_error;
    ioOut.TagSet("startTime");
    ioOut << m_startTime;
    ioOut.TagSet("endTime");
    ioOut << m_endTime;
}
//%outOfLineFunctions } +NdbBR9jtp3doAbuHEQ5sA
