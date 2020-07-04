//%includeGuardStart {
#ifndef GLAPPHANDLER_H
#define GLAPPHANDLER_H
//%includeGuardStart } 1msgI15TWmC3n6mkLWTBUg
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLAppHandler.h
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
//%Header } wU8yC7z8Ru1AOB7+dRKwDA
/*
 * $Id: GLAppHandler.h,v 1.36 2006/07/31 11:01:37 southa Exp $
 * $Log: GLAppHandler.h,v $
 * Revision 1.36  2006/07/31 11:01:37  southa
 * Music and dialogues
 *
 * Revision 1.35  2006/07/21 10:52:05  southa
 * win32 build fixes
 *
 * Revision 1.34  2006/07/08 16:05:54  southa
 * Ruby menus and key handling
 *
 * Revision 1.33  2006/06/01 15:38:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.32  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.31  2005/05/27 12:48:36  southa
 * Registration box tweaks
 *
 * Revision 1.30  2005/05/19 13:01:57  southa
 * Mac release work
 *
 * Revision 1.29  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.28  2004/01/02 21:13:04  southa
 * Source conditioning
 *
 * Revision 1.27  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.26  2003/08/21 23:08:17  southa
 * Fixed file headers
 *
 * Revision 1.25  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.24  2003/01/09 14:56:57  southa
 * Created Mushcore
 *
 * Revision 1.23  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.22  2002/12/03 20:28:14  southa
 * Network, player and control work
 *
 * Revision 1.21  2002/11/18 18:55:56  southa
 * Game resume and quit
 *
 * Revision 1.20  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.19  2002/10/15 14:02:29  southa
 * Mode changes
 *
 * Revision 1.18  2002/10/14 18:13:17  southa
 * GLModeDef work
 *
 * Revision 1.17  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.16  2002/08/17 10:41:50  southa
 * Designer fixes
 *
 * Revision 1.15  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.14  2002/08/02 15:20:53  southa
 * Frame rate timing
 *
 * Revision 1.13  2002/08/02 12:56:38  southa
 * Working collision checking
 *
 * Revision 1.12  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.11  2002/07/10 16:37:39  southa
 * Cursor removal
 *
 * Revision 1.10  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.9  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.8  2002/06/23 10:42:33  southa
 * SDL input
 *
 * Revision 1.7  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
 * Revision 1.6  2002/06/20 15:50:29  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.5  2002/06/06 13:36:13  southa
 * Mouse handling
 *
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

#include "mushMushcore.h"

class GLModeDef;

//:xml1base MushcoreAppHandler
//:generate virtual abstract standard ostream xml1
class GLAppHandler : public MushcoreAppHandler
{
public:
    virtual ~GLAppHandler() {}
    virtual bool KeyStateGet(Mushware::S32 inKey) const = 0;
    virtual bool LatchedKeyStateTake(Mushware::S32 inKey) = 0;
    virtual void MousePositionGet(Mushware::tVal& outX, Mushware::tVal& outY) const = 0;
    virtual void UnboundedMousePositionGet(Mushware::S32& outX, Mushware::S32& outY) const = 0;
    virtual void EnterScreen(const GLModeDef& inDef) = 0;
    virtual void PostRedisplay(void) = 0;
    virtual void SwapBuffers(void) = 0;
    virtual Mushware::U32 WidthGet(void) const = 0;
    virtual Mushware::U32 HeightGet(void) const = 0;
    virtual Mushware::U32 ScreenWidth(void) const { return WidthGet(); }
    virtual Mushware::U32 ScreenHeight(void) const { return HeightGet(); }

    virtual Mushware::U32 MillisecondsGet(void) const = 0;
    virtual bool HasFocus(void) const = 0;
    virtual void SetCursorState(bool inValue) = 0;
    virtual const GLModeDef& CurrentModeDefGet(void) = 0;
    virtual void PollForControlEvents(void) = 0;
    virtual void AppQuit(void) = 0;
    virtual void KeysOfInterestSet(const std::vector<Mushware::S32>& inKeyValues) = 0;
    virtual void ReadHistoricControlState(Mushware::S32& outUnboundedMouseX, Mushware::S32& outUnboundedMouseY, std::vector<bool>& outKeys, Mushware::tVal inMsec) = 0;
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const GLAppHandler& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } rMqbKQaO7FVVOiv0GbwMmg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
