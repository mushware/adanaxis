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
 * $Id: TestMushMeshArray.cpp,v 1.3 2003/10/15 12:23:10 southa Exp $
 * $Log: TestMushMeshArray.cpp,v $
 * Revision 1.3  2003/10/15 12:23:10  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.2  2003/10/15 11:54:54  southa
 * MushMeshArray neighbour testing and subdivision
 *
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

    return MushcoreScalar(0);
}

U32
TestMushMeshArray::ValueFunction(U32 inX, U32 inY)
{
    return inX+inY*10;
}

void
TestMushMeshArray::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testarray", TestArray);
}
