//%includeGuardStart {
#ifndef MUSHCOREINSTALLER_H
#define MUSHCOREINSTALLER_H
//%includeGuardStart } Md6j58uHfCuUvY5aZrdEIQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreInstaller.h
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
//%Header } PrawP4g9KR4/8l4yzD6HLg
/*
 * $Id: MushcoreInstaller.h,v 1.9 2006/06/01 15:39:45 southa Exp $
 * $Log: MushcoreInstaller.h,v $
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
