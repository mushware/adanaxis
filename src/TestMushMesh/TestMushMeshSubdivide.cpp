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
 * $Id: TestMushMeshSubdivide.cpp,v 1.7 2003/10/20 13:02:55 southa Exp $
 * $Log: TestMushMeshSubdivide.cpp,v $
 * Revision 1.7  2003/10/20 13:02:55  southa
 * Patch fixes and testing
 *
 * Revision 1.6  2003/10/18 20:28:39  southa
 * Subdivision speed tests
 *
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

void
TestMushMeshSubdivide::TrianglePrint(const MushMeshArray<tVal>& inArray, U32 inOrder)
{
    for (U32 y=inArray.SizeGet().Y(); y>0;)
    {
        --y;
        cout << "[";
        for (U32 x=0; x<inArray.SizeGet().X(); ++x)
        {
            if (y >= MushMeshUtils::TriangleLimitGet(x, inOrder))
            {
                cout << '(' << inArray.Get(x, y) << ')';
            }
            else
            {
                cout << ' ' << inArray.Get(x, y) << ' ';
            }
            if (x+1 != inArray.SizeGet().X())
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
}

bool
TestMushMeshSubdivide::VerifyRectangle1(const MushMeshArray<tVal>& inArray, const t2U32& inCentre, tVal inProp)
{
    const tVal AOfN6 = (5.0/8.0) - pow(3.0+2.0*cos(2.0*M_PI/6.0), 2.0)/64.0;
    const tVal Alpha6 = 6.0*(1.0-AOfN6)/AOfN6;
    const tVal A = 1.0/(Alpha6+6.0);
    const tVal B = 1.0/8.0;
    const tVal C = 3.0/8.0;
    const tVal D = Alpha6/(Alpha6+6.0);

    const tVal Rectangle1Prop0[5][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0.5, 0.5, 0},
        {0, 0.5, 1, 0.5, 0},
        {0, 0.5, 0.5, 0, 0},
        {0, 0, 0, 0, 0}
    };

    const tVal Rectangle1Prop1[5][5] =
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
                expected = inProp * Rectangle1Prop1[x + 4 - inCentre.X()][inCentre.Y() - y] +
                    (1 - inProp) * Rectangle1Prop0[x + 4 - inCentre.X()][inCentre.Y() - y];
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


bool
TestMushMeshSubdivide::VerifyTriangle1(const MushMeshArray<tVal>& inArray, const t2U32& inCentre, tVal inProp, U32 inOrder)
{
    const tVal AOfN6 = (5.0/8.0) - pow(3.0+2.0*cos(2.0*M_PI/6.0), 2.0)/64.0;
    const tVal Alpha6 = 6.0*(1.0-AOfN6)/AOfN6;
    const tVal A = 1.0/(Alpha6+6.0);
    const tVal B = 1.0/8.0;
    const tVal C = 3.0/8.0;
    const tVal D = Alpha6/(Alpha6+6.0);

    const tVal Triangle1Prop0[5][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0.5, 0.5, 0},
        {0, 0.5, 1, 0.5, 0},
        {0, 0.5, 0.5, 0, 0},
        {0, 0, 0, 0, 0}
    };

    const tVal Triangle1Prop1[5][5] =
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
                expected = inProp * Triangle1Prop1[x + 4 - inCentre.X()][inCentre.Y() - y] +
                    (1 - inProp) * Triangle1Prop0[x + 4 - inCentre.X()][inCentre.Y() - y];
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
TestMushMeshSubdivide::SubdivideTriangle1(U32 inX, U32 inY)
{
    enum
    {
        kXMax = 7,
        kYMax = 12
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
    t2BoxU32 activeBox(0, 0, kXMax-1, kYMax);

    MushMeshSubdivide<tVal>::TriangularSubdivide(subbedArray, meshArray, activeBox, 0, 3);

    if (!VerifyTriangle1(subbedArray, t2U32(inX*2+1, inY*2+1), 0, 3), 1)
    {
        cout << "Orig mesh = " << endl;
        ArrayPrint(meshArray);
        cout << "Moved mesh = " << endl;
        ArrayPrint(subbedArray);
        throw MushcoreLogicFail("Subdivision failed to verify");
    }

    MushMeshSubdivide<tVal>::TriangularSubdivide(subbedArray, meshArray, activeBox, 1.0, 3);
    

    if (!VerifyTriangle1(subbedArray, t2U32(inX*2+1, inY*2+1), 1.0, 3), 1)
    {
        cout << "Orig mesh = " << endl;
        ArrayPrint(meshArray);
        cout << "Moved mesh = " << endl;
        ArrayPrint(subbedArray);
        throw MushcoreLogicFail("Subdivision failed to verify");
    }
}

void
TestMushMeshSubdivide::SubdivideRectangle1(U32 inX, U32 inY)
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

    if (!VerifyRectangle1(subbedArray, t2U32(inX*2+1, inY*2+1), 0))
    {
        cout << "Orig mesh = " << endl;
        ArrayPrint(meshArray);
        cout << "Moved mesh = " << endl;
        ArrayPrint(subbedArray);
        throw MushcoreLogicFail("Subdivision failed to verify");
    }

    MushMeshSubdivide<tVal>::RectangularSubdivide(subbedArray, meshArray, activeBox, 1.0);
    

    if (!VerifyRectangle1(subbedArray, t2U32(inX*2+1, inY*2+1), 1.0))
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
            SubdivideRectangle1(x, y);
        }
    }
    for (U32 x=0; x<5; ++x)
    {
        for (U32 y=0; y<5; ++y)
        {
            SubdivideTriangle1(x, y);
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
    ValueTimeTest<float>("(dummy) float");
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
