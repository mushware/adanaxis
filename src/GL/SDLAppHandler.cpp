/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: SDLAppHandler.cpp,v 1.29 2002/12/20 13:17:37 southa Exp $
 * $Log: SDLAppHandler.cpp,v $
 * Revision 1.29  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.28  2002/12/03 20:28:15  southa
 * Network, player and control work
 *
 * Revision 1.27  2002/11/18 18:55:56  southa
 * Game resume and quit
 *
 * Revision 1.26  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.25  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
 *
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

#include "GLAppSignal.h"
#include "GLModeDef.h"
#include "GLStandard.h"
#include "GLState.h"
#include "GLUtils.h"

#include "mushMedia.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;


SDLAppHandler::SDLAppHandler():
    m_redisplay(false),
    m_visible(true),
    m_keyState(GLKeys::kNumberOfKeys, false),
    m_latchedKeyState(GLKeys::kNumberOfKeys, false),
    m_mouseX(0),
    m_mouseY(0),
    m_unboundedMouseX(0),
    m_unboundedMouseY(0),
    m_controlBuffer(kControlBufferSize, SDLControlEntry(0)),
    m_firstDelta(true)
{}

void
SDLAppHandler::Initialise(void)
{
    m_mouseX=0;
    m_mouseY=0;
    m_unboundedMouseX=0;
    m_unboundedMouseY=0;
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
    U32 keyValue = inSignal.keyValue.ValueGet();
    COREASSERT(keyValue < m_keyState.size());

    AddToControlBuffer(keyValue, inSignal.keyDown);
    
    m_keyState[keyValue]=inSignal.keyDown;
    if (inSignal.keyDown)
    {
        m_latchedKeyState[keyValue]=true;
    }

    if (keyValue == 27 && inSignal.keyDown)
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
SDLAppHandler::UnboundedMousePositionGet(S32& outX, S32& outY) const
{
    outX=m_unboundedMouseX;
    outY=-m_unboundedMouseY;
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
    m_keyState = vector<bool>(GLKeys::kNumberOfKeys, false);
    m_modeDef=inDef;
    PlatformVideoUtils::AppActivate();
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
    m_doQuit=false;
    while (!m_doQuit)
    {
        PollForControlEvents();
        if (m_redisplay)
        {
            m_redisplay=false;
            Display();
        }
        Idle();
    }
}

void
SDLAppHandler::AddToControlBuffer(U32 inKeyValue, bool inKeyDirection)
{
    COREASSERT(m_controlBufferIndex < m_controlBuffer.size());
    
    SDLControlEntry& controlEntry = m_controlBuffer[m_controlBufferIndex];
    controlEntry.timestamp = MillisecondsGet();
    controlEntry.keyValue = inKeyValue;
    controlEntry.keyDirection = inKeyDirection;
    controlEntry.unboundedMouseX = m_unboundedMouseX;
    controlEntry.unboundedMouseY = m_unboundedMouseY;

    ++m_controlBufferIndex;
    if (m_controlBufferIndex >= m_controlBuffer.size())
    {
        m_controlBufferIndex=0;
    }
}

void
SDLAppHandler::PollForControlEvents(void)
{
    U32 loopCtr=0;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                Signal(GLKeyboardSignal((event.key.type==SDL_KEYDOWN), TranslateKey(&event.key), m_mouseX, m_mouseY));
                break;

            case SDL_MOUSEMOTION:
            {
                // We log what the mouse position _was_ in the history, so as we track backwards
                // regenerating the control state we'll see the change at the right time
                AddToControlBuffer(0, 0);
                m_mouseX=event.motion.x;
                m_mouseY=event.motion.y;
                S32 mouseDeltaX = event.motion.xrel;
                S32 mouseDeltaY = event.motion.yrel;
                PlatformInputUtils::MouseDeltaOverrideGet(mouseDeltaX, mouseDeltaY);
                m_unboundedMouseX += mouseDeltaX;
                m_unboundedMouseY += mouseDeltaY;

            }
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
                m_doQuit=true;
                break;
        }
        
        if (++loopCtr > 100) break;
    }    
}

void
SDLAppHandler::KeysOfInterestSet(const vector<GLKeys::tKeyValue>& inKeyValues)
{
    m_keysOfInterest = inKeyValues;
}

void
SDLAppHandler::ReadHistoricControlState(S32& outUnboundedMouseX, S32& outUnboundedMouseY, vector<bool>& outKeys, tVal inAtMsec)
{
    if (outKeys.size() < m_keysOfInterest.size())
    {
        outKeys.resize(m_keysOfInterest.size());
    }
    U32 keysOfInterestSize = m_keysOfInterest.size();
    for (U32 i=0; i<keysOfInterestSize; ++i)
    {
        U32 keyValue = m_keysOfInterest[i];
        COREASSERT(keyValue < m_keyState.size());
        outKeys[i] = m_keyState[keyValue];
    }

    outUnboundedMouseX = m_unboundedMouseX;
    outUnboundedMouseY = m_unboundedMouseY;

    // Wind the control state back in time

    U32 bufferIndex = m_controlBufferIndex;
    U32 bufferSize = m_controlBuffer.size();
    do
    {
        if (bufferIndex == 0)
        {
            bufferIndex = bufferSize;
        }
        --bufferIndex;
        SDLControlEntry& bufferEntry = m_controlBuffer[bufferIndex];
        if (bufferEntry.timestamp > inAtMsec)
        {
            // Unwind this entry from the returned state
            outUnboundedMouseX = bufferEntry.unboundedMouseX;
            outUnboundedMouseY = bufferEntry.unboundedMouseY;
            if (bufferEntry.keyValue != 0)
            {
                for (U32 i=0; i<keysOfInterestSize; ++i)
                {
                    U32 keyValue = m_keysOfInterest[i];
                    if (bufferEntry.keyValue == keyValue)
                    {
                        // Negated because we are _removing_ this entry from the current state
                        outKeys[i] = !bufferEntry.keyDirection;
                        break;
                    }
                }
            }
        }
        else
        {
            // Timestamp are now older than we need to go
            break;
        }
    } while (bufferIndex != m_controlBufferIndex);
}

void
SDLAppHandler::AppQuit(void)
{
    m_doQuit=true;
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

