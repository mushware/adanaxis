/*
 * $Id: PlatformInputUtils.cpp,v 1.1 2002/06/06 12:30:18 southa Exp $
 * $Log: PlatformInputUtils.cpp,v $
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

bool
PlatformInputUtils::MouseDeltaPrologue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    ioX=cursorPos.x;
    ioY=cursorPos.y;
    if (ioX==ioLastX && ioY==ioLastY)
    {
	return false;
    }
    else
    {
	    return true;
    }
}

void
PlatformInputUtils::GetMouseDeltas(S32& outXDelta, S32& outYDelta, S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
    outXDelta=ioX-ioLastX;
    outYDelta=ioY-ioLastY;
}

void
PlatformInputUtils::MouseDeltaEpilogue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
    RECT rc; 
    GetClipCursor(&rc);
    int newXPos=(rc.left+rc.right)/2;
    int newYPos=(rc.top+rc.bottom)/2;
    SetCursorPos(newXPos, newYPos);
    ioLastX=newXPos;
    ioLastY=newYPos;
}

