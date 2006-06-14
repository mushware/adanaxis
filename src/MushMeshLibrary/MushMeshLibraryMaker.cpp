//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryMaker.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Gpg4xmCu29c825wXOynyhA
/*
 * $Id$
 * $Log$
 */

#include "MushMeshLibraryMaker.h"

#include "MushMeshLibraryBase.h"

using namespace Mushware;
using namespace std;

void
MushMeshLibraryMaker::Make(MushMesh4Mesh& ioMesh)
{
	MushMeshLibraryBase::Sgl().PolygonPrismCreate(ioMesh, t4Val(1,1,1,1), 9);
}

//%outOfLineFunctions {

const char *MushMeshLibraryMaker::AutoName(void) const
{
    return "MushMeshLibraryMaker";
}

MushcoreVirtualObject *MushMeshLibraryMaker::AutoClone(void) const
{
    return new MushMeshLibraryMaker(*this);
}

MushcoreVirtualObject *MushMeshLibraryMaker::AutoCreate(void) const
{
    return new MushMeshLibraryMaker;
}

MushcoreVirtualObject *MushMeshLibraryMaker::AutoVirtualFactory(void)
{
    return new MushMeshLibraryMaker;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshLibraryMaker", MushMeshLibraryMaker::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshLibraryMaker::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushMesh4Maker::AutoPrint(ioOut);
    ioOut << "]";
}
bool
MushMeshLibraryMaker::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushMesh4Maker::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMeshLibraryMaker::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushMesh4Maker::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } uwucyOGWYSJTgsbnT9mYFw
