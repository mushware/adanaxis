//%includeGuardStart {
#ifndef TESTMUSHMESHSUBDIVIDE_H
#define TESTMUSHMESHSUBDIVIDE_H
//%includeGuardStart } BgqjDqOHt2g1f9pgpwVQpA
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshSubdivide.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Y06e1+m5y028sC2Kud/rxQ
/*
 * $Id: TestMushMeshSubdivide.h,v 1.9 2004/01/02 21:13:17 southa Exp $
 * $Log: TestMushMeshSubdivide.h,v $
 * Revision 1.9  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.8  2003/10/25 18:26:03  southa
 * Patch connection rework
 *
 * Revision 1.7  2003/10/25 15:56:59  southa
 * Test tweaks
 *
 * Revision 1.6  2003/10/25 14:27:31  southa
 * Triangle mesh fixes
 *
 * Revision 1.5  2003/10/25 11:08:18  southa
 * Triangular mesh work
 *
 * Revision 1.4  2003/10/24 12:39:09  southa
 * Triangular mesh work
 *
 * Revision 1.3  2003/10/18 20:28:39  southa
 * Subdivision speed tests
 *
 * Revision 1.2  2003/10/18 12:58:39  southa
 * Subdivision implementation
 *
 * Revision 1.1  2003/10/15 11:54:55  southa
 * MushMeshArray neighbour testing and subdivision
 *
 */

#include "TestMushMeshStandard.h"



#if defined(HAVE_MUSHMESH_MUSHMESH_H)
#include <MushMesh/MushMeshSubdivide.h>
#else
#if defined(HAVE_MUSHMESH_H)
#include <MushMeshSubdivide.h>
#else
#include "MushMesh/MushMeshSubdivide.h"
#endif
#endif

class TestMushMeshSubdivide
{
public:
    static MushcoreScalar TestSubdivide(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
private:
    static void ArrayPrint(const MushMeshArray<Mushware::tVal>& inArray);
    static void TrianglePrint(const MushMeshArray<Mushware::tVal>& inArray, Mushware::U32 inOrder);
    static bool VerifyRectangle1(const MushMeshArray<Mushware::tVal>& inArray, const Mushware::t2U32& inCentre, Mushware::tVal inProp);
    static bool VerifyTriangle1(const MushMeshArray<Mushware::tVal>& inArray, const Mushware::t2U32& inCentre, Mushware::tVal inProp, Mushware::U32 inOrder);
    static void SubdivideRectangle1(Mushware::U32 inX, Mushware::U32 inY);
    static void SubdivideTriangle1(Mushware::U32 inXSize, Mushware::U32 inYSize, Mushware::U32 inOrder, Mushware::U32 inX, Mushware::U32 inY);
    template<class T> static void RectangleTimeTest(MushMeshWorkspace< MushMeshArray<T> >& inWorkspace, const std::string& inName);
    template<class T> static void RectangleValueTimeTest(const std::string& inName);
    template<class T> static void RectangleVectorTimeTest(const std::string& inName);
    template<class T> static void TriangleTimeTest(MushMeshWorkspace< MushMeshArray<T> >& inWorkspace, Mushware::U32 inOrder, const std::string& inName);
    template<class T> static void TriangleValueTimeTest(const std::string& inName);
    template<class T> static void TriangleVectorTimeTest(const std::string& inName);

    static Mushware::tVal m_testSeconds;
};

template<class T>
inline void
TestMushMeshSubdivide::RectangleValueTimeTest(const std::string& inName)
{
    MushMeshWorkspace< MushMeshArray<T> > workspace;

    enum
    {
        kXMax = 33,
        kYMax = 33
    };
    workspace.CurrentWRefGet().SizeSet(Mushware::t2U32(kXMax, kYMax));

    // Place non-trivial data in the array
    for (Mushware::U32 x=0; x<kXMax; ++x)
    {
        for (Mushware::U32 y=0; y<kYMax; ++y)
        {
            workspace.CurrentWRefGet().Set(x+500*y, x, y);
        }
    }
    workspace.Swap();
    RectangleTimeTest(workspace, inName);
}

template<class T>
inline void
TestMushMeshSubdivide::RectangleVectorTimeTest(const std::string& inName)
{
    MushMeshWorkspace< MushMeshArray<T> > workspace;

    enum
    {
        kXMax = 33,
        kYMax = 33
    };
    workspace.CurrentWRefGet().SizeSet(Mushware::t2U32(kXMax, kYMax));

    // Place non-trivial data in the array
    for (Mushware::U32 x=0; x<kXMax; ++x)
    {
        for (Mushware::U32 y=0; y<kYMax; ++y)
        {
            T value;
            for (Mushware::U32 i=0; i<T::SizeGet(); ++i)
            {
                value.Set(x+500*y+i, i);
            }
            workspace.CurrentWRefGet().Set(value, x, y);
        }
    }
    workspace.Swap();
    RectangleTimeTest(workspace, inName);
}

template<class T>
inline void
TestMushMeshSubdivide::RectangleTimeTest(MushMeshWorkspace< MushMeshArray<T> >& inWorkspace, const std::string& inName)
{
    clock_t startTime = 0;
    clock_t endTime;
    Mushware::U32 count;

    for (count=0; count<1e7; ++count)
    {
        MushMeshSubdivide<T>::RectangularSubdivide(inWorkspace.CurrentWRefGet(),
            inWorkspace.PreviousGet(),
            Mushware::t2BoxU32(Mushware::t2U32(1,1), inWorkspace.PreviousGet().SizeGet()-1),
            1.0);
        if (startTime == 0)
        {
            startTime = clock();
        }

        endTime = clock();
        if (endTime - startTime > m_testSeconds * CLOCKS_PER_SEC)
        {
            break;
        }
    }
    Mushware::tLongVal elapsed = (static_cast<Mushware::tLongVal>(endTime - startTime)) / CLOCKS_PER_SEC;
    Mushware::tVal finalVertices = pow(static_cast<double>(inWorkspace.CurrentGet().SizeGet().X()), 2);
    cout << inName << " vertices: " << count * finalVertices / elapsed << " per second (vertices=" << finalVertices << " repetitions=" << count << ')'<< endl;
}


template<class T>
inline void
TestMushMeshSubdivide::TriangleValueTimeTest(const std::string& inName)
{
    MushMeshWorkspace< MushMeshArray<T> > workspace;

    enum
    {
        kXMax = 20,
        kYMax = 80,
        kOrder = 5
    };
    workspace.CurrentWRefGet().SizeSet(Mushware::t2U32(kXMax, kYMax));

    // Place non-trivial data in the array
    for (Mushware::U32 x=0; x<kXMax; ++x)
    {
        for (Mushware::U32 y=0; y<kYMax; ++y)
        {
            workspace.CurrentWRefGet().Set(x+500*y, x, y);
        }
    }
    workspace.Swap();
    TriangleTimeTest(workspace, kOrder, inName);
}

template<class T>
inline void
TestMushMeshSubdivide::TriangleVectorTimeTest(const std::string& inName)
{
    MushMeshWorkspace< MushMeshArray<T> > workspace;

    enum
    {
        kXMax = 20,
        kYMax = 80,
        kOrder = 5
    };
    workspace.CurrentWRefGet().SizeSet(Mushware::t2U32(kXMax, kYMax));

    // Place non-trivial data in the array
    for (Mushware::U32 x=0; x<kXMax; ++x)
    {
        for (Mushware::U32 y=0; y<kYMax; ++y)
        {
            T value;
            for (Mushware::U32 i=0; i<T::SizeGet(); ++i)
            {
                value.Set(x+500*y+i, i);
            }
            workspace.CurrentWRefGet().Set(value, x, y);
        }
    }
    workspace.Swap();
    TriangleTimeTest(workspace, kOrder, inName);
}

template<class T>
inline void
TestMushMeshSubdivide::TriangleTimeTest(MushMeshWorkspace< MushMeshArray<T> >& inWorkspace, Mushware::U32 inOrder, const std::string& inName)
{
    clock_t startTime = 0;
    clock_t endTime;
    Mushware::U32 count;

    for (count=0; count<1e7; ++count)
    {
        MushMeshSubdivide<T>::TriangularSubdivide(inWorkspace.CurrentWRefGet(),
            inWorkspace.PreviousGet(),
            Mushware::t2BoxU32(Mushware::t2U32(0,0), inWorkspace.PreviousGet().SizeGet()-Mushware::t2U32(1, 0)),
            inOrder, 1.0);
        if (startTime == 0)
        {
            startTime = clock();
        }

        endTime = clock();
        if (endTime - startTime > m_testSeconds * CLOCKS_PER_SEC)
        {
            break;
        }
    }
    Mushware::tLongVal elapsed = (static_cast<Mushware::tLongVal>(endTime - startTime)) / CLOCKS_PER_SEC;

    Mushware::U32 xSize = inWorkspace.CurrentGet().SizeGet().X();
    Mushware::U32 ySize = inWorkspace.CurrentGet().SizeGet().Y();
    Mushware::U32 xTriangleSize = ySize / inOrder;
    Mushware::U32 finalVertices = 1 + xTriangleSize*(ySize+1)/2 + ySize * (xSize - 1 - xTriangleSize);
    cout << inName << " vertices: " << count * finalVertices / elapsed << " per second (vertices=" << finalVertices << " repetitions=" << count << ')'<< endl;
}


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
