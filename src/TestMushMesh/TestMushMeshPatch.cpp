//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPatch.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } yKD5SCMk6D67HbzoDOzgSA
/*
 * $Id: TestMushMeshPatch.cpp,v 1.3 2004/01/02 21:13:17 southa Exp $
 * $Log: TestMushMeshPatch.cpp,v $
 * Revision 1.3  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/26 10:05:30  southa
 * End patch testing
 *
 * Revision 1.1  2003/10/20 13:05:57  southa
 * Created
 *
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
    for (U32 x=0; x<inArray1.SizeGet().X(); ++x)
    {
        for (U32 y=0; y<inArray1.SizeGet().Y(); ++y)
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
    auto_ptr<MushMeshPatchEnd> pEnd1(new MushMeshPatchEnd);

    Mushware::tGeometryArray array1;
    Mushware::tGeometryArray array2;
    Mushware::tGeometryArray array3;

    array1.SizeSet(t2U32(kXMax, kYMax));
    array2.SizeSet(t2U32(kXMax, kYMax));
    array3.SizeSet(t2U32(kXMax, kYMax-2));
    
    for (U32 x=0; x<kXMax; ++x)
    {
        for (U32 y=0; y<kYMax; ++y)
        {
            tVal testValue = x + y*10;
            array1.Set(tGeometryVector(100+testValue), x, y);
            array2.Set(tGeometryVector(200+testValue), x, y);
            if (y < kYMax - 2)
            {
                array3.Set(tGeometryVector(300+testValue), x, y);
            }
        }
    }

    /*********************
     *
     * Pipe patching tests
     *
     *********************/

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
    if (pPipe1->GeometryGet().Get(0,1)[0] != array2.Get(2,1)[0] ||
        pPipe1->GeometryGet().Get(0,2)[0] != array2.Get(2,2)[0] ||
        pPipe1->GeometryGet().Get(0,3)[0] != array2.Get(2,3)[0] ||
        pPipe1->GeometryGet().Get(0,4)[0] != array2.Get(2,4)[0] ||
        pPipe1->GeometryGet().Get(0,5)[0] != array2.Get(2,5)[0] ||
        pPipe2->GeometryGet().Get(0,1)[0] != array1.Get(2,1)[0] ||
        pPipe2->GeometryGet().Get(0,2)[0] != array1.Get(2,2)[0] ||
        pPipe2->GeometryGet().Get(0,3)[0] != array1.Get(2,3)[0] ||
        pPipe2->GeometryGet().Get(0,4)[0] != array1.Get(2,4)[0] ||
        pPipe2->GeometryGet().Get(0,5)[0] != array1.Get(2,5)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 5) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 5))
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
    if (pPipe1->GeometryGet().Get(5,1)[0] != array2.Get(3,1)[0] ||
        pPipe1->GeometryGet().Get(5,2)[0] != array2.Get(3,2)[0] ||
        pPipe1->GeometryGet().Get(5,3)[0] != array2.Get(3,3)[0] ||
        pPipe1->GeometryGet().Get(5,4)[0] != array2.Get(3,4)[0] ||
        pPipe1->GeometryGet().Get(5,5)[0] != array2.Get(3,5)[0] ||
        pPipe2->GeometryGet().Get(5,1)[0] != array1.Get(3,1)[0] ||
        pPipe2->GeometryGet().Get(5,2)[0] != array1.Get(3,2)[0] ||
        pPipe2->GeometryGet().Get(5,3)[0] != array1.Get(3,3)[0] ||
        pPipe2->GeometryGet().Get(5,4)[0] != array1.Get(3,4)[0] ||
        pPipe2->GeometryGet().Get(5,5)[0] != array1.Get(3,5)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 5) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 5))
    {
        throw MushcoreLogicFail("Right edge update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conEdgeBottom.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(1,0)[0] != array2.Get(1,2)[0] ||
        pPipe1->GeometryGet().Get(2,0)[0] != array2.Get(2,2)[0] ||
        pPipe1->GeometryGet().Get(3,0)[0] != array2.Get(3,2)[0] ||
        pPipe1->GeometryGet().Get(4,0)[0] != array2.Get(4,2)[0] ||
        pPipe2->GeometryGet().Get(1,0)[0] != array1.Get(1,2)[0] ||
        pPipe2->GeometryGet().Get(2,0)[0] != array1.Get(2,2)[0] ||
        pPipe2->GeometryGet().Get(3,0)[0] != array1.Get(3,2)[0] ||
        pPipe2->GeometryGet().Get(4,0)[0] != array1.Get(4,2)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 4) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 4))
    {
        throw MushcoreLogicFail("Bottom edge update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conEdgeTop.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(1,6)[0] != array2.Get(1,4)[0] ||
        pPipe1->GeometryGet().Get(2,6)[0] != array2.Get(2,4)[0] ||
        pPipe1->GeometryGet().Get(3,6)[0] != array2.Get(3,4)[0] ||
        pPipe1->GeometryGet().Get(4,6)[0] != array2.Get(4,4)[0] ||
        pPipe2->GeometryGet().Get(1,6)[0] != array1.Get(1,4)[0] ||
        pPipe2->GeometryGet().Get(2,6)[0] != array1.Get(2,4)[0] ||
        pPipe2->GeometryGet().Get(3,6)[0] != array1.Get(3,4)[0] ||
        pPipe2->GeometryGet().Get(4,6)[0] != array1.Get(4,4)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 4) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 4))
    {
        throw MushcoreLogicFail("Top edge update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conBottomLeft.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(0,0)[0] != array2.Get(2,2)[0] ||
        pPipe2->GeometryGet().Get(0,0)[0] != array1.Get(2,2)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 1) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 1))
    {
        throw MushcoreLogicFail("Bottom left corner update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conBottomRight.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(5,0)[0] != array2.Get(3,2)[0] ||
        pPipe2->GeometryGet().Get(5,0)[0] != array1.Get(3,2)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 1) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 1))
    {
        throw MushcoreLogicFail("Bottom right corner update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conTopLeft.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(0,6)[0] != array2.Get(2,4)[0] ||
        pPipe2->GeometryGet().Get(0,6)[0] != array1.Get(2,4)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 1) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 1))
    {
        throw MushcoreLogicFail("Top left corner update failed");
    }

    pPipe1->GeometrySet(array1);
    pPipe2->GeometrySet(array2);
    conTopRight.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(5,6)[0] != array2.Get(3,4)[0] ||
        pPipe2->GeometryGet().Get(5,6)[0] != array1.Get(3,4)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 1) ||
        !ChangeVerify(pPipe2->GeometryGet(), array2, 1))
    {
        throw MushcoreLogicFail("Top right corner update failed");
    }

    /*********************
     *
     * End patching tests
     *
     *********************/
    MushMeshConnector endEdgeRight(*pPipe1, MushMeshPatch::kEdgeRight, *pEnd1, MushMeshPatch::kEdgeRight);
    MushMeshConnector endPointBottomRight(*pPipe1, MushMeshPatch::kPointBottomRight, *pEnd1, MushMeshPatch::kPointBottomRight);
    MushMeshConnector endPointTopRight(*pPipe1, MushMeshPatch::kPointTopRight, *pEnd1, MushMeshPatch::kPointTopRight);

    pPipe1->GeometrySet(array1);
    pEnd1->GeometrySet(array3);

    endEdgeRight.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(5,1)[0] != array3.Get(3,0)[0] ||
        pPipe1->GeometryGet().Get(5,2)[0] != array3.Get(3,1)[0] ||
        pPipe1->GeometryGet().Get(5,3)[0] != array3.Get(3,2)[0] ||
        pPipe1->GeometryGet().Get(5,4)[0] != array3.Get(3,3)[0] ||
        pPipe1->GeometryGet().Get(5,5)[0] != array3.Get(3,4)[0] ||
        pEnd1->GeometryGet().Get(5,0)[0] != array1.Get(3,1)[0] ||
        pEnd1->GeometryGet().Get(5,1)[0] != array1.Get(3,2)[0] ||
        pEnd1->GeometryGet().Get(5,2)[0] != array1.Get(3,3)[0] ||
        pEnd1->GeometryGet().Get(5,3)[0] != array1.Get(3,4)[0] ||
        pEnd1->GeometryGet().Get(5,4)[0] != array1.Get(3,5)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 5) ||
        !ChangeVerify(pEnd1->GeometryGet(), array3, 5))
    {
        cout << "Patch 1 = " << endl;
        GeometryPrint(pPipe1->GeometryGet());
        cout << "Patch 2 = " << endl;
        GeometryPrint(pEnd1->GeometryGet());
        throw MushcoreLogicFail("End right edge update failed");
    }

    pPipe1->GeometrySet(array1);
    pEnd1->GeometrySet(array3);

    endPointBottomRight.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(5,0)[0] != array3.Get(3,4)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 1) ||
        !ChangeVerify(pEnd1->GeometryGet(), array3, 0))
    {
        throw MushcoreLogicFail("End bottom right point update failed");
    }

    pPipe1->GeometrySet(array1);
    pEnd1->GeometrySet(array3);

    endPointTopRight.TargetsUpdate();
    if (pPipe1->GeometryGet().Get(5,6)[0] != array3.Get(3,0)[0] ||
        !ChangeVerify(pPipe1->GeometryGet(), array1, 1) ||
        !ChangeVerify(pEnd1->GeometryGet(), array3, 0))
    {
        throw MushcoreLogicFail("End top right point update failed");
    }

    return MushcoreScalar(0);
}

void
TestMushMeshPatch::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshpatch", TestPatch);
}
