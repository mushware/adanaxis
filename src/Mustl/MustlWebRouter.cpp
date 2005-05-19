//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlWebRouter.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } QgVYeHVnb0+kbOOk7qNckw
/*
 * $Id: MustlWebRouter.cpp,v 1.15 2004/01/02 21:13:16 southa Exp $
 * $Log: MustlWebRouter.cpp,v $
 * Revision 1.15  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.14  2003/10/06 22:23:45  southa
 * Game to GameMustl move
 *
 * Revision 1.13  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:09:33  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.10  2003/01/13 15:01:20  southa
 * Fix Mustl command line build
 *
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

MUSHCORE_SINGLETON_INSTANCE(MustlWebRouter);

MustlWebRouter::MustlWebRouter() :
    m_lastTickMsec(0)
{
}

void
MustlWebRouter::ReceiveAll(void)
{
    tMsec currentMsec = MustlTimer::Sgl().CurrentMsecGet();
    
    bool callTick=false;;
    if (m_lastTickMsec + kTickPeriod < currentMsec)
    {
        m_lastTickMsec = currentMsec;
        callTick = true;
    }

    MushcoreData<MustlWebLink>::tMapIterator endValue=MushcoreData<MustlWebLink>::Sgl().End();
    MushcoreData<MustlWebLink>::tMapIterator killValue=MushcoreData<MustlWebLink>::Sgl().End();
    
    for (MushcoreData<MustlWebLink>::tMapIterator p=MushcoreData<MustlWebLink>::Sgl().Begin();
         p != endValue; ++p)
    {
        try
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
                        // MustlLog::Sgl().Log() << "Received on " << p->first << ": '" << MustlUtils::MakePrintable(data) << "'" << endl;
                        webLink.ReceivedProcess(linkData);
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        catch (MushcoreNonFatalFail& e)
        {
            MustlLog::Sgl().WebLog() << "Network exception: " << e.what() << endl;
        }
    }
    if (killValue != MushcoreData<MustlWebLink>::Sgl().End())
    {
        MushcoreData<MustlWebLink>::Sgl().Delete(killValue);
    }
}
