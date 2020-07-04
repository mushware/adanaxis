//%includeGuardStart {
#ifndef PLATFORMVIDEOUTILS_H
#define PLATFORMVIDEOUTILS_H
//%includeGuardStart } AEK+Al+NrqhKC+Q5B1/9Bg
//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformVideoUtils.h
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
//%Header } X9aMnhgGvCbJBIlZZgFEFQ
/*
 * $Id: PlatformVideoUtils.h,v 1.20 2007/06/25 17:58:49 southa Exp $
 * $Log: PlatformVideoUtils.h,v $
 * Revision 1.20  2007/06/25 17:58:49  southa
 * X11 fixes
 *
 * Revision 1.19  2007/04/18 09:23:23  southa
 * Header and level fixes
 *
 * Revision 1.18  2006/11/25 21:26:33  southa
 * Display mode definitions
 *
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

    void Acquaint(void);
    const GLModeDef& PreviousModeDef(const GLModeDef& inModeDef) const;
    const GLModeDef& NextModeDef(const GLModeDef& inModeDef) const;
    const GLModeDef& DefaultModeDef(void) const;
    Mushware::U32 NumModesGet(void) const;
    void RenderModeInfo(Mushware::U32 inNum) const;
    void ModeChangePrologue(void);
    void ModeChangeEpilogue(void);
    void ModeAdd(Mushware::U32 inWidth, Mushware::U32 inHeight);
    bool ModeSelectFixAttempt(Mushware::U32 inIteration);


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
