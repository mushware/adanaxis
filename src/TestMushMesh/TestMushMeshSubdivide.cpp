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
 * $Id: TestMushMeshSubdivide.cpp,v 1.5 2003/10/18 12:58:39 southa Exp $
 * $Log: TestMushMeshSubdivide.cpp,v $
 * Revision 1.5  2003/10/18 12:58:39  southa
 * Subdivision implementation
 *
 * Revision 1.4  2003/10/17 19:33:11  southa
 * Mesh patches
 *
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

void
TestMushMeshSubdivide::ArrayPrint(const MushMeshArray<tVal>& inArray)
{
    for (U32 y=inArray.SizeGet().Y(); y>0;)
    {
        --y;
        cout << "[";
        for (U32 x=0; x<inArray.SizeGet().X(); ++x)
        {
            cout << inArray.Get(x, y);
            if (x+1 != inArray.SizeGet().X())
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
}

bool
TestMushMeshSubdivide::VerifySingle1(const MushMeshArray<tVal>& inArray, const t2U32& inCentre, tVal inProp)
{
    const tVal AOfN6 = (5.0/8.0) - pow(3.0+2.0*cos(2.0*M_PI/6.0), 2.0)/64.0;
    const tVal Alpha6 = 6.0*(1.0-AOfN6)/AOfN6;
    const tVal A = 1.0/(Alpha6+6.0);
    const tVal B = 1.0/8.0;
    const tVal C = 3.0/8.0;
    const tVal D = Alpha6/(Alpha6+6.0);

    const tVal Single1Prop0[5][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0.5, 0.5, 0},
        {0, 0.5, 1, 0.5, 0},
        {0, 0.5, 0.5, 0, 0},
        {0, 0, 0, 0, 0}
    };

    const tVal Single1Prop1[5][5] =
    {
        {0, 0, A, B, A},
        {0, B, C, C, B},
        {A, C, D, C, A},
        {B, C, C, B, 0},
        {A, B, A, 0, 0}
    };

    bool success = true;
    for (U32 x=0; x<inArray.SizeGet().X(); ++x)
    {
        for (U32 y=0; y<inArray.SizeGet().Y(); ++y)
        {
            tVal expected;

            if (x + 4 < inCentre.X() ||
                x > inCentre.X() + 0 ||
                y + 4 < inCentre.Y() ||
                y > inCentre.Y() + 0)
            {
                expected = 0;
            }
            else
            {
                MUSHCOREASSERT(x + 4 - inCentre.X() < 5);
                MUSHCOREASSERT(y + 4 - inCentre.Y() < 5);
                expected = inProp * Single1Prop1[x + 4 - inCentre.X()][inCentre.Y() - y] +
                    (1 - inProp) * Single1Prop0[x + 4 - inCentre.X()][inCentre.Y() - y];
            }
            if (fabs(inArray.Get(x, y) - expected) > 0.0001)
            {
                cout << "Centre " << inCentre << " fault at (" << x << ", " << y << ") : expected " << expected << ", got " << inArray.Get(x, y) << endl;
                success = false;
            }
        }
    }
    return success;
}


void
TestMushMeshSubdivide::SubdivideSingle1(U32 inX, U32 inY)
{
    enum
    {
        kXMax = 5,
        kYMax = 5
    };
    MushMeshArray<tVal> meshArray(kXMax, kYMax);

    for (U32 x=0; x<kXMax; ++x)
    {
        for (U32 y=0; y<kYMax; ++y)
        {
            meshArray.Set(0, x, y);
        }
    }
    meshArray.Set(1, inX, inY);

    MushMeshArray<tVal> subbedArray;
    t2BoxU32 activeBox(1,1,4,4);

    MushMeshSubdivide<tVal>::RectangularSubdivide(subbedArray, meshArray, activeBox, 0);

    if (!VerifySingle1(subbedArray, t2U32(inX*2+1, inY*2+1), 0))
    {
        cout << "Orig mesh = " << endl;
        ArrayPrint(meshArray);
        cout << "Moved mesh = " << endl;
        ArrayPrint(subbedArray);
        throw MushcoreLogicFail("Subdivision failed to verify");
    }

    MushMeshSubdivide<tVal>::RectangularSubdivide(subbedArray, meshArray, activeBox, 1.0);
    

    if (!VerifySingle1(subbedArray, t2U32(inX*2+1, inY*2+1), 1.0))
    {
        cout << "Orig mesh = " << endl;
        ArrayPrint(meshArray);
        cout << "Moved mesh = " << endl;
        ArrayPrint(subbedArray);
        throw MushcoreLogicFail("Subdivision failed to verify");
    }
}

MushcoreScalar
TestMushMeshSubdivide::TestSubdivide(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    for (U32 x=0; x<5; ++x)
    {
        for (U32 y=0; y<5; ++y)
        {
            SubdivideSingle1(x, y);
        }
    }
    cout << endl;
    cout << "Timing tests (duration = 1s, clock granularity = 1/" << CLOCKS_PER_SEC << "s)" << endl;
#if 0
    ValueTimeTest<char>("Single char  ");
    ValueTimeTest<unsigned char>("Single uchar ");
    ValueTimeTest<short>("Single short ");
    ValueTimeTest<int>("Single int   ");
    ValueTimeTest<unsigned int>("Single uint  ");
    ValueTimeTest<long>("  long long  ");
    ValueTimeTest<unsigned long long>(" ulong long  ");
#endif
    ValueTimeTest<float>("(dummy) float  ");
    ValueTimeTest<float>("Single float ");
    ValueTimeTest<double>("Single double");
    VectorTimeTest< MushMeshVector<tVal, 1> >("1D vector    ");
    VectorTimeTest< MushMeshVector<tVal, 2> >("2D vector    ");
    VectorTimeTest< MushMeshVector<tVal, 4> >("4D vector    ");
    VectorTimeTest< MushMeshVector<tVal, 8> >("8D vector    ");
    VectorTimeTest< MushMeshVector<tVal, 16> >("16D vector   ");

    return MushcoreScalar(0);
}


void
TestMushMeshSubdivide::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testsubdivide", TestSubdivide);
}
