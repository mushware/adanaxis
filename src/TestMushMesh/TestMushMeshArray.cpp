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
 * $Id: TestMushMeshArray.cpp,v 1.1 2003/10/15 07:08:29 southa Exp $
 * $Log: TestMushMeshArray.cpp,v $
 * Revision 1.1  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 */
#include "TestMushMeshArray.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshArrayInstaller(TestMushMeshArray::Install);

MushcoreScalar
TestMushMeshArray::TestArray(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    /* NonCyclicVertex corresponds to neighbours at the N positions below
     *
     * +---N---N
     * |   |   |
     * |   |   |
     * |   |   |
     * N---X---N
     * |   |   |
     * |   |   |
     * |   |   |
     * N---N---+
     */

    tNeighbourSpec NonCyclicVertex[] =
    {
        {0,0, 3, {{1,0}, {1,1}, {0,1}}},
        {0,1, 4, {{1,1}, {1,2}, {0,2}, {0,0}}},
        {1,0, 4, {{2,0}, {2,1}, {1,1}, {0,0}}},
        {1,1, 6, {{2,1}, {2,2}, {1,2}, {0,1}, {0,0}, {1,0}}},

        {0,3, 4, {{1,3}, {1,4}, {0,4}, {0,2}}},
        {0,4, 2, {{1,4}, {0,3}}},
        {1,3, 6, {{2,3}, {2,4}, {1,4}, {0,3}, {0,2}, {1,2}}},
        {1,4, 4, {{2,4}, {0,4}, {0,3}, {1,3}}},

        {2,3, 6, {{3,3}, {3,4}, {2,4}, {1,3}, {1,2}, {2,2}}},
        {2,4, 4, {{3,4}, {1,4}, {1,3}, {2,3}}},
        {3,3, 4, {{3,4}, {2,3}, {2,2}, {3,2}}},
        {3,4, 3, {{2,4}, {2,3}, {3,3}}},

        {2,0, 4, {{3,0}, {3,1}, {2,1}, {1,0}}},
        {2,1, 6, {{3,1}, {3,2}, {2,2}, {1,1}, {1,0}, {2,0}}},
        {3,0, 2, {{3,1}, {2,0}}},
        {3,1, 4, {{3,2}, {2,1}, {2,0}, {3,0}}}
    };
    
    enum
    {
        kXMax = 4,
        kYMax = 5
    };
    typedef MushMeshVector<tVal, 2> t2vecVal;
    // Basic operations
    MushMeshArray<U32> meshArray(kXMax, kYMax);

    for (U32 x=0; x<kXMax; ++x)
    {
        for (U32 y=0; y<kYMax; ++y)
        {
            meshArray.Set(ValueFunction(x, y), x, y);
        }
    }

    for (U32 x=0; x<kXMax; ++x)
    {
        for (U32 y=0; y<kYMax; ++y)
        {
            if (meshArray.Get(x, y) != ValueFunction(x, y))
            {
                throw(MushcoreLogicFail("MeshArray readback failed"));
            }
        }
    }

    MushwareValarray<const U32 *> verts(6);
    U32 numVerts;

    for (U32 i=0; i < sizeof(NonCyclicVertex) / sizeof(NonCyclicVertex[0]); ++i)
    {
        const tNeighbourSpec& nSpec = NonCyclicVertex[i];
        meshArray.VertexNeighboursGet(verts, numVerts, nSpec.x, nSpec.y);
        CheckNeighbours(nSpec, verts, numVerts, i);
    }
    return MushcoreScalar(0);
}

U32
TestMushMeshArray::ValueFunction(U32 inX, U32 inY)
{
    return inX+inY*10;
}

void
TestMushMeshArray::CheckNeighbours(const tNeighbourSpec& inSpec, const MushwareValarray<const U32 *>& inVerts,
                                   U32 inNumVerts, U32 inNumTest)
{
    if (inNumVerts != inSpec.numNeighbours)
    {
        ostringstream message;
        message << "Test " << inNumTest << ": Wrong number of neighbours (" << inNumVerts << ")";
        throw(MushcoreLogicFail(message.str()));
    }
    
    vector<bool> usedVert(6, false);
    vector<bool> usedNeighbour(6, false);

    for (U32 i=0; i<inNumVerts; ++i)
    {
        for (U32 j=0; j<inSpec.numNeighbours; j++)
        {
            if (!usedVert[i] && !usedNeighbour[j])
            {
                if (*inVerts[i] == ValueFunction(inSpec.neighbours[j].nx, inSpec.neighbours[j].ny))
                {
                     usedVert[i] = true;
                     usedNeighbour[j] = true;
                }
            }
        }
    }

    for (U32 i=0; i<inNumVerts; ++i)
    {
        if (!usedVert[i])
        {
            cout << "usedVert= " << usedVert << ", usedNeighbour= " << usedNeighbour << endl;
            ostringstream message;
            message << "Test " << inNumTest << ": Unused vertex (" << i << ", " << *inVerts[i] << ")";
            throw(MushcoreLogicFail(message.str()));
        }
    }
        
    for (U32 j=0; j<inSpec.numNeighbours; j++)
    {
        if (!usedNeighbour[j])
        {
           ostringstream message;
            message << "Test " << inNumTest << ": Unused neighbour (" << j << ")";
            throw(MushcoreLogicFail(message.str()));
        }
    }
}

void
TestMushMeshArray::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testarray", TestArray);
}
