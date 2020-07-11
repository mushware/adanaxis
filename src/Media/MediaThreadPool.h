//%includeGuardStart {
#ifndef MEDIATHREADPOOL_H
#define MEDIATHREADPOOL_H
//%includeGuardStart } eNAmS7Ud1fB5c0IOfBUI4Q
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaThreadPool.h
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
//%Header } JQfYaOtS63pq8Ta8jhSbVw

#include "MediaSDL.h"
#include "MediaStandard.h"

class MediaJob;

//:generate
class MediaThreadPool : public MushcoreSingleton<MediaThreadPool>
{
public:

    MediaThreadPool();
    virtual ~MediaThreadPool();

    MediaJobId JobIdTake();

    virtual void WaitMapGive(std::auto_ptr<MediaJob> apJob);
    virtual void MediaThreadPool::WaitMapGive(MediaJob **pJob);
    virtual bool OutputQueueTake(MediaJob **pJob);
    virtual void MainThreadPump();
    virtual void JobKill(MediaJobId jobId);
    virtual void JobKillIfExists(MediaJobId jobId);
    virtual void JobKillByType(const std::string& jobType);

protected:
    void JobDelete(MediaJobId jobId);
    void JobStart(MediaJobId jobId);
    bool InputQueueTake(MediaJob **pJob);
    void OutputQueueGive(MediaJob **pJob);
    void HandleStateChange();

    virtual void InputQueueGive(std::auto_ptr<MediaJob> apJob);
    virtual void InputQueueGive(MediaJob **pJob);

private:
    MediaJobId m_nextJobId;
    Mushware::U32 m_numThreads;
    SDL_atomic_t m_done;
    SDL_sem *m_pJobAvailSem;
    SDL_mutex *m_pStateMutex;
    std::vector<SDL_Thread *> m_threads;
    std::map<MediaJobId, MediaJob *> m_jobMap;
    std::deque<MediaJob *> m_inputQueue;
    std::deque<MediaJob *> m_outputQueue;
    bool m_stateHasChanged;
    Mushware::tVal m_threadPumpTimeLimit; //:readwrite

    static int MediaThreadPool::ThreadHandler(void *data);

//%classPrototypes {
public:
    const Mushware::tVal& ThreadPumpTimeLimit(void) const { return m_threadPumpTimeLimit; }
    void ThreadPumpTimeLimitSet(const Mushware::tVal& inValue) { m_threadPumpTimeLimit=inValue; }
//%classPrototypes } twD9UlX7OhJnx0po+Cft7A
};


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
