#ifndef PLATFORMVIDEOUTILS_H
#define PLATFORMVIDEOUTILS_H
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
 * $Id: PlatformVideoUtils.h,v 1.5 2002/11/12 11:49:22 southa Exp $
 * $Log: PlatformVideoUtils.h,v $
 * Revision 1.5  2002/11/12 11:49:22  southa
 * Initial MHTML processing
 *
 * Revision 1.4  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.3  2002/10/17 15:50:59  southa
 * Config saving, pause and quit
 *
 * Revision 1.2  2002/10/15 14:02:31  southa
 * Mode changes
 *
 * Revision 1.1  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 */

#include "mushCore.h"

class GLModeDef;

class PlatformVideoUtils
{
public:
    PlatformVideoUtils();
    static PlatformVideoUtils& Instance(void) {return *((m_instance==NULL)?m_instance=new PlatformVideoUtils:m_instance);}
    const GLModeDef& ModeDefGet(U32 inNum);
    U32 PreviousModeDef(U32 inNum) const;
    U32 NextModeDef(U32 inNum) const;
    U32 DefaultModeGet(void) const;
    U32 NumModesGet(void) const;
    void RenderModeInfo(U32 inNum) const;
    static void VBLWait(void);
    static void ForceShowCursor(void);
    static void AppActivate(void);
    
private:
    vector<GLModeDef> m_modeDefs;
    static PlatformVideoUtils *m_instance;
};
#endif
