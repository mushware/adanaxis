/*
 * $Id$
 * $Log$
 */

#include "SDLAppHandler.h"

#include "GLStandard.h"
#include "GLUtils.h"
#include "GLAppSignal.h"

#include "mushPlatform.h"
#include "mushMedia.h"

void
SDLAppHandler::Initialise(void)
{

}

void
SDLAppHandler::Idle(void)
{
    CoreAppHandler::Idle();
}

void
SDLAppHandler::Display(void)
{
}

void
SDLAppHandler::KeyboardSignal(const GLKeyboardSignal& inSignal)
{
    COREASSERT(inSignal.keyValue.ValueGet() < m_keyState.size());
    m_keyState[inSignal.keyValue.ValueGet()]=inSignal.keyDown;

    if (inSignal.keyValue.ValueGet() == 27 && inSignal.keyDown)
    {
        // Escape key pressed
        CoreAppHandler::Instance().Signal(CoreAppSignal(CoreAppSignal::kEscape));
    }
}

bool
SDLAppHandler::KeyStateGet(const GLKeys& inKey) const
{
    COREASSERT(inKey.ValueGet() < m_keyState.size());
    return m_keyState[inKey.ValueGet()];
}

void
SDLAppHandler::MousePositionGet(S32& outX, S32& outY) const
{
    outX=0;
    outY=0;
}

void
SDLAppHandler::MouseDeltaGet(S32& outXDelta, S32& outYDelta) const
{
    outXDelta=0;
    outYDelta=0; 
}

void
SDLAppHandler::EnterScreen(tInitType inType)
{
    MediaSDL::Instance().InitVideo();
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_width=640;
    m_height=480;
    m_bpp=32;
    
    switch (inType)
    {
        case kGame:
            SDL_SetVideoMode(m_width, m_height, m_bpp, SDL_OPENGL|SDL_FULLSCREEN);
            break;

        case kWindow:
            SDL_SetVideoMode(m_width, m_height, m_bpp, SDL_OPENGL);
            break;

        default:
            throw(LogicFail("Bad value to SDLAppHandler::EnterScreen"));
    }
}

void
SDLAppHandler::PostRedisplay(void)
{
    m_redisplay=true;
}

void
SDLAppHandler::SwapBuffers(void)
{
    SDL_GL_SwapBuffers();
}
U32
SDLAppHandler::GetMilliseconds(void) const
{
    return SDL_GetTicks();
}

#if 0
void
SDLAppHandler::IdleHandler(void)
{
    Instance().Idle();
}

void
SDLAppHandler::VisibilityHandler(int inState)
{
    if (inState == GLUT_NOT_VISIBLE)
    {
        Instance().Signal(GLAppSignal(GLAppSignal::kVisible));
    }
    else if (inState == GLUT_VISIBLE)
    {
        Instance().Signal(GLAppSignal(GLAppSignal::kVisible));
    }
}

void
SDLAppHandler::DisplayHandler(void)
{
    Instance().Signal(GLAppSignal(GLAppSignal::kDisplay));
}

void
SDLAppHandler::KeyboardHandler(unsigned char inKey, int inX, int inY)
{
    Instance().Signal(GLKeyboardSignal(1, inKey, inX, inY));
}

void
SDLAppHandler::KeyboardUpHandler(unsigned char inKey, int inX, int inY)
{
    Instance().Signal(GLKeyboardSignal(0, inKey, inX, inY));
}

void
SDLAppHandler::SpecialHandler(int inKey, int inX, int inY)
{
    Instance().Signal(GLKeyboardSignal(1, TranslateSpecialKey(inKey), inX, inY));
}

void
SDLAppHandler::SpecialUpHandler(int inKey, int inX, int inY)
{
    Instance().Signal(GLKeyboardSignal(0, TranslateSpecialKey(inKey), inX, inY));
}

void
SDLAppHandler::PassiveMotionHandler(int inX, int inY)
{
    S32 deltaX=0;
    S32 deltaY=0;
    
    if (!m_lastMouseValid)
    {
        m_lastMouseX=inX;
        m_lastMouseY=inY;
    }
    
    if (PlatformInputUtils::MouseDeltaPrologue(inX, inY, m_lastMouseX, m_lastMouseY))
    {
    	PlatformInputUtils::GetMouseDeltas(deltaX, deltaY, inX, inY, m_lastMouseX, m_lastMouseY);
    	PlatformInputUtils::MouseDeltaEpilogue(inX, inY, m_lastMouseX, m_lastMouseY);
    }
    if (m_lastMouseValid)
    {
        m_mouseXDelta+=deltaX;
        m_mouseYDelta+=deltaY;
    }
    else
    {
        m_lastMouseValid=true;
    }

    m_mouseX=inX;
    m_mouseY=inY;
}

#endif

void
SDLAppHandler::Signal(const CoreAppSignal& inSignal)
{
    switch (inSignal.SigNumberGet())
    {
        case GLAppSignal::kDisplay:
            Display();
            break;

        case GLAppSignal::kVisible:
            m_visible=true;
            break;

        case GLAppSignal::kNotVisible:
            m_visible=false;
            break;

        case GLAppSignal::kKeyboard:
        {
            KeyboardSignal(dynamic_cast<const GLKeyboardSignal&>(inSignal));
        }
        break;

        default:
            if (inSignal.IsCoreAppSignal())
            {
                CoreAppHandler::Signal(inSignal);
            }
            else
            {
                cerr << "Unhandled SDLAppHandler signal 0x" << hex << inSignal.SigNumberGet() << dec << endl;
            }
            break;
    }
}    

void
SDLAppHandler::MainLoop(void)
{
    bool doQuit=false;
    while (!doQuit)
    {
        SDL_Event event;
        bool isEvent=SDL_PollEvent(&event);
        if (isEvent)
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    break;

                case SDL_QUIT:
                    doQuit=true;
                    break;
            }
        }
        if (m_redisplay)
        {
            m_redisplay=false;
            Display();
        }
        if (!isEvent)
        {
            Idle();
        }
    }
}    
