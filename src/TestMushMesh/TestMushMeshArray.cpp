//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshArray.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } R8QEHD8pK6fOXGrE7cqcdg
/*
 * $Id$
 * $Log$
 */
#include "TestMushMeshArray.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshArrayInstaller(TestMushMeshArray::Install);

MushcoreScalar
TestMushMeshArray::TestArray(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    enum
    {
        kXMax = 3,
        kYMax = 4
    };
    typedef MushMeshVector<tVal, 2> t2vecVal;
    // Basic operations
    MushMeshArray<U32> meshArray(kXMax, kYMax);

    for (U32 x=0; x<3; ++x)
    {
        for (U32 y=0; y<4; ++y)
        {
            meshArray.Set(x+5*y, x, y);
        }
    }

    for (U32 x=0; x<3; ++x)
    {
        for (U32 y=0; y<4; ++y)
        {
            if (meshArray.Get(x, y) != x+5*y)
            {
                throw(MushcoreLogicFail("MeshArray readback failed"));
            }
        }
    }

    MushwareValarray<const U32 *> verts(6);
    U32 numVerts;
    meshArray.VertexNeighboursGet(verts, numVerts, 0, 0);
    if (numVerts != 3)
    {
        throw(MushcoreLogicFail("VertexNeighboursGet return wrong number (1)"));
    }
    meshArray.VertexNeighboursGet(verts, numVerts, 1, 0);
    if (numVerts != 4)
    {
         cout << "numVerts=" << numVerts << endl;
         throw(MushcoreLogicFail("VertexNeighboursGet return wrong number (2)"));
    }
    meshArray.VertexNeighboursGet(verts, numVerts, 0, 1);
    if (numVerts != 4)
    {
        throw(MushcoreLogicFail("VertexNeighboursGet return wrong number (3)"));
    }
    meshArray.VertexNeighboursGet(verts, numVerts, 1, 1);
    if (numVerts != 6)
    {
        throw(MushcoreLogicFail("VertexNeighboursGet return wrong number (4)"));
    }
    meshArray.VertexNeighboursGet(verts, numVerts, kXMax, 0);
    if (numVerts != 2)
    {
        throw(MushcoreLogicFail("VertexNeighboursGet return wrong number (5)"));
    }
    meshArray.VertexNeighboursGet(verts, numVerts, kXMax, 1);
    if (numVerts != 4)
    {
        throw(MushcoreLogicFail("VertexNeighboursGet return wrong number (6)"));
    }
    meshArray.VertexNeighboursGet(verts, numVerts, 0, kYMax);
    if (numVerts != 2)
    {
        throw(MushcoreLogicFail("VertexNeighboursGet return wrong number (7)"));
    }
    meshArray.VertexNeighboursGet(verts, numVerts, 1, kYMax);
    if (numVerts != 4)
    {
        throw(MushcoreLogicFail("VertexNeighboursGet return wrong number (8)"));
    }
    meshArray.VertexNeighboursGet(verts, numVerts, kXMax, kYMax);
    if (numVerts != 3)
    {
        throw(MushcoreLogicFail("VertexNeighboursGet return wrong number (9)"));
    }
}

void
TestMushMeshArray::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testarray", TestArray);
}
