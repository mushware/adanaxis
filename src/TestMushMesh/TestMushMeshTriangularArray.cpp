//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshTriangularArray.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } I5PPNMg6sviaX01QxvfPlA
/*
 * $Id: TestMushMeshTriangularArray.cpp,v 1.1 2003/10/23 20:03:58 southa Exp $
 * $Log: TestMushMeshTriangularArray.cpp,v $
 * Revision 1.1  2003/10/23 20:03:58  southa
 * End mesh work
 *
 * Revision 1.5  2003/10/20 13:02:54  southa
 * Patch fixes and testing
 *
 * Revision 1.4  2003/10/17 19:33:11  southa
 * Mesh patches
 *
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
#include "TestMushMeshTriangularArray.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshTriangularArrayInstaller(TestMushMeshTriangularArray::Install);

void
TestMushMeshTriangularArray::ArrayVerify(const MushMeshTriangularArray<U32>& inArray, const string& inName)
{
    for (U32 x=0; x<kXMax; ++x)
    {
        for (U32 y=0; y<x*kOrder; ++y)
        {
            if (inArray.Get(x, y) != ValueFunction(x, y))
            {
                cout << endl << "Failed array = " << inArray << endl;
                throw(MushcoreLogicFail(inName+" failed"));
            }
        }
    }
}

MushcoreScalar
TestMushMeshTriangularArray::TestTriangularArray(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    // Check valarray assignment
    typedef MushwareValarray<U32> tValarray;
    tValarray srcValarray;

    srcValarray.resize(1);
    srcValarray[0] = 3;

    {
        tValarray destValarray;
        destValarray = srcValarray;
        if (destValarray.size() != srcValarray.size() ||
            destValarray[0] != srcValarray[0])
        {
#ifdef HAVE_RESIZING_VALARRAY_ASSIGNMENT
            throw MushcoreLogicFail("Resizing valarray assignment doesn't work, but HAVE_RESIZING_VALARRAY_ASSIGNMENT is #defined");
#endif
        }
    }

    // Basic operations
    MushMeshTriangularArray<U32> meshArray(kXMax, kOrder);

    for (U32 x=0; x<kXMax; ++x)
    {
        for (U32 y=0; y<x*kOrder; ++y)
        {
            meshArray.Set(ValueFunction(x, y), x, y);
        }
    }
    
    // cout << endl << meshArray;
    
    ArrayVerify(meshArray, "Readback");

    MushMeshTriangularArray<U32> destArray;

    destArray = meshArray;

    ArrayVerify(destArray, "Assignment");

    return MushcoreScalar(0);
}

U32
TestMushMeshTriangularArray::ValueFunction(U32 inX, U32 inY)
{
    return inX+inY*10;
}

void
TestMushMeshTriangularArray::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testtriangulararray", TestTriangularArray);
}
