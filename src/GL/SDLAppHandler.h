/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"
#include "GLKeys.h"
#include "GLAppHandler.h"

class GLKeyboardSignal;

class SDLAppHandler : public GLAppHandler
{
public:
    SDLAppHandler(): m_redisplay(false), m_visible(true), m_keyState(GLKeys::kNumberOfKeys) {}
    virtual ~SDLAppHandler() {}
    virtual bool KeyStateGet(const GLKeys& inKey) const;
    virtual void MousePositionGet(S32& outX, S32& outY) const;
    virtual void MouseDeltaGet(S32& outX, S32& outY) const;
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

private:
    U32 m_width;
    U32 m_height;
    U32 m_bpp;
    bool m_redisplay;
    bool m_visible;
    vector<bool> m_keyState;
};
