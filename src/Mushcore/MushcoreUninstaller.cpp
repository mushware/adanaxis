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
 * $Id: MushcoreUninstaller.cpp,v 1.2 2003/01/17 13:30:41 southa Exp $
 * $Log: MushcoreUninstaller.cpp,v $
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
