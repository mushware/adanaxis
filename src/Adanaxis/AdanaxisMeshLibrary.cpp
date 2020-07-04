//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisMeshLibrary.cpp
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
//%Header } NDO/UzTuMs1ff7PqDDlD4w
/*
 * $Id: AdanaxisMeshLibrary.cpp,v 1.8 2007/04/18 09:22:01 southa Exp $
 * $Log: AdanaxisMeshLibrary.cpp,v $
 * Revision 1.8  2007/04/18 09:22:01  southa
 * Header and level fixes
 *
 * Revision 1.7  2006/08/01 17:21:24  southa
 * River demo
 *
 * Revision 1.6  2006/06/14 18:45:46  southa
 * Ruby mesh generation
 *
 * Revision 1.5  2006/06/09 21:07:12  southa
 * Tiled skin generation
 *
 * Revision 1.4  2006/06/08 20:17:30  southa
 * Texture tile generation method 2
 *
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

    MushMeshDisplacement disp(t4Val(0,0,0,-1), tQValPair::RotationIdentity(), t4Val(0,0,0,0));
    
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
    
    MushMeshDisplacement disp(t4Val(0,0,0,1), tQValPair::RotationIdentity(), t4Val(0.5,0.5,0.5,0.5));
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
    
    AttendantVerticesSet(ioMesh, 1);
}

void
AdanaxisMeshLibrary::TestObjectExtrusionContext(MushMeshLibraryExtrusionContext& outContext, const MushMesh4Mesh& inMesh, Mushware::tVal inAnim) const
{
    MushMeshDisplacement disp(t4Val(0,0,0,-5), tQValPair::RotationIdentity(), t4Val(0.5, 0.5, 0.5, 0.5));
	
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
    
    MushMeshLibraryBase::Sgl().PolygonPrismCreate(ioMesh, t4Val(2,2,2,2), 5);            
	
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
