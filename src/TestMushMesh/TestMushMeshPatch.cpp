//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPatch.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } jDg4bI5jmVKXjT+HJt+gYg
/*
 * $Id$
 * $Log$
 */


#include "TestMushMeshPatch.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshPatchInstaller(TestMushMeshPatch::Install);

void
TestMushMeshPatch::GeometryPrint(const tGeometryArray& inArray)
{
    for (U32 y=inArray.SizeGet().Y(); y>0;)
    {
        --y;
        cout << "[";
        for (U32 x=0; x<inArray.SizeGet().X(); ++x)
        {
            cout << inArray.Get(x, y).X();
            if (x+1 != inArray.SizeGet().X())
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
}

bool
TestMushMeshPatch::ChangeVerify(const Mushware::tGeometryArray& inArray1,
                                const Mushware::tGeometryArray& inArray2,
                                Mushware::U32 inChanges)
{
    U32 changes = 0;
    for (U32 x=0; x<kXMax; ++x)
    {
        for (U32 y=0; y<kYMax; ++y)
        {
            if (inArray1.Get(x,y)[0] != inArray2.Get(x,y)[0])
            {
                changes++;
            }
        }
    }
    if (changes != inChanges)
    {
        cout << "Wrong number of changes: " << changes << " should be " << inChanges << endl;
        return false;
    }
    return true;
}

MushcoreScalar
TestMushMeshPatch::TestPatch(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    auto_ptr<MushMeshPatchPipe> pPipe1(new MushMeshPatchPipe);
    auto_ptr<MushMeshPatchPipe> pPipe2(new MushMeshPatchPipe);

    Mushware::tGeometryArray array1;
    Mushware::tGeometryArray array2;

    array1.SizeSet(t2U32(kXMax, kYMax));
    array2.SizeSet(t2U32(kXMax, kYMax));

    for (U32 x=0; x<kXMax; ++x)
    {
        for (U32 y=0; y<kYMax; ++y)
        {
            tVal testValue = x + y*10;
            array1.Set(tGeometryVector(100+testValue), x, y);
            array2.Set(tGeometryVector(200+testValue), x, y);
        }
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);

    MushMeshConnector conEdgeLeft(*pPipe1, MushMeshPatch::kEdgeLeft, *pPipe2, MushMeshPatch::kEdgeLeft);
    MushMeshConnector conEdgeRight(*pPipe1, MushMeshPatch::kEdgeRight, *pPipe2, MushMeshPatch::kEdgeRight);
    MushMeshConnector conEdgeBottom(*pPipe1, MushMeshPatch::kEdgeBottom, *pPipe2, MushMeshPatch::kEdgeBottom);
    MushMeshConnector conEdgeTop(*pPipe1, MushMeshPatch::kEdgeTop, *pPipe2, MushMeshPatch::kEdgeTop);
    MushMeshConnector conBottomLeft(*pPipe1, MushMeshPatch::kPointBottomLeft, *pPipe2, MushMeshPatch::kPointBottomLeft);
    MushMeshConnector conBottomRight(*pPipe1, MushMeshPatch::kPointBottomRight, *pPipe2, MushMeshPatch::kPointBottomRight);
    MushMeshConnector conTopLeft(*pPipe1, MushMeshPatch::kPointTopLeft, *pPipe2, MushMeshPatch::kPointTopLeft);
    MushMeshConnector conTopRight(*pPipe1, MushMeshPatch::kPointTopRight, *pPipe2, MushMeshPatch::kPointTopRight);

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conEdgeLeft.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(0,1)[0] != array2.Get(1,1)[0] ||
        pPipe1->GeometryGet().Get(0,2)[0] != array2.Get(1,2)[0] ||
        pPipe1->GeometryGet().Get(0,3)[0] != array2.Get(1,3)[0] ||
        pPipe1->GeometryGet().Get(0,4)[0] != array2.Get(1,4)[0] ||
        pPipe2->GeometryGet().Get(0,1)[0] != array1.Get(1,1)[0] ||
        pPipe2->GeometryGet().Get(0,2)[0] != array1.Get(1,2)[0] ||
        pPipe2->GeometryGet().Get(0,3)[0] != array1.Get(1,3)[0] ||
        pPipe2->GeometryGet().Get(0,4)[0] != array1.Get(1,4)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 4) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 4))
    {
        cout << "Patch 1 = " << endl;
        GeometryPrint(pPipe1->GeometryGet());
        cout << "Patch 2 = " << endl;
        GeometryPrint(pPipe2->GeometryGet());
        throw MushcoreLogicFail("Left edge update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conEdgeRight.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(4,1)[0] != array2.Get(3,1)[0] ||
        pPipe1->GeometryGet().Get(4,2)[0] != array2.Get(3,2)[0] ||
        pPipe1->GeometryGet().Get(4,3)[0] != array2.Get(3,3)[0] ||
        pPipe1->GeometryGet().Get(4,4)[0] != array2.Get(3,4)[0] ||
        pPipe2->GeometryGet().Get(4,1)[0] != array1.Get(3,1)[0] ||
        pPipe2->GeometryGet().Get(4,2)[0] != array1.Get(3,2)[0] ||
        pPipe2->GeometryGet().Get(4,3)[0] != array1.Get(3,3)[0] ||
        pPipe2->GeometryGet().Get(4,4)[0] != array1.Get(3,4)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 4) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 4))
    {
        throw MushcoreLogicFail("Right edge update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conEdgeBottom.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(1,0)[0] != array2.Get(1,1)[0] ||
        pPipe1->GeometryGet().Get(2,0)[0] != array2.Get(2,1)[0] ||
        pPipe1->GeometryGet().Get(3,0)[0] != array2.Get(3,1)[0] ||
        pPipe2->GeometryGet().Get(1,0)[0] != array1.Get(1,1)[0] ||
        pPipe2->GeometryGet().Get(2,0)[0] != array1.Get(2,1)[0] ||
        pPipe2->GeometryGet().Get(3,0)[0] != array1.Get(3,1)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 3) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 3))
    {
        throw MushcoreLogicFail("Bottom edge update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conEdgeTop.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(1,5)[0] != array2.Get(1,4)[0] ||
        pPipe1->GeometryGet().Get(2,5)[0] != array2.Get(2,4)[0] ||
        pPipe1->GeometryGet().Get(3,5)[0] != array2.Get(3,4)[0] ||
        pPipe2->GeometryGet().Get(1,5)[0] != array1.Get(1,4)[0] ||
        pPipe2->GeometryGet().Get(2,5)[0] != array1.Get(2,4)[0] ||
        pPipe2->GeometryGet().Get(3,5)[0] != array1.Get(3,4)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 3) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 3))
    {
        throw MushcoreLogicFail("Top edge update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conBottomLeft.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(0,0)[0] != array2.Get(1,1)[0] ||
        pPipe2->GeometryGet().Get(0,0)[0] != array1.Get(1,1)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 1) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 1))
    {
        throw MushcoreLogicFail("Bottom left corner update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conBottomRight.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(4,0)[0] != array2.Get(3,1)[0] ||
        pPipe2->GeometryGet().Get(4,0)[0] != array1.Get(3,1)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 1) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 1))
    {
        throw MushcoreLogicFail("Bottom right corner update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conTopLeft.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(0,5)[0] != array2.Get(1,4)[0] ||
        pPipe2->GeometryGet().Get(0,5)[0] != array1.Get(1,4)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 1) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 1))
    {
        throw MushcoreLogicFail("Top left corner update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conTopRight.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(4,5)[0] != array2.Get(3,4)[0] ||
        pPipe2->GeometryGet().Get(4,5)[0] != array1.Get(3,4)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 1) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 1))
    {
        throw MushcoreLogicFail("Top right corner update failed");
    }

    return MushcoreScalar(0);
}

void
TestMushMeshPatch::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testpatch", TestPatch);
}
