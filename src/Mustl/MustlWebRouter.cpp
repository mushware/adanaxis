/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MustlWebRouter.cpp,v 1.9 2003/01/11 17:58:16 southa Exp $
 * $Log: MustlWebRouter.cpp,v $
 * Revision 1.9  2003/01/11 17:58:16  southa
 * Mustl fixes
 *
 * Revision 1.8  2003/01/09 14:57:08  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/29 21:00:00  southa
 * More build fixes
 *
 * Revision 1.6  2002/12/29 20:30:57  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.5  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/12/17 12:53:34  southa
 * Mustl library
 *
 * Revision 1.3  2002/12/13 01:06:54  southa
 * Mustl work
 *
 * Revision 1.2  2002/12/12 18:38:26  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:27  southa
 * Created Mustl
 *
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

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;
//using Mushware::MushcoreData;

auto_ptr<MustlWebRouter> MustlWebRouter::m_instance;

MustlWebRouter::MustlWebRouter() :
    m_lastTickMsec(0)
{
}

void
MustlWebRouter::ReceiveAll(void)
{
    tMsec currentMsec = MustlTimer::Instance().CurrentMsecGet();
    
    bool callTick=false;;
    if (m_lastTickMsec + kTickPeriod < currentMsec)
    {
        m_lastTickMsec = currentMsec;
        callTick = true;
    }

    MushcoreData<MustlWebLink>::tMapIterator endValue=MushcoreData<MustlWebLink>::Instance().End();
    MushcoreData<MustlWebLink>::tMapIterator killValue=MushcoreData<MustlWebLink>::Instance().End();
    
    for (MushcoreData<MustlWebLink>::tMapIterator p=MushcoreData<MustlWebLink>::Instance().Begin();
         p != endValue; ++p)
    {
        MUSTLASSERT(p->second != NULL);
        MustlWebLink& webLink = *p->second;
        if (callTick)
        {
            webLink.Tick();
        }

        if (webLink.IsDead())
        {
            killValue=p;
        }
        else
        {
            string linkData;
            for (U32 i=0; i<kMaxReceivesPerCall; ++i)
            {
                if (webLink.Receive(linkData))
                {
                    // MustlLog::Instance().Log() << "Received on " << p->first << ": '" << MustlUtils::MakePrintable(data) << "'" << endl;
                    webLink.ReceivedProcess(linkData);
                }
                else
                {
                    break;
                }
            }
        }
    }
    if (killValue != MushcoreData<MustlWebLink>::Instance().End())
    {
        MushcoreData<MustlWebLink>::Instance().Delete(killValue);
    }
}
