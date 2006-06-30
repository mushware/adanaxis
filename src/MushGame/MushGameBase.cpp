//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameBase.cpp
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
//%Header } 72jYu/IZevqg7bsvRKLvxw
/*
 * $Id$
 * $Log$
 */

#include "MushGameBase.h"

#include "API/mushMushGL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGameBase);

void
MushGameBase::SwapIn(MushGameAppHandler& inHandler)
{
    
}

void
MushGameBase::SwapOut(MushGameAppHandler& inHandler)
{
    MushGLUtil::Purge();
    MushGLV::Sgl().Purge();
}
//%outOfLineFunctions {

const char *MushGameBase::AutoName(void) const
{
    return "MushGameBase";
}

MushcoreVirtualObject *MushGameBase::AutoClone(void) const
{
    return new MushGameBase(*this);
}

MushcoreVirtualObject *MushGameBase::AutoCreate(void) const
{
    return new MushGameBase;
}

MushcoreVirtualObject *MushGameBase::AutoVirtualFactory(void)
{
    return new MushGameBase;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameBase", MushGameBase::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameBase::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameBase::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameBase::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } 3yx1HCmGcBDPT0sFAvjmng
