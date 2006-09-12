//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibrarySingleFacet.cpp
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
//%Header } jXe27ZCKRIN0zXKHCsxj4Q
/*
 * $Id: MushMeshLibrarySingleFacet.cpp,v 1.2 2006/08/01 17:21:35 southa Exp $
 * $Log: MushMeshLibrarySingleFacet.cpp,v $
 * Revision 1.2  2006/08/01 17:21:35  southa
 * River demo
 *
 * Revision 1.1  2006/07/17 14:43:41  southa
 * Billboarded deco objects
 *
 */


#include "MushMeshLibrarySingleFacet.h"

#include "MushMeshLibraryBase.h"

using namespace Mushware;
using namespace std;

void
MushMeshLibrarySingleFacet::Make(MushMesh4Mesh& ioMesh) const
{
	if (m_order < 3)
	{
		throw MushcoreRequestFail("Bad order parameter for facet creation");	
	}
	MushMeshLibraryBase::Sgl().SingleFacetCreate(ioMesh, m_order);
}

//%outOfLineFunctions {

const char *MushMeshLibrarySingleFacet::AutoName(void) const
{
    return "MushMeshLibrarySingleFacet";
}

MushcoreVirtualObject *MushMeshLibrarySingleFacet::AutoClone(void) const
{
    return new MushMeshLibrarySingleFacet(*this);
}

MushcoreVirtualObject *MushMeshLibrarySingleFacet::AutoCreate(void) const
{
    return new MushMeshLibrarySingleFacet;
}

MushcoreVirtualObject *MushMeshLibrarySingleFacet::AutoVirtualFactory(void)
{
    return new MushMeshLibrarySingleFacet;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshLibrarySingleFacet", MushMeshLibrarySingleFacet::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshLibrarySingleFacet::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushMesh4Base::AutoPrint(ioOut);
    ioOut << "order=" << m_order;
    ioOut << "]";
}
bool
MushMeshLibrarySingleFacet::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushMeshLibrarySingleFacet::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushMesh4Base::AutoXMLPrint(ioOut);
    ioOut.TagSet("order");
    ioOut << m_order;
}
//%outOfLineFunctions } 6a+fJ4B+pHZCiyOIrfv58A
