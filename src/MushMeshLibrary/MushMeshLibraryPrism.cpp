//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryPrism.cpp
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
//%Header } KxO0L8VZ2TtpF4kp6s1grg
/*
 * $Id: MushMeshLibraryPrism.cpp,v 1.3 2007/04/18 09:22:53 southa Exp $
 * $Log: MushMeshLibraryPrism.cpp,v $
 * Revision 1.3  2007/04/18 09:22:53  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/08/01 17:21:35  southa
 * River demo
 *
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
