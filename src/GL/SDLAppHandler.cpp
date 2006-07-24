//%Header {
/*****************************************************************************
 *
 * File: src/GL/SDLAppHandler.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } X577BrzUUfCyG/exJzzEYQ
/*
 * $Id: SDLAppHandler.cpp,v 1.59 2006/07/21 10:52:06 southa Exp $
 * $Log: SDLAppHandler.cpp,v $
 * Revision 1.59  2006/07/21 10:52:06  southa
 * win32 build fixes
 *
 * Revision 1.58  2006/07/18 16:58:37  southa
 * Texture fixes
 *
 * Revision 1.57  2006/07/17 14:43:39  southa
 * Billboarded deco objects
 *
 * Revision 1.56  2006/07/11 19:49:04  southa
 * Control menu
 *
 * Revision 1.55  2006/07/08 16:05:55  southa
 * Ruby menus and key handling
 *
 * Revision 1.54  2006/07/07 18:13:57  southa
 * Menu start and stop
 *
 * Revision 1.53  2006/07/04 16:55:27  southa
 * Ruby key handling
 *
 * Revision 1.52  2006/07/02 09:43:27  southa
 * MushGLFont work
 *
 * Revision 1.51  2006/06/30 17:26:10  southa
 * Render prelude
 *
 * Revision 1.50  2006/06/01 15:38:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.49  2005/07/14 12:50:30  southa
 * Extrusion work
 *
 * Revision 1.48  2005/07/08 12:07:07  southa
 * MushGaem control work
 *
 * Revision 1.47  2005/06/06 15:07:09  southa
 * X11 work
 *
 * Revision 1.46  2005/05/27 12:48:36  southa
 * Registration box tweaks
 *
 * Revision 1.45  2005/05/26 16:05:29  southa
 * win32 support
 *
 * Revision 1.44  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.43  2005/04/10 00:09:22  southa
 * Registration
 *
 * Revision 1.42  2005/04/01 00:02:02  southa
 * Build tweaks
 *
 * Revision 1.41  2005/03/25 22:04:48  southa
 * Dialogue and MushcoreIO fixes
 *
 * Revision 1.40  2005/03/13 00:34:46  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.39  2005/01/26 00:48:46  southa
 * MushMeshGroup and rendering
 *
 * Revision 1.38  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.37  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.36  2003/08/21 23:08:33  southa
 * Fixed file headers
 *
 * Revision 1.35  2003/04/13 08:39:18  southa
 * Bring window to foreground on mode change
 *
 * Revision 1.34  2003/01/20 10:45:24  southa
 * Singleton tidying
 *
 * Revision 1.33  2003/01/13 14:31:56  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.32  2003/01/12 17:32:51  southa
 * Mushcore work
 *
 * Revision 1.31  2003/01/09 14:56:59  southa
 * Created Mushcore
 *
 * Revision 1.30  2002/12/29 20:59:53  southa
 * More build fixes
 *
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

#include "GLSTL.h"

using namespace Mushware;
using namespace std;


SDLAppHandler::SDLAppHandler():
    m_redisplay(false),
    m_visible(true),
    m_keyState(MediaKeyboard::kNumKeys, false),
    m_latchedKeyState(MediaKeyboard::kNumKeys, false),
    m_mouseX(0),
    m_mouseY(0),
    m_unboundedMouseX(0),
    m_unboundedMouseY(0),
    m_controlBuffer(kControlBufferSize, SDLControlEntry(0)),
    m_controlBufferIndex(0),
    m_firstDelta(true)
{
    m_deviceList.resize(kNumDevices);
    for (U32 i=0; i<kNumDevices; ++i)
    {
        m_deviceList[i].resize(kAxesPerDevice, 0);
    }
}

void
SDLAppHandler::Initialise(void)
{
    m_mouseX=0;
    m_mouseY=0;
    m_unboundedMouseX=0;
    m_unboundedMouseY=0;
    m_firstDelta=true;
    MediaJoystick::Sgl();
}

void
SDLAppHandler::Idle(void)
{
    MushcoreAppHandler::Idle();
}

void
SDLAppHandler::Display(void)
{
}

void
SDLAppHandler::KeyboardSignal(const GLKeyboardSignal& inSignal)
{
    U32 keyValue = inSignal.KeyValue();
    if (keyValue >= m_keyState.size())
    {
        m_keyState.resize(keyValue+1, false);
    }

    AddToControlBuffer(keyValue, inSignal.keyDown);
    
    m_keyState[keyValue]=inSignal.keyDown;
    if (inSignal.keyDown)
    {
        m_latchedKeyState[keyValue]=true;
    }
}

bool
SDLAppHandler::KeyStateGet(const Mushware::U32 inKey) const
{
    if (inKey >= m_keyState.size())
    {
        ostringstream message;
        message << "Key number " << inKey << " too large";
        throw MushcoreDataFail(message.str());
    }
    return m_keyState[inKey];
}

bool
SDLAppHandler::LatchedKeyStateTake(const Mushware::U32 inKey)
{
    if (inKey >= m_keyState.size())
    {
        ostringstream message;
        message << "Key number " << inKey << " too large";
        throw MushcoreDataFail(message.str());
    }
    bool state=m_latchedKeyState[inKey];
    if (state)
    {
        m_latchedKeyState[inKey]=false;
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

tVal
SDLAppHandler::ScaledUnboundedMouseX(void) const
{
    return m_unboundedMouseX / 640.0;
}

tVal
SDLAppHandler::ScaledUnboundedMouseY(void) const
{
    return -m_unboundedMouseY / 640.0;
}

void
SDLAppHandler::EnterScreen(const GLModeDef& inDef)
{
    GLUtils::Decache();

    PlatformVideoUtils::Sgl().ModeChangePrologue();
    MediaSDL::Sgl().InitVideoIfRequired();
    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
#if (SDL_MAJOR_VERSION >= 1) && (SDL_MINOR_VERSION >= 2) && (SDL_PATCHLEVEL >= 6)
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
#endif
    
#if (SDL_MAJOR_VERSION >= 1) && (SDL_MINOR_VERSION >= 2) && (SDL_PATCHLEVEL >= 10)
    // Attributes supported from SDL version 1.2.10 onwards
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
#endif
    
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
    
    PlatformVideoUtils::Sgl().ModeChangeEpilogue();
    if (surface == NULL) throw(MushcoreDeviceFail("Could not select a video mode"));


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
    SDL_WM_SetCaption(MushcoreInfo::Sgl().ApplicationNameGet().c_str(), (MushcoreInfo::Sgl().ApplicationNameGet()+".bmp").c_str());

    GLState::Reset();
    for (U32 i=0; i<m_keyState.size(); ++i)
    {
        m_keyState[i] = false;
    }
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

bool
SDLAppHandler::HasFocus(void) const
{
    return ((SDL_GetAppState() & SDL_APPINPUTFOCUS) != 0);
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
SDLAppHandler::Signal(const MushcoreAppSignal& inSignal)
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
        {
            if (inSignal.IsMushcoreAppSignal())
            {
                MushcoreAppHandler::Signal(inSignal);
            }
            else
            {
                cerr << "Unhandled SDLAppHandler signal 0x" << hex << inSignal.SigNumberGet() << dec << endl;
            }
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

    MediaSDL::Sgl().QuitVideoIfRequired();
}

void
SDLAppHandler::AddToControlBuffer(U32 inKeyValue, bool inKeyDirection)
{
    MUSHCOREASSERT(m_controlBufferIndex < m_controlBuffer.size());
    
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
                Signal(GLKeyboardSignal((event.key.type==SDL_KEYDOWN),
                                        static_cast<U32>(event.key.keysym.sym),
                                        static_cast<U32>(event.key.keysym.mod),
                                        m_mouseX, m_mouseY));
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
                    button > (MediaKeyboard::kKeyMouse4 - MediaKeyboard::kKeyMouse0))
                {
                    cerr << "Button index " << button << " ignored" << endl;
                    break;
                }
                m_mouseX=event.button.x;
                m_mouseY=event.button.y;
                Signal(GLKeyboardSignal((event.button.state == SDL_PRESSED),
                                        MediaKeyboard::kKeyMouse0+button,
                                        0,
                                        event.button.x, event.button.y));
            }
            break;

            case SDL_QUIT:
                m_doQuit=true;
                break;
                
            case SDL_JOYAXISMOTION:
            {
                if (event.jaxis.which < kNumDevices && event.jaxis.axis < kAxesPerDevice)
                {
                    tVal axisValue = - event.jaxis.value / 32768.0;
                    MushcoreUtil::Constrain<tVal>(axisValue, -1, 1);
                    m_deviceList[event.jaxis.which][event.jaxis.axis] = axisValue;
                }
            }
            break;
            
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
            {
                if (event.jbutton.which < kNumDevices)
                {
                    U32 keyValue = MediaKeyboard::kKeyStick0 +
                        MediaKeyboard::kKeyStickSpacing * event.jbutton.which +
                        event.jbutton.button;
                    Signal(GLKeyboardSignal((event.jbutton.state == SDL_PRESSED),
                                            keyValue,
                                            0,
                                            m_mouseX, m_mouseY));
                }
            }
            break;
            
            case SDL_JOYHATMOTION:
            {
                if (event.jhat.which < kNumDevices)
                {
                    bool leftState = (event.jhat.value & SDL_HAT_LEFT) != 0;
                    bool rightState = (event.jhat.value & SDL_HAT_RIGHT) != 0;
                    bool upState = (event.jhat.value & SDL_HAT_UP) != 0;
                    bool downState = (event.jhat.value & SDL_HAT_DOWN) != 0;
                    
                    U32 keyBase = MediaKeyboard::kKeyStick0 +
                        MediaKeyboard::kKeyStickSpacing * event.jhat.which +
                        MediaKeyboard::kKeyStickHat +
                        4 * event.jhat.hat;
                    Signal(GLKeyboardSignal(leftState,
                                            keyBase + MediaKeyboard::kKeyStickHatLeft,
                                            0,
                                            m_mouseX, m_mouseY));
                    Signal(GLKeyboardSignal(rightState,
                                            keyBase + MediaKeyboard::kKeyStickHatRight,
                                            0,
                                            m_mouseX, m_mouseY));
                    Signal(GLKeyboardSignal(upState,
                                            keyBase + MediaKeyboard::kKeyStickHatUp,
                                            0,
                                            m_mouseX, m_mouseY));
                    Signal(GLKeyboardSignal(downState,
                                            keyBase + MediaKeyboard::kKeyStickHatDown,
                                            0,
                                            m_mouseX, m_mouseY));
                }
            }
            break;    
                
            default:
                // Ignore
                break;
        }
        
        if (++loopCtr > 100) break;
    }
    
    if (loopCtr > 100)
    {
        throw MushcoreDataFail("event loopCtr overrun");
    }
}

Mushware::tVal
SDLAppHandler::DeviceAxis(Mushware::U32 inDevice, Mushware::U32 inAxis)
{
    if (inDevice >= kNumDevices || inAxis >= kAxesPerDevice)
    {
        ostringstream message;
        message << "Bad device (" << inDevice << ") or axis (" << inAxis << ") number";
        throw MushcoreDataFail(message.str());
    }
    return m_deviceList[inDevice][inAxis];
}

void
SDLAppHandler::KeysOfInterestSet(const vector<Mushware::U32>& inKeyValues)
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
        MUSHCOREASSERT(keyValue < m_keyState.size());
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


