/*
 * $Id$
 * $Log$
 */

#include "MushcoreUninstaller.h"

#include "MushcoreFail.h"

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
