//%includeGuardStart {
#ifndef MUSHCOREINSTALLER_H
#define MUSHCOREINSTALLER_H
//%includeGuardStart } Md6j58uHfCuUvY5aZrdEIQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreInstaller.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /7wr4A8Yk6GeA/5lcuifhw
/*
 * $Id: MushcoreInstaller.h,v 1.6 2003/09/17 19:40:35 southa Exp $
 * $Log: MushcoreInstaller.h,v $
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
