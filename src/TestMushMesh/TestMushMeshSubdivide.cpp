//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshSubdivide.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } SFPsgjlDzWIJxo/MBcs9fA
/*
 * $Id: TestMushMeshSubdivide.cpp,v 1.14 2003/11/13 23:25:32 southa Exp $
 * $Log: TestMushMeshSubdivide.cpp,v $
 * Revision 1.14  2003/11/13 23:25:32  southa
 * gcc 2.95 mods
 *
 * Revision 1.13  2003/10/25 18:26:03  southa
 * Patch connection rework
 *
 * Revision 1.12  2003/10/25 15:56:59  southa
 * Test tweaks
 *
 * Revision 1.11  2003/10/25 14:27:31  southa
 * Triangle mesh fixes
 *
 * Revision 1.10  2003/10/25 11:08:18  southa
 * Triangular mesh work
 *
 * Revision 1.9  2003/10/24 20:41:16  southa
 * Triangular subdivision test and fixes
 *
 * Revision 1.8  2003/10/24 12:39:09  southa
 * Triangular mesh work
 *
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

Mushware::tVal TestMushMeshSubdivide::m_testSeconds = 0.1;

void
TestMushMeshSubdivide::ArrayPrint(const MushMeshArray<tVal>& inArray)
{
    for (U32 y=inArray.SizeGet().Y(); y>0;)
    {
        --y;
        cout << "[";
        for (U32 x=0; x<inArray.SizeGet().X(); ++x)
        {
            cout << setw(4) << inArray.Get(x, y);
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
            if (y >= MushMeshUtils::TriangleLimitGet(x, inOrder) && t2U32(x,y) != t2U32(0,0))
            {
                cout << setw(4) << setprecision(4) << inArray.Get(x, y) * 10000<< '/';
            }
            else
            {
                cout << setw(5) << setprecision(4) << inArray.Get(x, y) * 10000;
            }
            if (x+1 != inArray.SizeGet().X())
            {
                cout << ",";
            }
        }
        cout << "]" << endl;
    }
    cout << setprecision(6);
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
                expected = inProp * Rectangle1Prop1[inCentre.Y() - y][x + 4 - inCentre.X()] +
                    (1 - inProp) * Rectangle1Prop0[inCentre.Y() - y][x + 4 - inCentre.X()];
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

    const tVal AOfN5 = (5.0/8.0) - pow(3.0+2.0*cos(2.0*M_PI/5.0), 2.0)/64.0;
    const tVal Alpha5 = 5.0*(1.0-AOfN5)/AOfN5;
    const tVal E = 1.0/(Alpha5+5.0);
    const tVal F = Alpha5/(Alpha5+5.0);

    const tVal Triangle1Form1Prop0[5][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0.5, 0.5, 0},
        {0, 0.5, 1, 0.5, 0},
        {0, 0.5, 0.5, 0, 0},
        {0, 0, 0, 0, 0}
    };

    const tVal Triangle1Form2Prop0[5][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0.5, 0.5, 0},
        {0, 0.5, 1, 0.5, 0},
        {0, 0, 0.5, 0.5, 0},
        {0, 0, 0, 0, 0}
    };

    const tVal Triangle1Form3Prop0[5][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0.5, 0.5, 0},
        {0, 0.5, 1, 0.5, 0},
        {0, 0, 0.5, 0, 0},
        {0, 0, 0, 0, 0}
    };

    const tVal Triangle1Form1[5][5] =
    {
        {0, 0, A, B, A},
        {0, B, C, C, B},
        {A, C, D, C, A},
        {B, C, C, B, 0},
        {A, B, A, 0, 0}
    };

    const tVal Triangle1Form2[5][5] =
    {
        {0, 0, A, B, A},
        {0, B, C, C, B},
        {A, C, D, C, A},
        {0, B, C, C, B},
        {0, 0, A, B, A},
    };

    const tVal Triangle1Form3[5][5] =
    {
        {0, 0, A, B, A},
        {0, B, C, C, B},
        {A, C, F, C, A},
        {0, B, C, B, 0},
        {0, 0, A, 0, 0},
    };

    bool success = true;
    tVal inverseProp = 1-inProp;
    U32 cX = inCentre.X();
    U32 cY = inCentre.Y();
    U32 xDefect = inArray.SizeGet().Y() / inOrder;
    // Check the apex
    for (U32 x=0; x<inArray.SizeGet().X(); ++x)
    {
        U32 centreClip = inOrder*cX;
        if (centreClip == 0) centreClip = 1;
        for (U32 y=0; y<inArray.SizeGet().Y(); ++y)
        {
            U32 yClip = inOrder*x;
            if (yClip == 0) yClip = 1;

            tVal expected = 0;
            if (y >= yClip || cY >= centreClip)
            {
                // Either this or the centre point is outside of the active part of the array
                expected = 0;
            }
            else
            {
                if (x == 0)
                {
                    const tVal AOfN = (5.0/8.0) - pow(3.0+2.0*cos(2.0*M_PI/inOrder), 2.0)/64.0;
                    const tVal Alpha = inOrder*(1.0-AOfN)/AOfN;
                    if (cX == 0)
                    {
                        expected = Alpha/(Alpha + inOrder);
                        expected *= inProp;
                        expected += inverseProp;
                    }
                    else if (cX == 2)
                    {
                        expected = 1/(Alpha + inOrder);
                        expected *= inProp;
                    }
                    else
                    {
                        expected = 0;
                    }
                }
                else if (x == 1)
                {
                    if (cX == 0 && y < inOrder)
                    {
                        expected = C * inProp + 0.5 * inverseProp;
                    }
                    else if (cX == 2)
                    {
                        U32 cYWrap = inOrder*2;
                        if (cY == y*2)
                        {
                            expected = C * inProp + 0.5 * inverseProp;
                        }
                        else if ((cY + 2) % cYWrap == y*2 ||
                            (cY + cYWrap - 2) % cYWrap == y*2)
                        {
                            expected = B * inProp;
                        }
                        else
                        {
                            expected = 0;
                        }
                    }
                }
                else if (x == 2 && cX == 0)
                {
                    // centre at 0,0 affects all second row vertices
                    if (y < inOrder * 2)
                    {
                        if (x == xDefect)
                        {
                            expected = y%2?B:E;
                        }
                        else
                        {
                            expected = y%2?B:A;
                        }
                        expected *= inProp;
                    }
                    else
                    {
                        expected = 0;
                    }
                }
                else if (cX == 0)
                {
                    expected = 0;
                }
                else
                {
                    const tVal (*formProp0Ptr)[5][5];
                    tVal formProp1[5][5];
                    
                    U32 formSize = sizeof(formProp1);
                    
                    // We are in the area covered by the form matrices
                    // Determine which form we have
                    if (cX <= xDefect && cY % cX == 0)
                    {
                        if (cX == xDefect)
                        {
                            formProp0Ptr = &Triangle1Form3Prop0;
                            memcpy(formProp1, Triangle1Form3, formSize);
                        }
                        else
                        {
                            formProp0Ptr = &Triangle1Form2Prop0;
                            memcpy(formProp1, Triangle1Form2, formSize);
                        }
                    }
                    else
                    {
                        formProp0Ptr = &Triangle1Form1Prop0;
                        memcpy(formProp1, Triangle1Form1, formSize);
                    }


                    // Prepare to de-skew the y axis
                    U32 skew;
                    if (cX > xDefect)
                    {
                        skew = cY / xDefect;
                    }
                    else if (cX > 0)
                    {
                        skew = cY/cX;
                    }
                    else
                    {
                        skew = 0;
                    }
                    
                    // Fix form for the valency difference on the defect line
                    if (cX + 2 == xDefect)
                    {
                        for (U32 ty = 0; ty < 5; ++ty)
                        {
                            if (formProp1[4-ty][4] == A)
                            {
                                // Translate form array y to defect line y and test if a defect exists
                                if ((xDefect + cY - 2 + ty + 2*skew) % xDefect == 0)
                                {
                                    formProp1[4-ty][4] = E;
                                }
                            }
                        }
                    }

                    if (cX == xDefect)
                    {
                        for (U32 ty = 0; ty < 5; ++ty)
                        {
                            if (formProp1[4-ty][2] == A)
                            {
                                // Translate form array y to defect line y and test if a defect exists
                                if ((xDefect + cY - 2 + ty) % xDefect == 0)
                                {
                                    formProp1[4-ty][2] = E;
                                }
                            }
                        }
                    }

                    if (cX == xDefect + 2)
                    {
                        for (U32 ty = 0; ty < 5; ++ty)
                        {
                            if (formProp1[4-ty][0] == A)
                            {
                                // Translate form array y to defect line y and test if a defect exists
                                if ((xDefect + cY - 2 + ty) % xDefect == 0)
                                {
                                    formProp1[4-ty][0] = E;
                                }
                            }
                        }
                    }


                    /* Use the slow but simple approach.  Check if any of the form array elements,
                     * after skewing and wrapping, match the index we have
                     */
                    for (U32 tx=0; tx<5; ++tx)
                    {
                        for (U32 ty=0; ty<5; ++ty)
                        {
                            // newX, newY is the coordinate that x,y of the form array maps onto
                            U32 newX = cX + tx;
                            if (newX >= 2) // Make sure newX not negative
                            {
                                newX -= 2; // newX valid after this

                                U32 yWrap = newX * inOrder;
                                if (yWrap < 1)
                                {
                                    yWrap = 1;
                                }
                                if (yWrap > inArray.SizeGet().Y())
                                {
                                    yWrap = inArray.SizeGet().Y();
                                }

                                U32 newY = cY + ty + yWrap - 2;

                                // Deskew y, keeping it positive

                                if (newX <= xDefect)
                                {
                                    if (cX > xDefect)
                                    {
                                        newY -= skew * (xDefect - newX);
                                    }
                                    else if (cX > newX)
                                    {
                                        newY -= skew * (cX - newX);
                                    }
                                    else
                                    {
                                        newY += skew * (newX - cX);
                                    }
                                }
                                newY = newY % yWrap;
                                if (newX == x && newY == y)
                                {
                                    expected = inProp * formProp1[4-ty][tx] +
                                          inverseProp * (*formProp0Ptr)[4-ty][tx];
                                }
                            }
                        }
                    }
                }
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
TestMushMeshSubdivide::SubdivideTriangle1(U32 inXSize, U32 inYSize, U32 inOrder, U32 inX, U32 inY)
{
    MushMeshArray<tVal> meshArray(inXSize, inYSize);

    for (U32 x=0; x<inXSize; ++x)
    {
        for (U32 y=0; y<inYSize; ++y)
        {
            meshArray.Set(0, x, y);
        }
    }
    meshArray.Set(1, inX, inY);

    MushMeshArray<tVal> subbedArray;
    t2BoxU32 activeBox(0, 0, inXSize-1, inYSize);

    MushMeshSubdivide<tVal>::TriangularSubdivide(subbedArray, meshArray, activeBox, inOrder, 0);

    if (!VerifyTriangle1(subbedArray, t2U32(inX*2, inY*2), 0, inOrder))
    {
        cout << "Orig mesh = " << endl;
        TrianglePrint(meshArray, inOrder);
        cout << "Moved mesh = " << endl;
        TrianglePrint(subbedArray, inOrder);
        throw MushcoreLogicFail("Subdivision failed to verify");
    }

    MushMeshSubdivide<tVal>::TriangularSubdivide(subbedArray, meshArray, activeBox, inOrder, 1.0);

    if (!VerifyTriangle1(subbedArray, t2U32(inX*2, inY*2), 1.0, inOrder))
    {
        cout << "Orig mesh = " << endl;
        TrianglePrint(meshArray, inOrder);
        cout << "Moved mesh = " << endl;
        TrianglePrint(subbedArray, inOrder);
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


    for (U32 order = 3; order < 7; ++order)
    {
        for (U32 xSize = 3 ; xSize < 8; ++xSize)
        {
            U32 ySize;
            if (xSize > 4)
            {
                ySize = (xSize - 4) * order;
            }
            else
            {
                ySize = (xSize - 3) * order;
            }
            if (ySize < order) ySize = order;

            for (U32 x=0; x<xSize; ++x)
            {
                for (U32 y=0; y<ySize; ++y)
                {
                    SubdivideTriangle1(xSize, ySize, order, x, y);
                }
            }
        }
    }
    cout << endl;
    cout << "Rectangle timing tests (duration = " << m_testSeconds << "s, clock granularity = 1/" << CLOCKS_PER_SEC << "s)" << endl;
    cout << ios::fixed << setprecision(0);
#if 0
    ValueTimeTest<char>("Single char  ");
    ValueTimeTest<unsigned char>("Single uchar ");
    ValueTimeTest<short>("Single short ");
    ValueTimeTest<int>("Single int   ");
    ValueTimeTest<unsigned int>("Single uint  ");
    ValueTimeTest<long>("  long long  ");
    ValueTimeTest<unsigned long long>(" ulong long  ");
#endif
    RectangleValueTimeTest<float>("(dummy) float");
    RectangleValueTimeTest<float>("Single float ");
    RectangleValueTimeTest<double>("Single double");
    RectangleVectorTimeTest< MushMeshVector<tVal, 1> >("1D vector    ");
    RectangleVectorTimeTest< MushMeshVector<tVal, 2> >("2D vector    ");
    RectangleVectorTimeTest< MushMeshVector<tVal, 3> >("3D vector    ");
    RectangleVectorTimeTest< MushMeshVector<tVal, 4> >("4D vector    ");
    RectangleVectorTimeTest< MushMeshVector<tVal, 8> >("8D vector    ");
    RectangleVectorTimeTest< MushMeshVector<tVal, 16> >("16D vector   ");

    cout.unsetf(ios::fixed);
    cout << "Triangle timing tests (duration = " << m_testSeconds << "s, clock granularity = 1/" << CLOCKS_PER_SEC << "s)" << endl;
    cout << ios::fixed << setprecision(0);

    TriangleValueTimeTest<float>("(dummy) float");
    TriangleValueTimeTest<float>("Single float ");
    TriangleValueTimeTest<double>("Single double");
    TriangleVectorTimeTest< MushMeshVector<tVal, 1> >("1D vector    ");
    TriangleVectorTimeTest< MushMeshVector<tVal, 2> >("2D vector    ");
    TriangleVectorTimeTest< MushMeshVector<tVal, 3> >("3D vector    ");
    TriangleVectorTimeTest< MushMeshVector<tVal, 4> >("4D vector    ");
    TriangleVectorTimeTest< MushMeshVector<tVal, 8> >("8D vector    ");
    TriangleVectorTimeTest< MushMeshVector<tVal, 16> >("16D vector   ");
    
    cout.unsetf(ios::fixed);
    cout << setprecision(6);

    return MushcoreScalar(0);
}


void
TestMushMeshSubdivide::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testsubdivide", TestSubdivide);
}
