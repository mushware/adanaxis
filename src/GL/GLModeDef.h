#ifndef GLMODEDEF_H
#define GLMODEDEF_H

/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GLModeDef.h,v 1.2 2002/10/15 14:02:29 southa Exp $
 * $Log: GLModeDef.h,v $
 * Revision 1.2  2002/10/15 14:02:29  southa
 * Mode changes
 *
 * Revision 1.1  2002/10/14 18:13:17  southa
 * GLModeDef work
 *
 */

#include "mushCore.h"

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
    
    GLModeDef(const string& inName, U32 inWidth, U32 inHeight,
              U32 inBpp, U32 inHz, tScreen inScreen, tCursor inCursor, tSync inSync) :
        m_name(inName),
        m_width(inWidth),
        m_height(inHeight),
        m_bpp(inBpp),
        m_hz(inHz),
        m_screen(inScreen),
        m_cursor(inCursor),
        m_sync(inSync)
    {}

    const string& NameGet(void) const { return m_name; }
    U32 WidthGet(void) const { return m_width; }
    U32 HeightGet(void) const { return m_height; }
    U32 BPPGet(void) const { return m_bpp; }
    U32 HzGet(void) const { return m_hz; }
    bool FullScreenGet(void) const { return m_screen == kScreenFull; }
    bool CursorShowGet(void) const { return m_cursor == kCursorShow; }
    bool HardSyncGet(void) const { return m_sync == kSyncHard; }
    tSync SyncGet(void) const { return m_sync; }

    static GLModeDef Default(void);

private:
    string m_name;
    U32 m_width;
    U32 m_height;
    U32 m_bpp;
    U32 m_hz;
    tScreen m_screen;
    tCursor m_cursor;
    tSync m_sync;
};
#endif
