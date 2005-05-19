//%Header {
/*****************************************************************************
 *
 * File: src/Platform/MacOSX/PlatformInputUtils.cpp
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
//%Header } buThZSFeAbrqXgmDB6JlgA
/*
 * $Id: PlatformInputUtils.cpp,v 1.15 2005/03/13 00:34:48 southa Exp $
 * $Log: PlatformInputUtils.cpp,v $
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


bool
PlatformInputUtils::TranslateKey(GLKeys& outKey, const U32 inKeyCode)
{
    bool retVal = false;
    switch (inKeyCode)
    {
        case 310:
            // Command key
            outKey = GLKeys::kKeyCommand;
            retVal = true;
            break;
            
        case 'q':
            GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());

            if (glAppHandler.KeyStateGet(GLKeys::kKeyCommand))
            {
                outKey = GLKeys::kKeyQuit;
                retVal = true;
            }
            break;
    }
    return retVal;
}
