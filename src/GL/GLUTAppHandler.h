#ifndef GLUTAPPHANDLER_H
#define GLUTAPPHANDLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GLUTAppHandler.h,v 1.15 2002/11/18 18:55:56 southa Exp $
 * $Log: GLUTAppHandler.h,v $
 * Revision 1.15  2002/11/18 18:55:56  southa
 * Game resume and quit
 *
 * Revision 1.14  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.13  2002/10/15 14:02:29  southa
 * Mode changes
 *
 * Revision 1.12  2002/10/14 18:13:17  southa
 * GLModeDef work
 *
 * Revision 1.11  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/17 10:41:50  southa
 * Designer fixes
 *
 * Revision 1.9  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.8  2002/08/02 15:20:54  southa
 * Frame rate timing
 *
 * Revision 1.7  2002/08/02 12:56:39  southa
 * Working collision checking
 *
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
#include "GLModeDef.h"

class GLKeyboardSignal;

class GLUTAppHandler : public GLAppHandler
{
public:
    GLUTAppHandler();
    virtual ~GLUTAppHandler() {}
    virtual bool KeyStateGet(const GLKeys& inKey) const;
    virtual bool LatchedKeyStateTake(const GLKeys& inKey);
    virtual void MousePositionGet(tVal& outX, tVal& outY) const;
    virtual void UnboundedMousePositionGet(S32& outX, S32& outY) const;
    virtual void EnterScreen(const GLModeDef& inDef);
    virtual void PostRedisplay(void);
    virtual void SwapBuffers(void);
    virtual U32 WidthGet(void) const {return m_width;}
    virtual U32 HeightGet(void) const {return m_height;}
    virtual U32 MillisecondsGet(void) const;
    virtual void SetCursorState(bool inValue);
    virtual const GLModeDef& CurrentModeDefGet(void);
    virtual void PollForControlEvents(void);
    virtual void AppQuit(void);
    virtual void KeysOfInterestSet(const vector<GLKeys::tKeyValue>& inKeyValues);
    virtual void ReadHistoricControlState(S32& outUnboundedMouseX, S32& outUnboundedMouseY, vector<bool>& outKeys, tVal inMsec);
    
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
    vector<bool> m_latchedKeyState;
    U32 m_width;
    U32 m_height;
    U32 m_bpp;
    GLModeDef m_modeDef;

    static S32 m_mouseX;
    static S32 m_mouseY;
    static S32 m_lastMouseX;
    static S32 m_lastMouseY;
    static S32 m_mouseXDelta;
    static S32 m_mouseYDelta;
    static bool m_lastMouseValid;
};
#endif
