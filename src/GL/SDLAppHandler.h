#ifndef SDLAPPHANDLER_H
#define SDLAPPHANDLER_H
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
 * $Id: SDLAppHandler.h,v 1.6 2002/07/19 15:44:40 southa Exp $
 * $Log: SDLAppHandler.h,v $
 * Revision 1.6  2002/07/19 15:44:40  southa
 * Graphic optimisations
 *
 * Revision 1.5  2002/07/10 16:37:39  southa
 * Cursor removal
 *
 * Revision 1.4  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/23 10:42:33  southa
 * SDL input
 *
 * Revision 1.1  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
 */

#include "mushCore.h"
#include "GLKeys.h"
#include "GLAppHandler.h"

class GLKeyboardSignal;

class SDLAppHandler : public GLAppHandler
{
public:
    SDLAppHandler();
    virtual ~SDLAppHandler() {}
    virtual bool KeyStateGet(const GLKeys& inKey) const;
    virtual void MousePositionGet(S32& outX, S32& outY) const;
    virtual void MouseDeltaGet(tVal& outX, tVal& outY);
    virtual void EnterScreen(tInitType inType);
    virtual void PostRedisplay(void);
    virtual void SwapBuffers(void);
    virtual U32 WidthGet(void) const {return m_width;}
    virtual U32 HeightGet(void) const {return m_height;}
    virtual U32 GetMilliseconds(void) const;
    virtual void SetCursorState(bool inValue);
    
protected:
    virtual void Initialise(void);
    virtual void Idle(void);
    virtual void MainLoop(void);
    virtual void Display(void);
    virtual void KeyboardSignal(const GLKeyboardSignal& inSignal);
    virtual void Signal(const CoreAppSignal& inSignal);
    bool IsVisible(void) {return m_visible;}
    GLKeys TranslateKey(/* SDL_KeyboardEvent */ void *inKeyEvent) const;
    
private:
    U32 m_width;
    U32 m_height;
    U32 m_bpp;
    bool m_showCursor;
    bool m_redisplay;
    bool m_visible;
    vector<bool> m_keyState;
    U32 m_mouseX;
    U32 m_mouseY;
    tVal m_mouseXDelta;
    tVal m_mouseYDelta;
};
#endif
