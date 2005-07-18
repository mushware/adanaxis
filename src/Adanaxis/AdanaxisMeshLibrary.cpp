//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisMeshLibrary.cpp
 *
 * Copyright: Andy Southgate 2005
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
//%Header } HZgJeg4wxB1Uq93YJryJDg
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisMeshLibrary.h"

using namespace Mushware;
using namespace std;

void
AdanaxisMeshLibrary::ProjectileCreate(MushMesh4Mesh& ioMesh) const
{
    U32 levelOfDetail = 5;
    MushMeshLibraryBase::Sgl().PolygonPrismCreate(ioMesh, t4Val(0.25,0.25,0.20,1), levelOfDetail);
    
    MushMeshLibraryFGenExtrude faceExtrude;
    MushMeshLibraryVGenExtrude vertexExtrude;

    MushMeshDisplacement disp(t4Val(0,0,0,-1), tQValPair::RotationIdentity(), 0);
    
    MushMeshLibraryExtrusionContext extrusionContext(disp, 0);
    
    extrusionContext.Reset();
    faceExtrude.FaceExtrude(ioMesh, extrusionContext, 1);
    extrusionContext.Reset();
    vertexExtrude.FaceExtrude(ioMesh, extrusionContext, 1);
}

//%outOfLineFunctions {

const char *AdanaxisMeshLibrary::AutoName(void) const
{
    return "AdanaxisMeshLibrary";
}

MushcoreVirtualObject *AdanaxisMeshLibrary::AutoClone(void) const
{
    return new AdanaxisMeshLibrary(*this);
}

MushcoreVirtualObject *AdanaxisMeshLibrary::AutoCreate(void) const
{
    return new AdanaxisMeshLibrary;
}

MushcoreVirtualObject *AdanaxisMeshLibrary::AutoVirtualFactory(void)
{
    return new AdanaxisMeshLibrary;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisMeshLibrary", AdanaxisMeshLibrary::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisMeshLibrary::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushMeshLibraryBase::AutoPrint(ioOut);
    ioOut << "]";
}
bool
AdanaxisMeshLibrary::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushMeshLibraryBase::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisMeshLibrary::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushMeshLibraryBase::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } ZaVHpe+5bhFscJeBx5nHGw
