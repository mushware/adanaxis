/*
 * $Id: MustlWebRouter.cpp,v 1.4 2002/12/05 13:20:13 southa Exp $
 * $Log: MustlWebRouter.cpp,v $
 * Revision 1.4  2002/12/05 13:20:13  southa
 * Client link handling
 *
 * Revision 1.3  2002/11/23 17:23:45  southa
 * Sleep in setup
 *
 * Revision 1.2  2002/11/12 17:05:01  southa
 * Tidied localweb server
 *
 * Revision 1.1  2002/11/06 14:16:57  southa
 * Basic web server
 *
 */

#include "MustlWebRouter.h"

#include "MustlLog.h"
#include "MustlProtocol.h"
#include "MustlUtils.h"
#include "MustlWebLink.h"

auto_ptr<MustlWebRouter> MustlWebRouter::m_instance;

MustlWebRouter::MustlWebRouter() :
m_lastTickMsec(0)
{
}

void
MustlWebRouter::ReceiveAll(void)
{
    U32 currentMsec = SDL_GetTicks();
    bool callTick=false;;
    if (m_lastTickMsec + kTickPeriod < currentMsec)
    {
        m_lastTickMsec = currentMsec;
        callTick = true;
    }

    CoreData<MustlWebLink>::tMapIterator endValue=CoreData<MustlWebLink>::Instance().End();
    CoreData<MustlWebLink>::tMapIterator killValue=CoreData<MustlWebLink>::Instance().End();

    if (callTick)
    {
        for (CoreData<MustlWebLink>::tMapIterator p=CoreData<MustlWebLink>::Instance().Begin();
             p != endValue; ++p)
        {
            p->second->Tick();
            if (p->second->IsDead())
            {
                killValue=p;
            }
        }
    }

    if (killValue != CoreData<MustlWebLink>::Instance().End())
    {
        CoreData<MustlWebLink>::Instance().Delete(killValue->first);
    }
    
    for (CoreData<MustlWebLink>::tMapIterator p=CoreData<MustlWebLink>::Instance().Begin();
         p != endValue; ++p)
    {
        string data;
        for (U32 i=0; i<kMaxReceivesPerCall; ++i)
        {
            if (p->second->Receive(data))
            {
                // MustlLog::Instance().Log() << "Received on " << p->first << ": '" << MustlUtils::MakePrintable(data) << "'" << endl;
                p->second->ReceivedProcess(data);
            }
            else
            {
                break;
            }
        }
    }
}
