//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibrarySingleFacet.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } C+iG5Gx4HYZHOkIzomeyfw
/*
 * $Id: MushMeshLibrarySingleFacet.cpp,v 1.4 2007/04/18 09:22:54 southa Exp $
 * $Log: MushMeshLibrarySingleFacet.cpp,v $
 * Revision 1.4  2007/04/18 09:22:54  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/09/12 15:28:50  southa
 * World sphere
 *
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
