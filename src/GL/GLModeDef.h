//%includeGuardStart {
#ifndef GLMODEDEF_H
#define GLMODEDEF_H
//%includeGuardStart } HpyOkMHY3tVLkWwkBhP8FQ
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLModeDef.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } 1BHMSi7yjZ2g63pCINCKcw

/*
 * $Id: GLModeDef.h,v 1.10 2004/01/06 20:46:49 southa Exp $
 * $Log: GLModeDef.h,v $
 * Revision 1.10  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.9  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:08:24  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.5  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.2  2002/10/15 14:02:29  southa
 * Mode changes
 *
 * Revision 1.1  2002/10/14 18:13:17  southa
 * GLModeDef work
 *
 */

#include "mushMushcore.h"

class GLModeDef
{
public:
    enum tScreen
    {
        kScreenInvalid,
        kScreenNone,
        kScreenWindow,
        kScreenFull
    };
    enum tSync
    {
        kSyncInvalid,
        kSyncNone,
        kSyncSoft,
        kSyncHard
    };
    enum tCursor
    {
        kCursorInvalid,
        kCursorNone,
        kCursorHide,
        kCursorShow
    };

    GLModeDef();
    
    GLModeDef(const std::string& inName, Mushware::U32 inWidth, Mushware::U32 inHeight,
              Mushware::U32 inBpp, Mushware::U32 inHz, tScreen inScreen, tCursor inCursor, tSync inSync) :
        m_name(inName),
        m_width(inWidth),
        m_height(inHeight),
        m_bpp(inBpp),
        m_hz(inHz),
        m_screen(inScreen),
        m_cursor(inCursor),
        m_sync(inSync)
    {}

    const std::string& NameGet(void) const { return m_name; }
    Mushware::U32 WidthGet(void) const { return m_width; }
    Mushware::U32 HeightGet(void) const { return m_height; }
    Mushware::U32 BPPGet(void) const { return m_bpp; }
    Mushware::U32 HzGet(void) const { return m_hz; }
    bool FullScreenGet(void) const { return m_screen == kScreenFull; }
    bool CursorShowGet(void) const { return m_cursor == kCursorShow; }
    bool HardSyncGet(void) const { return m_sync == kSyncHard; }
    tSync SyncGet(void) const { return m_sync; }

    static GLModeDef Default(void);

private:
    std::string m_name;
    Mushware::U32 m_width;
    Mushware::U32 m_height;
    Mushware::U32 m_bpp;
    Mushware::U32 m_hz;
    tScreen m_screen;
    tCursor m_cursor;
    tSync m_sync;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
