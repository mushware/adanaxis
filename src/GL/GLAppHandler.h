/*
 * $Id: GLAppHandler.h,v 1.4 2002/06/05 16:29:51 southa Exp $
 * $Log: GLAppHandler.h,v $
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

class GLKeyboardSignal;

class GLAppHandler : public CoreAppHandler
{
public:
    GLAppHandler(): m_visible(true), m_keyState(GLKeys::kNumberOfKeys) {}
    virtual ~GLAppHandler() {}
    bool KeyStateGet(const GLKeys& inKey) const;
    void MousePositionGet(S32& outX, S32& outY) const;
    void MouseDeltaGet(S32& outX, S32& outY) const;
    
protected:
    virtual void Initialise(void);
    virtual void Idle(void);
    virtual void MainLoop(void);
    virtual void Display(void);
    virtual void KeyboardSignal(const GLKeyboardSignal& inSignal);
    virtual void Signal(const CoreAppSignal& inSignal);
    bool IsVisible(void) {return m_visible;}
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
    static S32 m_mouseX;
    static S32 m_mouseY;
    static S32 m_lastMouseX;
    static S32 m_lastMouseY;
    static S32 m_mouseXDelta;
    static S32 m_mouseYDelta;
    static bool m_lastMouseValid;
};
