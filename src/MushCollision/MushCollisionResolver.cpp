//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionResolver.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } ymdD2Lh32YJKehH+HKSuAg
/*
 * $Id: MushCollisionResolver.cpp,v 1.5 2006/06/01 15:39:16 southa Exp $
 * $Log: MushCollisionResolver.cpp,v $
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
        tVal boundingRadius1 = meshRef1.ChunkBoundingRadius(i);
        
        for (U32 j=0; j<numChunks2; ++j)
        {
            tVal boundingRadius2 = meshRef2.ChunkBoundingRadius(j);
            
            tVal distanceSep = (centroidsRef1[i] - centroidsRef2[j]).Magnitude() - boundingRadius1 - boundingRadius2;
            if ((i == 0 && j == 0) || distanceSep < minDistanceSep)
            {
                minDistanceSep = distanceSep;
                chunkNum1 = i;
                chunkNum2 = j;
            }
#if 0
            cout << " +++sep=" << distanceSep;
            cout << ", cent1=" << centroidsRef1[i] << " radius " << boundingRadius1;
            cout << ", cent2=" << centroidsRef2[j] << " radius " << boundingRadius2;
            cout << endl;
#endif
                
        }
    }
    outCollInfo.SeparatingDistanceSet(minDistanceSep);
    outCollInfo.ChunkNum1Set(chunkNum1);
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
        // Object bounding spheres intersect, so perform the chunkwise test
        ChunkResolve(outCollInfo, inPiece1, inPiece2);
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
