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
 * $Id: PlatformInputUtils.cpp,v 1.8 2002/12/10 10:54:28 southa Exp $
 * $Log: PlatformInputUtils.cpp,v $
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

#include <windows.h>

using namespace Mushware;

void
PlatformInputUtils::MouseDeltaOverrideGet(S32& ioXDelta, S32& ioYDelta)
{
}

