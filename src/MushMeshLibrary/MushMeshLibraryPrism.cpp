//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryPrism.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Zvd4xMcAvYhSnElgi3Y3jQ
/*
 * $Id: MushMeshLibraryPrism.cpp,v 1.1 2006/06/16 01:02:32 southa Exp $
 * $Log: MushMeshLibraryPrism.cpp,v $
 * Revision 1.1  2006/06/16 01:02:32  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshLibraryPrism.h"

#include "MushMeshLibraryBase.h"

using namespace Mushware;
using namespace std;

void
MushMeshLibraryPrism::Make(MushMesh4Mesh& ioMesh) const
{
	if (m_order < 3)
	{
		throw MushcoreRequestFail("Bad order parameter for prism creation");	
	}
	MushMeshLibraryBase::Sgl().PolygonPrismCreate(ioMesh, t4Val(1,1,1,1), m_order);
}

//%outOfLineFunctions {

const char *MushMeshLibraryPrism::AutoName(void) const
{
    return "MushMeshLibraryPrism";
}

MushcoreVirtualObject *MushMeshLibraryPrism::AutoClone(void) const
{
    return new MushMeshLibraryPrism(*this);
}

MushcoreVirtualObject *MushMeshLibraryPrism::AutoCreate(void) const
{
    return new MushMeshLibraryPrism;
}

MushcoreVirtualObject *MushMeshLibraryPrism::AutoVirtualFactory(void)
{
    return new MushMeshLibraryPrism;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshLibraryPrism", MushMeshLibraryPrism::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshLibraryPrism::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushMesh4Base::AutoPrint(ioOut);
    ioOut << "order=" << m_order;
    ioOut << "]";
}
bool
MushMeshLibraryPrism::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "order")
    {
        ioIn >> m_order;
    }
    else if (MushMesh4Base::AutoXMLDataProcess(ioIn, inTagStr))
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
MushMeshLibraryPrism::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushMesh4Base::AutoXMLPrint(ioOut);
    ioOut.TagSet("order");
    ioOut << m_order;
}
//%outOfLineFunctions } Q5tLA0/BRTrEF1mGw/XgbA
