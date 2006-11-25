//%includeGuardStart {
#ifndef PLATFORMVIDEOUTILS_H
#define PLATFORMVIDEOUTILS_H
//%includeGuardStart } AEK+Al+NrqhKC+Q5B1/9Bg
//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformVideoUtils.h
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
//%Header } VLWFZJL8pEO5dQmZmEC5Ww
/*
 * $Id: PlatformVideoUtils.h,v 1.17 2006/06/01 15:39:57 southa Exp $
 * $Log: PlatformVideoUtils.h,v $
 * Revision 1.17  2006/06/01 15:39:57  southa
 * DrawArray verification and fixes
 *
 * Revision 1.16  2005/05/26 00:46:40  southa
 * Made buildable on win32
 *
 * Revision 1.15  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.14  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.13  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.12  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.11  2003/08/21 23:09:34  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/04/13 08:39:18  southa
 * Bring window to foreground on mode change
 *
 * Revision 1.9  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.8  2003/01/11 13:03:18  southa
 * Use Mushcore header
 *
 * Revision 1.7  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/12/03 20:28:18  southa
 * Network, player and control work
 *
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

#include "mushMushcore.h"

class GLModeDef;

class PlatformVideoUtils
{
public:
    PlatformVideoUtils();
    static PlatformVideoUtils& Sgl(void) {return *((m_instance==NULL)?m_instance=new PlatformVideoUtils:m_instance);}

    const GLModeDef& PreviousModeDef(const GLModeDef& inModeDef) const;
    const GLModeDef& NextModeDef(const GLModeDef& inModeDef) const;
    const GLModeDef& DefaultModeDef(void) const;
    Mushware::U32 NumModesGet(void) const;
    void RenderModeInfo(Mushware::U32 inNum) const;
    void ModeChangePrologue(void);
    void ModeChangeEpilogue(void);
    void ModeAdd(Mushware::U32 inWidth, Mushware::U32 inHeight);

    static void VBLWait(void);
    static void ForceShowCursor(void);
    static void AppActivate(void);
    
protected:
    Mushware::U32 ModeDefFind(const GLModeDef& inModeDef) const;
    
private:

    std::vector<GLModeDef> m_modeDefs;
    std::vector< std::pair<long, long> > m_modesSoFar;
    static PlatformVideoUtils *m_instance;

    bool m_threadAttached;
    unsigned long m_fgThreadID;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
