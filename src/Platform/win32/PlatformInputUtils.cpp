//%Header {
/*****************************************************************************
 *
 * File: src/Platform/win32/PlatformInputUtils.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } RRqRe7Sh2HawjZTlRdSSOQ
/*
 * $Id: PlatformInputUtils.cpp,v 1.18 2007/04/18 09:23:24 southa Exp $
 * $Log: PlatformInputUtils.cpp,v $
 * Revision 1.18  2007/04/18 09:23:24  southa
 * Header and level fixes
 *
 * Revision 1.17  2006/07/08 16:06:01  southa
 * Ruby menus and key handling
 *
 * Revision 1.16  2006/06/01 15:39:58  southa
 * DrawArray verification and fixes
 *
 * Revision 1.15  2005/05/26 00:46:40  southa
 * Made buildable on win32
 *
 * Revision 1.14  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.13  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.12  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.11  2003/08/21 23:09:36  southa
 * Fixed file headers
 *
 * Revision 1.10  2002/12/29 21:00:01  southa
 * More build fixes
 *
 * Revision 1.9  2002/12/20 13:17:48  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/12/10 10:54:28  southa
 * AppActivate and input cleanup
 *
 * Revision 1.7  2002/10/22 20:42:08  southa
 * Source conditioning
 *
 * Revision 1.6  2002/10/08 22:27:00  southa
 * Fixed for win32
 *
 * Revision 1.5  2002/08/27 08:56:29  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.1  2002/06/06 14:59:57  southa
 * Mouse fixes
 *
 * Revision 1.1  2002/06/06 12:30:18  southa
 * Added support for src/Support/platform
 *
 * Revision 1.1  2002/06/06 10:40:20  southa
 * Created
 *
 */

/*********************************
 *
 * Windows support file
 *
 *********************************/

#include "mushPlatform.h"

#define NOMINMAX
#include <windows.h>

using namespace Mushware;
using namespace std;

void
PlatformInputUtils::MouseDeltaOverrideGet(S32& ioXDelta, S32& ioYDelta)
{
}

Mushware::U32
PlatformInputUtils::CurrentKeyModifiers(void)
{
    U32 retVal = 0;
    
    if ((GetAsyncKeyState(VK_LSHIFT) & (1<<15)) != 0 ||
        (GetAsyncKeyState(VK_RSHIFT) & (1<<15)) != 0)
    {
        retVal |= kKeyModShift;
    }
    if ((GetAsyncKeyState(VK_LCONTROL) & (1<<15)) != 0 ||
        (GetAsyncKeyState(VK_RCONTROL) & (1<<15)) != 0)
    {
        retVal |= kKeyModCtrl;
    }
    if ((GetAsyncKeyState(VK_LMENU) & (1<<15)) != 0 ||
        (GetAsyncKeyState(VK_RMENU) & (1<<15)) != 0)
    {
        retVal |= kKeyModAlt;
    }
    if ((GetAsyncKeyState(VK_LWIN) & (1<<15)) != 0 ||
        (GetAsyncKeyState(VK_RWIN) & (1<<15)) != 0)
    {
        retVal |= kKeyModMeta;
    }
    return retVal;
}
