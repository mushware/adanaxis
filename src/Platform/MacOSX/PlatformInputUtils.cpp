/*
 * $Id: PlatformInputUtils.cpp,v 1.1 2002/06/06 14:59:57 southa Exp $
 * $Log: PlatformInputUtils.cpp,v $
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

