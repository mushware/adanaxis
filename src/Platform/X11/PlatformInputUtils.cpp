//%Header {
/*****************************************************************************
 *
 * File: src/Platform/X11/PlatformInputUtils.cpp
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
//%Header } iOrN2AGdWBFdRmViCdLj4A
/*
 * $Id: PlatformInputUtils.cpp,v 1.15 2005/05/19 13:02:21 southa Exp $
 * $Log: PlatformInputUtils.cpp,v $
 * Revision 1.15  2005/05/19 13:02:21  southa
 * Mac release work
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
 * Revision 1.11  2003/02/05 18:49:52  southa
 * Build fixes
 *
 * Revision 1.10  2003/01/12 17:33:01  southa
 * Mushcore work
 *
 * Revision 1.9  2002/12/29 21:00:00  southa
 * More build fixes
 *
 * Revision 1.8  2002/12/20 13:17:48  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:42:08  southa
 * Source conditioning
 *
 * Revision 1.6  2002/10/21 10:54:33  southa
 * X11 build updates
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
 * Revision 1.1  2002/06/26 17:56:34  southa
 * Created
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
 * X11 support file
 *
 *********************************/

#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

void
PlatformInputUtils::MouseDeltaOverrideGet(S32& ioXDelta, S32& ioYDelta)
{
}

bool
PlatformInputUtils::TranslateKey(GLKeys& outKey, const U32 inKeyCode)
{
    bool retVal = false;
    return retVal;
}
