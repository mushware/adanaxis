/*
 * $Id: PlatformInputUtils.cpp,v 1.1 2002/06/06 14:59:57 southa Exp $
 * $Log: PlatformInputUtils.cpp,v $
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


bool
PlatformInputUtils::MouseDeltaPrologue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
}

void
PlatformInputUtils::GetMouseDeltas(S32& outXDelta, S32& outYDelta, S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
    throw(LogicFail("GetMouseDeltas not implemented for X11"));
}

void
PlatformInputUtils::MouseDeltaEpilogue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
}

