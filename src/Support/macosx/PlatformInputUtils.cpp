/*
 * $Id$
 * $Log$
 */

/*********************************
 *
 * MacOS X support file
 *
 *********************************/

#include "mushPlatform.h"

#include <ApplicationServices/ApplicationServices.h>

void
PlatformInputUtils::MouseDeltaPrologue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
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

