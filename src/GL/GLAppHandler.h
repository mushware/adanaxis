#ifndef GLAPPHANDLER_H
#define GLAPPHANDLER_H
/*
 * $Id: GLAppHandler.h,v 1.6 2002/06/20 15:50:29 southa Exp $
 * $Log: GLAppHandler.h,v $
 * Revision 1.6  2002/06/20 15:50:29  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.5  2002/06/06 13:36:13  southa
 * Mouse handling
 *
 * Revision 1.4  2002/06/05 16:29:51  southa
 * Mouse control
 *
 * Revision 1.3  2002/05/31 15:18:15  southa
 * Keyboard reading
 *
 * Revision 1.2  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 * Revision 1.1  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.5  2002/05/08 16:31:20  southa
 * Created API directory
 *
 * Revision 1.4  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 * Revision 1.3  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.2  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "mushCore.h"
#include "GLKeys.h"

class GLAppHandler : public CoreAppHandler
{
public:
    enum tInitType
    {
        kInvalid,
        kGame,
        kWindow
    };
    virtual ~GLAppHandler() {}
    virtual bool KeyStateGet(const GLKeys& inKey) const = 0;
    virtual void MousePositionGet(S32& outX, S32& outY) const = 0;
    virtual void MouseDeltaGet(S32& outX, S32& outY) const = 0;
    virtual void EnterScreen(tInitType inType) = 0;
    virtual void PostRedisplay(void) = 0;
    virtual void SwapBuffers(void) = 0;
    virtual U32 WidthGet(void) const = 0;
    virtual U32 HeightGet(void) const = 0;
    virtual U32 GetMilliseconds(void) const = 0;
};
#endif
