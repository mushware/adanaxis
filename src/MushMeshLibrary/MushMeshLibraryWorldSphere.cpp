//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryWorldSphere.cpp
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
//%Header } 8mxa8BM45+YBl0BRtUMKFA
/*
 * $Id: MushMeshLibraryWorldSphere.cpp,v 1.2 2007/04/18 09:22:54 southa Exp $
 * $Log: MushMeshLibraryWorldSphere.cpp,v $
 * Revision 1.2  2007/04/18 09:22:54  southa
 * Header and level fixes
 *
 * Revision 1.1  2006/09/12 15:28:50  southa
 * World sphere
 *
 */

#include "MushMeshLibraryWorldSphere.h"

#include "MushMeshLibraryBase.h"

using namespace Mushware;
using namespace std;

void
MushMeshLibraryWorldSphere::Make(MushMesh4Mesh& ioMesh) const
{
    for (U32 i=0; i < NumFacets(); ++i)
    {
        MushMeshDisplacement disp = MushMeshDisplacement::Identity();
        tVal dist = 100;
        tQValPair orientation = MushMeshTools::RandomOrientation();
        
        disp.OffsetSet( dist * orientation.RotatedVector(t4Val(1,0,0,0)) );
        disp.RotationSet(orientation);
        
        MushMeshLibraryBase::Sgl().SingleFacetCreate(ioMesh, 4, disp);
    }
}

//%outOfLineFunctions {

const char *MushMeshLibraryWorldSphere::AutoName(void) const
{
    return "MushMeshLibraryWorldSphere";
}

MushcoreVirtualObject *MushMeshLibraryWorldSphere::AutoClone(void) const
{
    return new MushMeshLibraryWorldSphere(*this);
}

MushcoreVirtualObject *MushMeshLibraryWorldSphere::AutoCreate(void) const
{
    return new MushMeshLibraryWorldSphere;
}

MushcoreVirtualObject *MushMeshLibraryWorldSphere::AutoVirtualFactory(void)
{
    return new MushMeshLibraryWorldSphere;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMeshLibraryWorldSphere", MushMeshLibraryWorldSphere::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMeshLibraryWorldSphere::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushMesh4Base::AutoPrint(ioOut);
    ioOut << "numFacets=" << m_numFacets << ", ";
    ioOut << "tilesPerTexture=" << m_tilesPerTexture;
    ioOut << "]";
}
bool
MushMeshLibraryWorldSphere::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "numFacets")
    {
        ioIn >> m_numFacets;
    }
    else if (inTagStr == "tilesPerTexture")
    {
        ioIn >> m_tilesPerTexture;
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
MushMeshLibraryWorldSphere::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushMesh4Base::AutoXMLPrint(ioOut);
    ioOut.TagSet("numFacets");
    ioOut << m_numFacets;
    ioOut.TagSet("tilesPerTexture");
    ioOut << m_tilesPerTexture;
}
//%outOfLineFunctions } SXLCe3/YcLhJqWipfr+Uxw
