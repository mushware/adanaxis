//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreUninstaller.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } LoEwKR7uXmnnBZ3mMAks7A
/*
 * $Id: MushcoreUninstaller.cpp,v 1.4 2003/09/17 19:40:36 southa Exp $
 * $Log: MushcoreUninstaller.cpp,v $
 * Revision 1.4  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:18  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.1  2003/01/16 13:11:32  southa
 * Install and uninstall MustlPlatform
 *
 */

#include "MushcoreUninstaller.h"

#include "MushcoreFail.h"

using namespace Mushware;
using namespace std;

MushcoreUninstaller::MushcoreUninstaller(tFuncPtr inFuncPtr) :
    m_funcPtr(inFuncPtr)
{
    if (inFuncPtr == NULL)
    {
        throw(MushcoreLogicFail("Cannot pass NULL to MushcoreUninstaller"));
    }
}

MushcoreUninstaller::~MushcoreUninstaller()
{
    m_funcPtr();
}

void
MushcoreUninstaller::NullFunction(void) const
{
}
