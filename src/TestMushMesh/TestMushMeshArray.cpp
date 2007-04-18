//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshArray.cpp
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
//%Header } WAo6CxAocoINCgdU3RP2Fg
/*
 * $Id: TestMushMeshArray.cpp,v 1.9 2006/06/01 15:40:01 southa Exp $
 * $Log: TestMushMeshArray.cpp,v $
 * Revision 1.9  2006/06/01 15:40:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/05 20:13:15  southa
 * Target and test updates
 *
 * Revision 1.6  2004/01/02 21:13:16  southa
 * Source conditioning
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
#include "TestMushMeshArray.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshArrayInstaller(TestMushMeshArray::Install);

void
TestMushMeshArray::ArrayVerify(const MushMeshArray<U32>& inArray, const string& inName)
{
    for (U32 x=0; x<kXMax; ++x)
    {
        for (U32 y=0; y<kYMax; ++y)
        {
            if (inArray.Get(x, y) != ValueFunction(x, y))
            {
                throw(MushcoreLogicFail(inName+" failed"));
            }
        }
    }
}

MushcoreScalar
TestMushMeshArray::TestArray(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
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
    MushMeshArray<U32> meshArray(kXMax, kYMax);

    for (U32 x=0; x<kXMax; ++x)
    {
        for (U32 y=0; y<kYMax; ++y)
        {
            meshArray.Set(ValueFunction(x, y), x, y);
        }
    }

    ArrayVerify(meshArray, "Readback");

    MushMeshArray<U32> destArray;

    destArray = meshArray;

    ArrayVerify(destArray, "Assignment");

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
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmesharray", TestArray);
}
