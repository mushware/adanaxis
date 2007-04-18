//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryWorldSphere.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Ly9mskV0FJ8rvrZ/7FLCMA
/*
 * $Id: MushMeshLibraryWorldSphere.cpp,v 1.1 2006/09/12 15:28:50 southa Exp $
 * $Log: MushMeshLibraryWorldSphere.cpp,v $
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
