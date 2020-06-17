//%Header {
/*****************************************************************************
 *
 * File: src/Platform/MacOSX/PlatformInputUtils.cpp
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
//%Header } NcpmWEolG/BQE6A7UR7xcA
/*
 * $Id: PlatformInputUtils.cpp,v 1.20 2007/04/18 09:23:23 southa Exp $
 * $Log: PlatformInputUtils.cpp,v $
 * Revision 1.20  2007/04/18 09:23:23  southa
 * Header and level fixes
 *
 * Revision 1.19  2006/07/08 16:06:01  southa
 * Ruby menus and key handling
 *
 * Revision 1.18  2006/07/07 18:14:00  southa
 * Menu start and stop
 *
 * Revision 1.17  2006/06/01 15:39:58  southa
 * DrawArray verification and fixes
 *
 * Revision 1.16  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.15  2005/03/13 00:34:48  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.14  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.13  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:09:35  southa
 * Fixed file headers
 *
 * Revision 1.11  2002/12/29 21:00:00  southa
 * More build fixes
 *
 * Revision 1.10  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/12/03 20:28:18  southa
 * Network, player and control work
 *
 * Revision 1.8  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/06 22:10:00  southa
 * Initial lighting test
 *
 * Revision 1.6.4.1  2002/09/04 10:18:04  southa
 * Fixed for MacOS X 10.2
 *
 * Revision 1.6  2002/08/27 08:56:29  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 * Revision 1.1  2002/06/06 14:59:57  southa
 * Mouse fixes
 *
 * Revision 1.1  2002/06/06 13:36:31  southa
 * Mouse handling
 *
 */

/*********************************
 *
 * MacOS X support file
 *
 *********************************/

#include "mushPlatform.h"

#include "mushGL.h"

#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

using namespace Mushware;
using namespace std;

void
PlatformInputUtils::MouseDeltaOverrideGet(S32& ioXDelta, S32& ioYDelta)
{
    CGMouseDelta xDelta, yDelta;
    CGGetLastMouseDelta(&xDelta, &yDelta);
    ioXDelta=xDelta;
    ioYDelta=yDelta;
}

Mushware::U32
PlatformInputUtils::CurrentKeyModifiers(void)
{
    U32 retVal = 0;
    
    UInt32 keyMods = GetCurrentKeyModifiers();
    
    if ((keyMods & shiftKey) != 0)
    {
        retVal |= kKeyModShift;
    }
    if ((keyMods & controlKey) != 0)
    {
        retVal |= kKeyModCtrl;
    }
    if ((keyMods & optionKey) != 0)
    {
        retVal |= kKeyModAlt;
    }
    if ((keyMods & cmdKey) != 0)
    {
        retVal |= kKeyModMeta;
    }
    return retVal;
}
