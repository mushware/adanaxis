//%includeGuardStart {
#ifndef SDLAPPHANDLER_H
#define SDLAPPHANDLER_H
//%includeGuardStart } H5tWwcRTm9Qy8lKFOS/83A
//%Header {
/*****************************************************************************
 *
 * File: src/GL/SDLAppHandler.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } /7Yj7cvvJAFoHDOehI9g2g
/*
 * $Id: SDLAppHandler.h,v 1.34 2007/03/09 19:50:12 southa Exp $
 * $Log: SDLAppHandler.h,v $
 * Revision 1.34  2007/03/09 19:50:12  southa
 * Resident textures
 *
 * Revision 1.33  2006/07/31 11:01:37  southa
 * Music and dialogues
 *
 * Revision 1.32  2006/07/28 16:52:20  southa
 * Options work
 *
 * Revision 1.31  2006/07/11 19:49:04  southa
 * Control menu
 *
 * Revision 1.30  2006/07/08 16:05:56  southa
 * Ruby menus and key handling
 *
 * Revision 1.29  2006/07/07 18:13:57  southa
 * Menu start and stop
 *
 * Revision 1.28  2006/06/01 15:38:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.27  2005/07/08 12:07:07  southa
 * MushGaem control work
 *
 * Revision 1.26  2005/05/27 12:48:37  southa
 * Registration box tweaks
 *
 * Revision 1.25  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.24  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.23  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.22  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.21  2003/08/21 23:08:33  southa
 * Fixed file headers
 *
 * Revision 1.20  2003/01/11 13:03:12  southa
 * Use Mushcore header
 *
 * Revision 1.19  2003/01/09 14:56:59  southa
 * Created Mushcore
 *
 * Revision 1.18  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.17  2002/12/03 20:28:15  southa
 * Network, player and control work
 *
 * Revision 1.16  2002/11/18 18:55:57  southa
 * Game resume and quit
 *
 * Revision 1.15  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.14  2002/10/15 14:02:30  southa
 * Mode changes
 *
 * Revision 1.13  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 * Revision 1.12  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.11  2002/08/17 10:41:50  southa
 * Designer fixes
 *
 * Revision 1.10  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.9  2002/08/02 15:20:54  southa
 * Frame rate timing
 *
 * Revision 1.7  2002/07/31 16:27:16  southa
 * Collision checking work
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

#include "GLAppHandler.h"
#include "GLModeDef.h"
#include "mushMushcore.h"

class GLKeyboardSignal;
struct SDL_Window;

class SDLControlEntry
{
public:
    explicit SDLControlEntry(Mushware::U32 inValue) : timestamp(inValue), unboundedMouseX(0), unboundedMouseY(0), keyValue(0), keyDirection(false) {}
    Mushware::U32 timestamp;
    Mushware::S32 unboundedMouseX;
    Mushware::S32 unboundedMouseY;
    Mushware::S32 keyValue;
    bool keyDirection;
};

// These don't work because this isn't the first class in the file
//:xml1base GLAppHandler
//:generate virtual standard ostream xml1
class SDLAppHandler : public GLAppHandler
{
public:
    SDLAppHandler();
    virtual ~SDLAppHandler() {}
    virtual bool KeyStateGet(Mushware::S32 inKey) const;
    virtual bool LatchedKeyStateTake(Mushware::S32 inKey);
    virtual void MousePositionGet(Mushware::tVal& outX, Mushware::tVal& outY) const;
    virtual void UnboundedMousePositionGet(Mushware::S32& outX, Mushware::S32& outY) const;
    virtual Mushware::tVal ScaledUnboundedMouseX(void) const;
    virtual Mushware::tVal ScaledUnboundedMouseY(void) const;
    virtual void EnterScreen(const GLModeDef& inDef);
    virtual void PostRedisplay(void);
    virtual void SwapBuffers(void);
    virtual Mushware::U32 WidthGet(void) const {return m_width;}
    virtual Mushware::U32 HeightGet(void) const {return m_height;}
    virtual Mushware::U32 MillisecondsGet(void) const;
    virtual bool HasFocus(void) const;
    virtual void SetCursorState(bool inValue);
    virtual const GLModeDef& CurrentModeDefGet(void);
    virtual void PollForControlEvents(void);
    virtual void AppQuit(void);
    virtual void KeysOfInterestSet(const std::vector<Mushware::S32>& inKeyValues);
    virtual void ReadHistoricControlState(Mushware::S32& outUnboundedMouseX, Mushware::S32& outUnboundedMouseY, std::vector<bool>& outKeys, Mushware::tVal inMsec);
    virtual Mushware::tVal DeviceAxis(Mushware::U32 inDevice, Mushware::U32 inAxis);
    virtual void KeyRepeatSet(bool inValue);
    virtual void MouseSensitivitySet(Mushware::tVal inValue) { m_mouseSensitivity = inValue; }
    virtual bool ScreenEntered(void) const { return m_screenEntered; }
    virtual bool ShiftAtStartupPressed(void) const { return m_shiftAtStartupPressed; }
    
protected:
    virtual void Initialise(void);
    virtual void Idle(void);
    virtual void MainLoop(void);
    virtual void Display(void);
    virtual void KeyboardSignal(const GLKeyboardSignal& inSignal);
    virtual void Signal(const MushcoreAppSignal& inSignal);
    bool IsVisible(void) {return m_visible;}
    
private:
    typedef std::vector<Mushware::tVal> tDeviceAxes;
    typedef std::vector<tDeviceAxes> tDeviceList;
    
    enum
    {
        kControlBufferSize=100,
        kNumDevices = 16,
        kAxesPerDevice = 16
    };

    void AddToControlBuffer(Mushware::U32 inKeyValue, bool inKeyDirection);
    
    Mushware::U32 m_width;
    Mushware::U32 m_height;
    Mushware::U32 m_bpp;
    bool m_showCursor;
    bool m_redisplay;
    bool m_visible;
    std::map<Mushware::S32, bool> m_keyState;
    std::map<Mushware::S32, bool> m_latchedKeyState;
    Mushware::tVal m_mouseX;
    Mushware::tVal m_mouseY;
    Mushware::S32 m_unboundedMouseX;
    Mushware::S32 m_unboundedMouseY;
    Mushware::tVal m_greatestDimension;
    GLModeDef m_modeDef;
    std::vector<SDLControlEntry> m_controlBuffer;
    Mushware::U32 m_controlBufferIndex;
    std::vector<Mushware::S32> m_keysOfInterest;
    bool m_firstDelta;
    bool m_doQuit;
    tDeviceList m_deviceList;
    Mushware::tVal m_mouseSensitivity;
    bool m_screenEntered;
    bool m_shiftAtStartupPressed;
    SDL_Window* m_pWindow;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
