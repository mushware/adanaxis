/*
 * $Id: MediaNetWebRouter.cpp,v 1.2 2002/11/12 17:05:01 southa Exp $
 * $Log: MediaNetWebRouter.cpp,v $
 * Revision 1.2  2002/11/12 17:05:01  southa
 * Tidied localweb server
 *
 * Revision 1.1  2002/11/06 14:16:57  southa
 * Basic web server
 *
 */

#include "MediaNetWebRouter.h"

#include "MediaNetLog.h"
#include "MediaNetProtocol.h"
#include "MediaNetUtils.h"
#include "MediaNetWebLink.h"

auto_ptr<MediaNetWebRouter> MediaNetWebRouter::m_instance;

MediaNetWebRouter::MediaNetWebRouter() :
m_lastTickMsec(0)
{
}

void
MediaNetWebRouter::ReceiveAll(void)
{
    U32 currentMsec = SDL_GetTicks();
    bool callTick=false;;
    if (m_lastTickMsec + kTickPeriod < currentMsec)
    {
        m_lastTickMsec = currentMsec;
        callTick = true;
    }

    CoreData<MediaNetWebLink>::tMapIterator endValue=CoreData<MediaNetWebLink>::Instance().End();
    CoreData<MediaNetWebLink>::tMapIterator killValue=CoreData<MediaNetWebLink>::Instance().End();

    if (callTick)
    {
        for (CoreData<MediaNetWebLink>::tMapIterator p=CoreData<MediaNetWebLink>::Instance().Begin();
             p != endValue; ++p)
        {
            p->second->Tick();
            if (p->second->IsDead())
            {
                killValue=p;
            }
        }
    }

    if (killValue != CoreData<MediaNetWebLink>::Instance().End())
    {
        CoreData<MediaNetWebLink>::Instance().DataDelete(killValue->first);
    }
    
    for (CoreData<MediaNetWebLink>::tMapIterator p=CoreData<MediaNetWebLink>::Instance().Begin();
         p != endValue; ++p)
    {
        string data;
        for (U32 i=0; i<kMaxReceivesPerCall; ++i)
        {
            if (p->second->Receive(data))
            {
                // MediaNetLog::Instance().Log() << "Received on " << p->first << ": '" << MediaNetUtils::MakePrintable(data) << "'" << endl;
                p->second->ReceivedProcess(data);
            }
            else
            {
                break;
            }
        }
    }
}
