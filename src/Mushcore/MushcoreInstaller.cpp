/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MushcoreInstaller.cpp,v 1.2 2003/01/17 13:30:41 southa Exp $
 * $Log: MushcoreInstaller.cpp,v $
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
