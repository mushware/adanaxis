//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionPiece.cpp
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
//%Header } TVLK6jjs4aga+MLw2NyBqQ
/*
 * $Id: MushCollisionPiece.cpp,v 1.6 2007/04/18 09:22:30 southa Exp $
 * $Log: MushCollisionPiece.cpp,v $
 * Revision 1.6  2007/04/18 09:22:30  southa
 * Header and level fixes
 *
 * Revision 1.5  2006/11/14 20:28:37  southa
 * Added rail gun
 *
 * Revision 1.4  2006/06/01 15:39:15  southa
 * DrawArray verification and fixes
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

#include "MushCollisionPiece.h"

using namespace Mushware;
using namespace std;

const MushMesh4Mesh&
MushCollisionPiece::CollisionMesh(void) const
{
    throw MushcoreDataFail(std::string("Request for collision mesh unsupported for type '")+AutoName()+"'");
}

const MushMeshPosticity&
MushCollisionPiece::CollisionPost(void) const
{
    throw MushcoreDataFail(std::string("Request for collision post unsupported for type '")+AutoName()+"'");
}

bool
MushCollisionPiece::CollisionIsWCylinder(void) const
{
    return false;
}

void
MushCollisionPiece::CollisionChunkWorldCentroidsBuild(void) const
{
    const MushMesh4Mesh& meshRef = CollisionMesh();
    const MushMesh4Mesh::tChunks& chunksRef = meshRef.Chunks();
    MushCollisionWorkspace::tChunkCentroids& centroidsRef = m_collSpace.ChunkCentroidsWRef();
    
    U32 numChunks = chunksRef.size();
    if (centroidsRef.size() != numChunks)
    {
        centroidsRef.resize(numChunks);
    }
    
    const MushMeshPosticity& postRef = CollisionPost();
    for (U32 i=0; i<numChunks; ++i)
    {
        centroidsRef[i] = meshRef.ChunkCentroid(i);
        MushMeshOps::ObjectToWorld(centroidsRef[i], postRef);
    }
    m_collSpace.ChunkCentroidsValidSet(true);
}

//%outOfLineFunctions {

const char *MushCollisionPiece::AutoName(void) const
{
    return "MushCollisionPiece";
}

MushcoreVirtualObject *MushCollisionPiece::AutoClone(void) const
{
    return new MushCollisionPiece(*this);
}

MushcoreVirtualObject *MushCollisionPiece::AutoCreate(void) const
{
    return new MushCollisionPiece;
}

MushcoreVirtualObject *MushCollisionPiece::AutoVirtualFactory(void)
{
    return new MushCollisionPiece;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushCollisionPiece", MushCollisionPiece::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushCollisionPiece::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "shrinkFactor=" << m_shrinkFactor << ", ";
    ioOut << "collSpace=" << m_collSpace;
    ioOut << "]";
}
bool
MushCollisionPiece::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "shrinkFactor")
    {
        ioIn >> m_shrinkFactor;
    }
    else if (inTagStr == "collSpace")
    {
        ioIn >> m_collSpace;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushCollisionPiece::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("shrinkFactor");
    ioOut << m_shrinkFactor;
    ioOut.TagSet("collSpace");
    ioOut << m_collSpace;
}
//%outOfLineFunctions } 1S2V/lUZGZVaV3r7yu08mQ
