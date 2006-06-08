//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisMeshLibrary.cpp
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
//%Header } s/ATdwJmdoQd9jSw8sBfiA
/*
 * $Id: AdanaxisMeshLibrary.cpp,v 1.3 2006/05/03 00:58:43 southa Exp $
 * $Log: AdanaxisMeshLibrary.cpp,v $
 * Revision 1.3  2006/05/03 00:58:43  southa
 * Texturing updates
 *
 * Revision 1.2  2005/09/05 12:54:29  southa
 * Solid rendering work
 *
 * Revision 1.1  2005/07/18 13:13:35  southa
 * Extrude to point and projectile mesh
 *
 */

#include "AdanaxisMeshLibrary.h"

using namespace Mushware;
using namespace std;

void
AdanaxisMeshLibrary::TesseractCreate(MushMesh4Mesh& ioMesh) const
{
    MushMeshLibraryBase::Sgl().PolygonPrismCreate(ioMesh, t4Val(1, 1, 1, 1), 4);
}

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

void
AdanaxisMeshLibrary::AttendantExtrusionContext(MushMeshLibraryExtrusionContext& outContext, const MushMesh4Mesh& inMesh, Mushware::tVal inAnim) const
{
    U32 number = kAttendantLODFactor * inMesh.LevelOfDetail();
    
    MushMeshDisplacement disp(t4Val(0,0,0,1), tQValPair::RotationIdentity(), 0.5);
    t4Val offset(0,0,0,-1);

    disp.RotationWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                        (1, inAnim*M_PI/number));
    MushMeshTools::QuaternionRotateInAxis(1, 0.5*inAnim*M_PI/number).VectorRotate(offset);
    disp.OffsetSet(offset);
    outContext.DispSet(disp);
    outContext.ScaleVelocitySet(1.0/number);    
}    

void
AdanaxisMeshLibrary::AttendantVerticesSet(MushMesh4Mesh& ioMesh, tVal inAnim) const
{
    U32 number = kAttendantLODFactor * ioMesh.LevelOfDetail();

    MushMeshLibraryExtrusionContext extrusionContext;
    AttendantExtrusionContext(extrusionContext, ioMesh, inAnim);
    
    MushMeshLibraryVGenExtrude vertexExtrude;
    extrusionContext.ResetNewFace(0);
    vertexExtrude.FaceExtrude(ioMesh, extrusionContext, number);
    MushMeshDisplacement disp = extrusionContext.Disp();
    disp.OffsetWRef().InPlaceElementwiseMultiply(t4Val(1,1,1,-1)); // Reverse W direction
    disp.RotationSet(disp.Rotation().Conjugate()); // Reverse rotation
    extrusionContext.ResetNewDispFace(disp, 1);
    vertexExtrude.FaceExtrude(ioMesh, extrusionContext, number);
}    

void
AdanaxisMeshLibrary::AttendantCreate(MushMesh4Mesh& ioMesh) const
{
    U32 number = kAttendantLODFactor * ioMesh.LevelOfDetail();

    MushMeshLibraryExtrusionContext extrusionContext;
    AttendantExtrusionContext(extrusionContext, ioMesh, 1.0);

    MushMeshLibraryFGenExtrude faceExtrude;
    
    MushMeshLibraryBase::Sgl().PolygonPrismCreate(ioMesh, t4Val(1,1,1,1), number);            

    extrusionContext.ResetNewFace(0);
    faceExtrude.FaceExtrude(ioMesh, extrusionContext, number);
    extrusionContext.ResetNewFace(1);
    faceExtrude.FaceExtrude(ioMesh, extrusionContext, number);
    
    AttendantVerticesSet(ioMesh, 1.0);
}    

void
AdanaxisMeshLibrary::TestObjectExtrusionContext(MushMeshLibraryExtrusionContext& outContext, const MushMesh4Mesh& inMesh, Mushware::tVal inAnim) const
{
    U32 number = 1;
    
    MushMeshDisplacement disp(t4Val(0,0,0,-5), tQValPair::RotationIdentity(), 0.5);
	
    //disp.RotationWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(1, 0));
    //MushMeshTools::QuaternionRotateInAxis(1, 0).VectorRotate(offset);
    outContext.DispSet(disp);
    outContext.ScaleVelocitySet(1.0);    
}    

void
AdanaxisMeshLibrary::TestObjectVerticesSet(MushMesh4Mesh& ioMesh, tVal inAnim) const
{
    U32 number = 1;
	
    MushMeshLibraryExtrusionContext extrusionContext;
    TestObjectExtrusionContext(extrusionContext, ioMesh, inAnim);
    
    MushMeshLibraryVGenExtrude vertexExtrude;
    extrusionContext.ResetNewFace(0);
    vertexExtrude.FaceExtrude(ioMesh, extrusionContext, number);
}    

void
AdanaxisMeshLibrary::TestObjectCreate(MushMesh4Mesh& ioMesh) const
{
    MushMeshLibraryExtrusionContext extrusionContext;
    TestObjectExtrusionContext(extrusionContext, ioMesh, 1.0);
	
    MushMeshLibraryFGenExtrude faceExtrude;
    
    MushMeshLibraryBase::Sgl().PolygonPrismCreate(ioMesh, t4Val(2,2,2,2), 4);            
	
    extrusionContext.ResetNewFace(0);
    faceExtrude.FaceExtrude(ioMesh, extrusionContext, 1);
	
#if 0
    extrusionContext.ResetNewFace(1);
    faceExtrude.FaceExtrude(ioMesh, extrusionContext, number);
#endif
	
    TestObjectVerticesSet(ioMesh, 1.0);
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
