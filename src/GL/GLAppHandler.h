#ifndef GLAPPHANDLER_H
#define GLAPPHANDLER_H
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
 * $Id: GLAppHandler.h,v 1.15 2002/08/07 13:36:46 southa Exp $
 * $Log: GLAppHandler.h,v $
 * Revision 1.15  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.14  2002/08/02 15:20:53  southa
 * Frame rate timing
 *
 * Revision 1.13  2002/08/02 12:56:38  southa
 * Working collision checking
 *
 * Revision 1.12  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.11  2002/07/10 16:37:39  southa
 * Cursor removal
 *
 * Revision 1.10  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.9  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.8  2002/06/23 10:42:33  southa
 * SDL input
 *
 * Revision 1.7  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
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
        kFullScreen,
        kWindow
    };
    virtual ~GLAppHandler() {}
    virtual bool KeyStateGet(const GLKeys& inKey) const = 0;
    virtual bool LatchedKeyStateTake(const GLKeys& inKey) = 0;
    virtual void MousePositionGet(tVal& outX, tVal& outY) const = 0;
    virtual void MouseDeltaTake(tVal& outX, tVal& outY) = 0;
    virtual void EnterScreen(tInitType inType) = 0;
    virtual void PostRedisplay(void) = 0;
    virtual void SwapBuffers(void) = 0;
    virtual U32 WidthGet(void) const = 0;
    virtual U32 HeightGet(void) const = 0;
    virtual U32 MillisecondsGet(void) const = 0;
    virtual void SetCursorState(bool inValue) = 0;
};
#endif
