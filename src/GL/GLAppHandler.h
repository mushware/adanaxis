//%includeGuardStart {
#ifndef GLAPPHANDLER_H
#define GLAPPHANDLER_H
//%includeGuardStart } 1msgI15TWmC3n6mkLWTBUg
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLAppHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } XaCf/61A2bEdA+h4Wlnatw
/*
 * $Id: GLAppHandler.h,v 1.28 2004/01/02 21:13:04 southa Exp $
 * $Log: GLAppHandler.h,v $
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

#include "GLKeys.h"
#include "mushMushcore.h"

class GLModeDef;

class GLAppHandler : public MushcoreAppHandler
{
public:
    virtual ~GLAppHandler() {}
    virtual bool KeyStateGet(const GLKeys& inKey) const = 0;
    virtual bool LatchedKeyStateTake(const GLKeys& inKey) = 0;
    virtual void MousePositionGet(Mushware::tVal& outX, Mushware::tVal& outY) const = 0;
    virtual void UnboundedMousePositionGet(Mushware::S32& outX, Mushware::S32& outY) const = 0;
    virtual void EnterScreen(const GLModeDef& inDef) = 0;
    virtual void PostRedisplay(void) = 0;
    virtual void SwapBuffers(void) = 0;
    virtual Mushware::U32 WidthGet(void) const = 0;
    virtual Mushware::U32 HeightGet(void) const = 0;
    virtual Mushware::U32 MillisecondsGet(void) const = 0;
    virtual void SetCursorState(bool inValue) = 0;
    virtual const GLModeDef& CurrentModeDefGet(void) = 0;
    virtual void PollForControlEvents(void) = 0;
    virtual void AppQuit(void) = 0;
    virtual void KeysOfInterestSet(const std::vector<GLKeys::tKeyValue>& inKeyValues) = 0;
    virtual void ReadHistoricControlState(Mushware::S32& outUnboundedMouseX, Mushware::S32& outUnboundedMouseY, std::vector<bool>& outKeys, Mushware::tVal inMsec) = 0;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
