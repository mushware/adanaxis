//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshSubdivide.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } raybvYJ6HiKtjntHFaNDHg
/*
 * $Id: TestMushMeshSubdivide.cpp,v 1.3 2003/10/17 12:27:20 southa Exp $
 * $Log: TestMushMeshSubdivide.cpp,v $
 * Revision 1.3  2003/10/17 12:27:20  southa
 * Line end fixes and more mesh work
 *
 * Revision 1.2  2003/10/15 12:27:00  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.1  2003/10/15 11:54:54  southa
 * MushMeshArray neighbour testing and subdivision
 *
 */
#include "TestMushMeshSubdivide.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshSubdivideInstaller(TestMushMeshSubdivide::Install);

MushcoreScalar
TestMushMeshSubdivide::TestSubdivide(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
#if 0
    enum
    {
        kXMax = 3,
        kYMax = 4
    };
    MushMeshArray<tVal> meshArray(kXMax, kYMax);

    for (U32 x=0; x<3; ++x)
    {
        for (U32 y=0; y<4; ++y)
        {
            meshArray.Set(x+5*y, x, y);
        }
    }
    MushMeshArray<tVal> movedArray(kXMax, kYMax);
    MushMeshSubdivide<tVal>::Move(movedArray, meshArray, 0);
    if (movedArray != meshArray)
    {
        throw MushcoreLogicFail("Move of proportion 0 does not copy array");
    }
    MushMeshSubdivide<tVal>::Move(movedArray, meshArray, 1);
    if (movedArray == meshArray)
    {
        throw MushcoreLogicFail("Move of proportion 1 just copies array");
    }

    MushMeshArray<tVal> subbedArray(kXMax*2, kYMax*2);
    MushMeshSubdivide<tVal>::Subdivide(subbedArray, meshArray, 0);
    
    cout << "Orig mesh = " << meshArray << endl;
    cout << "Moved mesh = " << subbedArray << endl;
#endif
    return MushcoreScalar(0);
}

void
TestMushMeshSubdivide::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testsubdivide", TestSubdivide);
}
