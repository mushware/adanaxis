//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreInstaller.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 5PXdwCnF43E8QsrzbKXGAA
/*
 * $Id: MushcoreInstaller.cpp,v 1.3 2003/08/21 23:09:14 southa Exp $
 * $Log: MushcoreInstaller.cpp,v $
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
