//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMesh4Library.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 3FPaZkPeOCD2fVyuZWK2Lg
/*
 * $Id: TestMushMesh4Library.cpp,v 1.3 2005/07/02 00:42:39 southa Exp $
 * $Log: TestMushMesh4Library.cpp,v $
 * Revision 1.3  2005/07/02 00:42:39  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/30 12:34:59  southa
 * Mesh and source conditioner work
 *
 * Revision 1.1  2005/06/30 12:04:56  southa
 * Mesh work
 *
 */

#include "TestMushMesh4Library.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMesh4Library(TestMushMesh4Library::Install);

MushcoreScalar
TestMushMesh4Library::Test4Library(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{    
    MushMesh4Mesh mesh;
    
    MushMeshLibraryBase::Sgl().PolygonPrismCreate(mesh, t4Val(sqrt(2.0),sqrt(2.0),1,1), 4);
    //MushMeshLibraryBase::Sgl().UnitTesseractCreate(mesh);

    MushMeshLibraryFGenExtrude faceExtrude;
    MushMeshLibraryVGenExtrude vertexExtrude;
    
    MushMeshDisplacement disp(t4Val(0,0,0,-1), tQValPair::RotationIdentity(), 1);
    
    MushMeshLibraryExtrusionContext extrusionContext(disp, 0);
    
    extrusionContext.Reset();
    faceExtrude.FaceExtrude(mesh, extrusionContext, 1);
    extrusionContext.Reset();
    vertexExtrude.FaceExtrude(mesh, extrusionContext, 1);


    if (mesh.VertexCounter() != 24 || mesh.FaceCounter() != 15)
    {
        // 3*8 vertices, 8 faces for each tesseract but one face shared
        throw MushcoreCommandFail("Vertex or face counter fault");
    }
    
    if (mesh.Chunks().size() != 2)
    {
        throw MushcoreCommandFail("Chunk size fault");
    }
    
    if (mesh.ChunkBoundingRadius(0) < 0.99 || mesh.ChunkBoundingRadius(0) > 1.01 ||
        mesh.ChunkBoundingRadius(1) < 0.99 || mesh.ChunkBoundingRadius(1) > 1.01)
    {
        throw MushcoreCommandFail("Bounding radius fault");
    }
    
    if ((mesh.ChunkCentroid(0) - t4Val(0,0,0,0)).Magnitude() > 0.01 ||
        (mesh.ChunkCentroid(1) - t4Val(0,0,0,-1)).Magnitude() > 0.01)
    {
        throw MushcoreCommandFail("Chunk centroid fault");
    }
    
    if ((mesh.Centroid() - t4Val(0,0,0,-0.5)).Magnitude() > 0.01)
    {
        throw MushcoreCommandFail("Mesh centroid fault");
    }
    
    if (mesh.BoundingRadius() < 1.3 || mesh.BoundingRadius() > 1.35)
    {
        throw MushcoreCommandFail("Bounding radius fault");
    }
    
    if (mesh.NumConnections() != 52)
    {
        // 32 in each tesseract, and 12 are shared in the shared face
        throw MushcoreCommandFail("NumConnections fault");
    }
    
    mesh.Prebuild(); // Check that the prebuild completes

    // MushcoreLog::Sgl().XMLInfoLog() << mesh;   

    return MushcoreScalar(0);
}

void
TestMushMesh4Library::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmesh4library", Test4Library);
}
