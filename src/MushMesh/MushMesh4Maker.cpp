//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Maker.cpp
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
//%Header } xZiQP5/l/Z1LcWmACtcmiA
/*
 * $Id$
 * $Log$
 */

#include "MushMesh4Maker.h"

MUSHCORE_SINGLETON_INSTANCE(MushMesh4Maker);

using namespace Mushware;
using namespace std;

void
MushMesh4Maker::Make(MushMesh4Mesh& ioMesh)
{
	throw MushcoreRequestFail("MushMesh4Maker not overriden - cannot build mesh");
}

//%outOfLineFunctions {

const char *MushMesh4Maker::AutoName(void) const
{
    return "MushMesh4Maker";
}

MushcoreVirtualObject *MushMesh4Maker::AutoClone(void) const
{
    return new MushMesh4Maker(*this);
}

MushcoreVirtualObject *MushMesh4Maker::AutoCreate(void) const
{
    return new MushMesh4Maker;
}

MushcoreVirtualObject *MushMesh4Maker::AutoVirtualFactory(void)
{
    return new MushMesh4Maker;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4Maker", MushMesh4Maker::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4Maker::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushMesh4Maker::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushMesh4Maker::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } C+6Nad+JPItHLhguOl+Slg
