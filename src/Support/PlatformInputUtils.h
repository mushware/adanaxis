#ifndef INPUTUTILS_H
#define INPUTUTILS_H
/*
 * $Id: InputUtils.h,v 1.1 2002/06/06 10:40:20 southa Exp $
 * $Log: InputUtils.h,v $
 * Revision 1.1  2002/06/06 10:40:20  southa
 * Created
 *
 */

#include "mushCore.h"

class PlatformInputUtils
{
public:
    static void MouseDeltaPrologue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY);    
    static void GetMouseDeltas(S32& outXDelta, S32& outYDelta, S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY);
    static void MouseDeltaEpilogue(S32& ioX, S32& ioY, S32& ioLastX, S32& ioLastY);
};

#endif
