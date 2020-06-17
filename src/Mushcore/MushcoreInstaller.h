//%includeGuardStart {
#ifndef MUSHCOREINSTALLER_H
#define MUSHCOREINSTALLER_H
//%includeGuardStart } Md6j58uHfCuUvY5aZrdEIQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreInstaller.h
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
//%Header } 8/jr5gatb7lMQxsMZjjrpQ
/*
 * $Id: MushcoreInstaller.h,v 1.10 2006/06/06 17:58:34 southa Exp $
 * $Log: MushcoreInstaller.h,v $
 * Revision 1.10  2006/06/06 17:58:34  southa
 * Ruby texture definition
 *
 * Revision 1.9  2006/06/01 15:39:45  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:14  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/16 13:11:32  southa
 * Install and uninstall MustlPlatform
 *
 * Revision 1.3  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.8  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/04 17:01:20  southa
 * More work
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "MushcoreStandard.h"

#define MUSHCORE_INSTALLER(fnName) namespace { MushcoreInstaller a(fnName); }

// Functions passed to MushcoreUninstaller are called with the global
// constructors at application startup
class MushcoreInstaller
{
public:
    MushcoreInstaller(void (*inFuncPtr)(void));
    void NullFunction(void) const;

    static Mushware::U32 NumInstalledModulesGet(void);
private:
    static Mushware::U32 m_installedModules;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
