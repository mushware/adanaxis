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
 * $Id: SDLAppHandler.cpp,v 1.24 2002/10/15 14:02:30 southa Exp $
 * $Log: SDLAppHandler.cpp,v $
 * Revision 1.24  2002/10/15 14:02:30  southa
 * Mode changes
 *
 * Revision 1.23  2002/10/14 18:13:17  southa
 * GLModeDef work
 *
 * Revision 1.22  2002/10/12 15:25:11  southa
 * Facet renderer
 *
 * Revision 1.21  2002/10/06 22:09:59  southa
 * Initial lighting test
 *
 * Revision 1.20  2002/09/02 14:48:02  southa
 * RPM building
 *
 * Revision 1.19  2002/09/01 16:29:18  southa
 * Support Redhat paths for include files
 * Revision 1.18.4.1  2002/09/04 10:18:04  southa
 * Fixed for MacOS X 10.2
 *
 * Revision 1.18  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.17  2002/08/17 10:41:50  southa
 * Designer fixes
 *
 * Revision 1.16  2002/08/10 12:34:46  southa
 * Added current dialogues
 *
 * Revision 1.15  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.14  2002/08/05 22:30:19  southa
 * Made mode selection more robust
 *
 * Revision 1.13  2002/08/02 15:20:54  southa
 * Frame rate timing
 *
 * Revision 1.11  2002/07/31 16:27:16  southa
 * Collision checking work
 *
 * Revision 1.10  2002/07/19 16:25:21  southa
 * Texture tweaks
 *
 * Revision 1.9  2002/07/19 15:44:40  southa
 * Graphic optimisations
 *
 * Revision 1.8  2002/07/10 16:37:39  southa
 * Cursor removal
 *
 * Revision 1.7  2002/07/08 14:22:02  southa
 * Rotated desks
 *
 * Revision 1.6  2002/07/07 13:44:18  southa
 * Screen size config variables
 *
 * Revision 1.5  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.4  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
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

#include "SDLAppHandler.h"

#include "GLStandard.h"
#include "GLUtils.h"
#include "GLState.h"
#include "GLAppSignal.h"
#include "GLModeDef.h"

#include "mushPlatform.h"
#include "mushMedia.h"


SDLAppHandler::SDLAppHandler():
    m_redisplay(false),
    m_visible(true),
    m_keyState(GLKeys::kNumberOfKeys, false),
    m_latchedKeyState(GLKeys::kNumberOfKeys, false),
    m_mouseX(0),
    m_mouseY(0),
    m_mouseXDelta(0),
    m_mouseYDelta(0),
    m_firstDelta(true)
{}

void
SDLAppHandler::Initialise(void)
{
    m_mouseX=0;
    m_mouseY=0;
    m_mouseXDelta=0;
    m_mouseYDelta=0;
    m_firstDelta=true;
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
    if (inSignal.keyDown)
    {
        m_latchedKeyState[inSignal.keyValue.ValueGet()]=true;
    }

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

bool
SDLAppHandler::LatchedKeyStateTake(const GLKeys& inKey)
{
    COREASSERT(inKey.ValueGet() < m_keyState.size());
    bool state=m_latchedKeyState[inKey.ValueGet()];
    if (state)
    {
        m_latchedKeyState[inKey.ValueGet()]=false;
    }
    return state;
}

void
SDLAppHandler::MousePositionGet(tVal& outX, tVal& outY) const
{
    // Return with origin in the centre and bottom left at -x,-y.  The screen should
    // measure 1 in its largest dimension
    outX=(m_mouseX - m_width/2) / m_greatestDimension;
    outY=(m_height/2 - m_mouseY) / m_greatestDimension;
}

void
SDLAppHandler::MouseDeltaTake(tVal& outXDelta, tVal& outYDelta)
{
    if (m_firstDelta)
    {
        outXDelta=0;
        outYDelta=0;
        m_firstDelta=false;
    }
    else
    {
        // Normalise based on 640x480 screen
        outXDelta=m_mouseXDelta/640;
        outYDelta=-m_mouseYDelta/640;
    }
    m_mouseXDelta=0;
    m_mouseYDelta=0;
}

void
SDLAppHandler::EnterScreen(const GLModeDef& inDef)
{
    GLUtils::Decache();

    MediaSDL::Instance().QuitVideoIfRequired();
    MediaSDL::Instance().InitVideo();
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_width=inDef.WidthGet();
    m_height=inDef.HeightGet();
    m_bpp=inDef.BPPGet();
    m_showCursor=inDef.CursorShowGet();
    U32 sdlFlags=0;
    if (inDef.FullScreenGet())
    {
        sdlFlags=SDL_OPENGL|SDL_FULLSCREEN;
    }
    else
    {
        sdlFlags=SDL_OPENGL;
    }

    SDL_Surface *surface=SDL_SetVideoMode(m_width, m_height, m_bpp, sdlFlags);

    if (surface == NULL)
    {
        cerr << "SDL video mode failed again - trying for any mode" << endl;
        surface=SDL_SetVideoMode(m_width, m_height, m_bpp, sdlFlags|SDL_ANYFORMAT);
    }
    if (surface == NULL)
    {
        cerr << "SDL video mode failed again - reducing bpp to 15" << endl;
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
        surface=SDL_SetVideoMode(m_width, m_height, m_bpp, sdlFlags|SDL_ANYFORMAT);
    }
    if (surface == NULL) throw(DeviceFail("Could not select a video mode"));


    // Got video mode
    if (m_width > m_height)
    {
        m_greatestDimension=m_width;
    }
    else
    {
        m_greatestDimension=m_height;
    }
    SetCursorState(m_showCursor);
    GLState::Reset();
    m_keyState = vector<bool>(GLKeys::kNumberOfKeys, false),
    m_modeDef=inDef;
}

const GLModeDef&
SDLAppHandler::CurrentModeDefGet(void)
{
    return m_modeDef;
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
SDLAppHandler::MillisecondsGet(void) const
{
    return SDL_GetTicks();
}

void
SDLAppHandler::SetCursorState(bool inValue)
{
    if (!inValue && !m_showCursor)
    {
        SDL_ShowCursor(SDL_DISABLE);
    }
    else
    {
        SDL_ShowCursor(SDL_ENABLE);
        PlatformVideoUtils::ForceShowCursor();
    }    
}

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
                case SDL_KEYUP:
                    Signal(GLKeyboardSignal((event.key.type==SDL_KEYDOWN), TranslateKey(&event.key), m_mouseX, m_mouseY));
                    break;

                case SDL_MOUSEMOTION:
                    m_mouseX=event.motion.x;
                    m_mouseY=event.motion.y;
                    m_mouseXDelta+=event.motion.xrel;
                    m_mouseYDelta+=event.motion.yrel;
                    PlatformInputUtils::MouseDeltaOverrideGet(m_mouseXDelta, m_mouseYDelta);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                {
                    U32 button=event.button.button-1;
                    if (event.button.button < 1 ||
                        button > (GLKeys::kKeyMouse5 - GLKeys::kKeyMouse1))
                    {
                        cerr << "Button index " << button << " ignored" << endl;
                        break;
                    }
                    m_mouseX=event.button.x;
                    m_mouseY=event.button.y;
                    Signal(GLKeyboardSignal((event.button.state == SDL_PRESSED),
                                       GLKeys(GLKeys::kKeyMouse1+button),
                                       event.button.x, event.button.y));
                }
                break;
                    
                case SDL_QUIT:
                    doQuit=true;
                    break;
            }
        }

        if (!isEvent)
        {
            if (m_redisplay)
            {
                m_redisplay=false;
                Display();
            }
            Idle();
        }
    }
}

GLKeys
SDLAppHandler::TranslateKey(void *inKeyEvent) const
{
    SDLKey keyValue=static_cast<SDL_KeyboardEvent *>(inKeyEvent)->keysym.sym;
    switch (keyValue)
    {
        case SDLK_F1:
            return GLKeys::kKeyF1;

        case SDLK_F2:
            return GLKeys::kKeyF2;

        case SDLK_F3:
            return GLKeys::kKeyF3;

        case SDLK_F4:
            return GLKeys::kKeyF4;

        case SDLK_F5:
            return GLKeys::kKeyF5;

        case SDLK_F6:
            return GLKeys::kKeyF6;

        case SDLK_F7:
            return GLKeys::kKeyF7;

        case SDLK_F8:
            return GLKeys::kKeyF8;

        case SDLK_F9:
            return GLKeys::kKeyF9;

        case SDLK_F10:
            return GLKeys::kKeyF10;

        case SDLK_F11:
            return GLKeys::kKeyF11;

        case SDLK_F12:
            return GLKeys::kKeyF12;

        case SDLK_LEFT:
            return GLKeys::kKeyLeft;

        case SDLK_UP:
            return GLKeys::kKeyUp;

        case SDLK_RIGHT:
            return GLKeys::kKeyRight;

        case SDLK_DOWN:
            return GLKeys::kKeyDown;

        case SDLK_PAGEUP:
            return GLKeys::kKeyPageUp;

        case SDLK_PAGEDOWN:
            return GLKeys::kKeyPageDown;

        case SDLK_HOME:
            return GLKeys::kKeyHome;

        case SDLK_END:
            return GLKeys::kKeyEnd;

        case SDLK_INSERT:
            return GLKeys::kKeyInsert;

        default:
            if (keyValue > 0 && keyValue < 0x100)
            {
                return keyValue;
            }
            break;
    }
    cerr << "Ignored SDL key " << keyValue << endl;
    return 0;
}

