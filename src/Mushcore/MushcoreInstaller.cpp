//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreInstaller.cpp
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
//%Header } hRztbsgwZVxlWapKGk+lWw
/*
 * $Id: MushcoreInstaller.cpp,v 1.6 2005/05/19 13:02:15 southa Exp $
 * $Log: MushcoreInstaller.cpp,v $
 * Revision 1.6  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:14  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.1  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 */

#include "MushcoreInstaller.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

U32 MushcoreInstaller::m_installedModules=0;

MushcoreInstaller::MushcoreInstaller(void (*inFuncPtr)(void))
{
    inFuncPtr();
    ++m_installedModules;
}

void
MushcoreInstaller::NullFunction(void) const
{
}

U32
MushcoreInstaller::NumInstalledModulesGet(void)
{
    return m_installedModules;
}
