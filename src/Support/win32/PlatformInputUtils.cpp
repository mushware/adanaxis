/*
 * $Id: InputUtils.cpp,v 1.1 2002/06/06 10:40:20 southa Exp $
 * $Log: InputUtils.cpp,v $
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

#include <winuser.h>

void
PlatformInputUtils::MouseDeltaPrologue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
}

void
PlatformInputUtils::GetMouseDeltas(S32& outXDelta, S32& outYDelta, S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
}

void
PlatformInputUtils::MouseDeltaEpilogue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY)
{
    RECT rcOldClip; 
    GetClipCursor(&rcOldClip);
    int newXPos=(rc.left+rc.right)/2;
    int newYPos=(rc.top+rc.bottom)/2;
    SetCursorPos(newXPos, newYPos);
    ioLastX=newXPos;
    inLastY=newYPos;
}

