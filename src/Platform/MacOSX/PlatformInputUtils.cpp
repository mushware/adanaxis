/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: PlatformInputUtils.cpp,v 1.2 2002/06/10 15:16:59 southa Exp $
 * $Log: PlatformInputUtils.cpp,v $
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

#include <ApplicationServices/ApplicationServices.h>

bool
PlatformInputUtils::MouseDeltaPrologue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
    return true;
}

void
PlatformInputUtils::GetMouseDeltas(S32& outXDelta, S32& outYDelta, S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
    CGMouseDelta xDelta, yDelta;
    CGGetLastMouseDelta(&xDelta, &yDelta);
    outXDelta=xDelta;
    outYDelta=yDelta;
}

void
PlatformInputUtils::MouseDeltaEpilogue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
}

