#ifndef GLUTAPPHANDLER_H
#define GLUTAPPHANDLER_H
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
 * $Id: GLUTAppHandler.h,v 1.2 2002/06/23 10:42:33 southa Exp $
 * $Log: GLUTAppHandler.h,v $
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

class GLUTAppHandler : public GLAppHandler
{
public:
    GLUTAppHandler();
    virtual ~GLUTAppHandler() {}
    virtual bool KeyStateGet(const GLKeys& inKey) const;
    virtual void MousePositionGet(S32& outX, S32& outY) const;
    virtual void MouseDeltaGet(S32& outX, S32& outY);
    virtual void EnterScreen(tInitType inType);
    virtual void PostRedisplay(void);
    virtual void SwapBuffers(void);
    virtual U32 WidthGet(void) const {return m_width;}
    virtual U32 HeightGet(void) const {return m_height;}
    virtual U32 GetMilliseconds(void) const;
    
protected:
    virtual void Initialise(void);
    virtual void Idle(void);
    virtual void MainLoop(void);
    virtual void Display(void);
    virtual void KeyboardSignal(const GLKeyboardSignal& inSignal);
    virtual void Signal(const CoreAppSignal& inSignal);
    bool IsVisible(void) {return m_visible;}

    // GLUT specific
    void RegisterHandlers(void);
    static GLKeys TranslateSpecialKey(int inKey);

private:
    static void IdleHandler(void);
    static void DisplayHandler(void);
    static void VisibilityHandler(int inState);
    static void KeyboardHandler(unsigned char inKey, int inX, int inY);
    static void KeyboardUpHandler(unsigned char inKey, int inX, int inY);
    static void SpecialHandler(int inKey, int inX, int inY);
    static void SpecialUpHandler(int inKey, int inX, int inY);
    static void PassiveMotionHandler(int inX, int inY);
    bool m_visible;
    vector<bool> m_keyState;
    U32 m_width;
    U32 m_height;
    U32 m_bpp;
    static S32 m_mouseX;
    static S32 m_mouseY;
    static S32 m_lastMouseX;
    static S32 m_lastMouseY;
    static S32 m_mouseXDelta;
    static S32 m_mouseYDelta;
    static bool m_lastMouseValid;

};
#endif
