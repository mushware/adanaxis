/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MushcoreUninstaller.cpp,v 1.1 2003/01/16 13:11:32 southa Exp $
 * $Log: MushcoreUninstaller.cpp,v $
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
