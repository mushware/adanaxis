//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionResolver.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } 1uefOWcKCDY4W2xTWkEYpg
/*
 * $Id: MushCollisionResolver.cpp,v 1.8 2007/03/21 11:56:06 southa Exp $
 * $Log: MushCollisionResolver.cpp,v $
 * Revision 1.8  2007/03/21 11:56:06  southa
 * Rail effects and damage icons
 *
 * Revision 1.7  2006/11/14 20:28:37  southa
 * Added rail gun
 *
 * Revision 1.6  2006/10/12 22:04:48  southa
 * Collision events
 *
 * Revision 1.5  2006/06/01 15:39:16  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 * Revision 1.3  2005/07/30 19:06:14  southa
 * Collision checking
 *
 * Revision 1.2  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.1  2005/07/27 18:09:59  southa
 * Collision checking
 *
 */

#include "MushCollisionResolver.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushCollisionResolver);

void
MushCollisionResolver::ChunkResolve(MushCollisionInfo& outCollInfo, const MushCollisionPiece& inPiece1, const MushCollisionPiece& inPiece2) const
{
    const MushMesh4Mesh& meshRef1 = inPiece1.CollisionMesh();
    const MushMesh4Mesh& meshRef2 = inPiece2.CollisionMesh();
    const MushMesh4Mesh::tChunks& chunksRef1 = meshRef1.Chunks();
    const MushMesh4Mesh::tChunks& chunksRef2 = meshRef2.Chunks();
    const MushCollisionWorkspace::tChunkCentroids& centroidsRef1 = inPiece1.CollisionChunkWorldCentroids();
    const MushCollisionWorkspace::tChunkCentroids& centroidsRef2 = inPiece2.CollisionChunkWorldCentroids();
    
    U32 numChunks1 = chunksRef1.size();
    U32 numChunks2 = chunksRef2.size();
    
    tVal minDistanceSep = 1;
    U32 chunkNum1 = 0;
    U32 chunkNum2 = 0;
    
    for (U32 i=0; i<numChunks1; ++i)
    {
        tVal boundingRadius1 = meshRef1.ChunkBoundingRadius(i) * inPiece1.ShrinkFactor();
        
        for (U32 j=0; j<numChunks2; ++j)
        {
            tVal boundingRadius2 = meshRef2.ChunkBoundingRadius(j) * inPiece2.ShrinkFactor();
            
            tVal distanceSep = (centroidsRef1[i] - centroidsRef2[j]).Magnitude() - boundingRadius1 - boundingRadius2;
            if ((i == 0 && j == 0) || distanceSep < minDistanceSep)
            {
                minDistanceSep = distanceSep;
                chunkNum1 = i;
                chunkNum2 = j;
            }                
        }
    }
    outCollInfo.SeparatingDistanceSet(minDistanceSep);
    outCollInfo.ChunkNum1Set(chunkNum1);
    outCollInfo.ChunkNum2Set(chunkNum2);
    outCollInfo.ChunkNumsValidSet(true);
    outCollInfo.ObjectPointersValidSet(false);
}

void
MushCollisionResolver::WCylinderResolve(MushCollisionInfo& outCollInfo, const MushCollisionPiece& inPiece1, const MushCollisionPiece& inPiece2) const
{
    const MushMesh4Mesh& meshRef2 = inPiece2.CollisionMesh();
    const MushMesh4Mesh::tChunks& chunksRef2 = meshRef2.Chunks();
    const MushCollisionWorkspace::tChunkCentroids& centroidsRef1 = inPiece1.CollisionChunkWorldCentroids();
    const MushCollisionWorkspace::tChunkCentroids& centroidsRef2 = inPiece2.CollisionChunkWorldCentroids();
    
    U32 numChunks2 = chunksRef2.size();
    
    tVal minDistanceSep = 1;
    U32 chunkNum2 = 0;
    
    for (U32 j=0; j<numChunks2; ++j)
    {
        tVal boundingRadius2 = meshRef2.ChunkBoundingRadius(j) * inPiece2.ShrinkFactor();
        t4Val vecSep = centroidsRef1[0] - centroidsRef2[j];

        inPiece1.CollisionPost().AngPos().Conjugate().VectorRotate(vecSep);

        vecSep.WSet(0);
        
        tVal distanceSep = vecSep.Magnitude() - boundingRadius2 - 1.0; // 1.0 is generosity margin
        
        if ((j == 0) || distanceSep < minDistanceSep)
        {
            minDistanceSep = distanceSep;
            chunkNum2 = j;
        }                
    }
    
    // Recalculate the point of contact with the nearest chunk
    if (numChunks2 > 0)
    {
        // Bring centroidRef2 onto the axis of the cylinder
        t4Val pointVec = centroidsRef2[chunkNum2] - centroidsRef1[0];
        inPiece1.CollisionPost().AngPos().Conjugate().VectorRotate(pointVec);
        // pointVec now in cylinder object space
        pointVec.XSet(0);
        pointVec.YSet(0);
        pointVec.ZSet(0);
        inPiece1.CollisionPost().AngPos().VectorRotate(pointVec);
        pointVec += centroidsRef1[0];
        
        outCollInfo.CollisionPointSet(pointVec);
        outCollInfo.CollisionPointValidSet(true);
    }
    
    outCollInfo.SeparatingDistanceSet(minDistanceSep);
    outCollInfo.ChunkNum1Set(0);
    outCollInfo.ChunkNum2Set(chunkNum2);
    outCollInfo.ChunkNumsValidSet(true);
    outCollInfo.ObjectPointersValidSet(false);
}

void
MushCollisionResolver::Resolve(MushCollisionInfo& outCollInfo, const MushCollisionPiece& inPiece1, const MushCollisionPiece& inPiece2) const
{
    inPiece1.CollisionResetIfNeeded(FrameMsec());
    inPiece2.CollisionResetIfNeeded(FrameMsec());
    t4Val centroidSepVec = inPiece1.CollisionWorldCentroid() - inPiece2.CollisionWorldCentroid();
    tVal centroidSep = centroidSepVec.Magnitude();
    tVal distanceSep = centroidSep - inPiece1.CollisionBoundingRadius() - inPiece2.CollisionBoundingRadius();
    
    if (distanceSep > 0)
    {
        // Object bounding spheres not intersecting
        outCollInfo.SeparatingDistanceSet(distanceSep);
        outCollInfo.ChunkNumsValidSet(false);
    }
    else
    {
        if (inPiece1.CollisionIsWCylinder())
        {
            WCylinderResolve(outCollInfo, inPiece1, inPiece2);
        }
        else if (inPiece2.CollisionIsWCylinder())
        {
            throw MushcoreLogicFail("Cannot resolve WCylinder in piece2");   
        }
        else
        {
            // Object bounding spheres intersect, so perform the chunkwise test
            ChunkResolve(outCollInfo, inPiece1, inPiece2);
        }
    }
}



//%outOfLineFunctions {

const char *MushCollisionResolver::AutoName(void) const
{
    return "MushCollisionResolver";
}

MushcoreVirtualObject *MushCollisionResolver::AutoClone(void) const
{
    return new MushCollisionResolver(*this);
}

MushcoreVirtualObject *MushCollisionResolver::AutoCreate(void) const
{
    return new MushCollisionResolver;
}

MushcoreVirtualObject *MushCollisionResolver::AutoVirtualFactory(void)
{
    return new MushCollisionResolver;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushCollisionResolver", MushCollisionResolver::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushCollisionResolver::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "frameMsec=" << m_frameMsec;
    ioOut << "]";
}
bool
MushCollisionResolver::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "frameMsec")
    {
        ioIn >> m_frameMsec;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushCollisionResolver::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("frameMsec");
    ioOut << m_frameMsec;
}
//%outOfLineFunctions } Wu3J/g5sj6Eo9u+Jjy0hSw
