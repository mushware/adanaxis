/*
 * $Id: SDLAppHandler.h,v 1.1 2002/06/21 18:50:16 southa Exp $
 * $Log: SDLAppHandler.h,v $
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
    GLKeys TranslateKey(/* SDL_KeyboardEvent */ void *inKeyEvent) const;
    
private:
    U32 m_width;
    U32 m_height;
    U32 m_bpp;
    bool m_redisplay;
    bool m_visible;
    vector<bool> m_keyState;
    U32 m_mouseX;
    U32 m_mouseY;
    U32 m_mouseXDelta;
    U32 m_mouseYDelta;
};
