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
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } cpsh/PUv+N7hZwaE5of9Kg
/*
 * $Id: TestMushMeshSubdivide.h,v 1.5 2003/10/25 11:08:18 southa Exp $
 * $Log: TestMushMeshSubdivide.h,v $
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
#include "MushMeshSubdivide.h"
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
    template<class T> static void TimeTest(MushMeshWorkspace< MushMeshArray<T> >& inWorkspace, const std::string& inName);
    template<class T> static void ValueTimeTest(const std::string& inName);
    template<class T> static void VectorTimeTest(const std::string& inName);
};

template<class T>
inline void
TestMushMeshSubdivide::ValueTimeTest(const std::string& inName)
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
    TimeTest(workspace, inName);
}

template<class T>
inline void
TestMushMeshSubdivide::VectorTimeTest(const std::string& inName)
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
    TimeTest(workspace, inName);
}

template<class T>
inline void
TestMushMeshSubdivide::TimeTest(MushMeshWorkspace< MushMeshArray<T> >& inWorkspace, const std::string& inName)
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
        if (endTime - startTime > CLOCKS_PER_SEC)
        {
            break;
        }
    }
    Mushware::tLongVal elapsed = (endTime - startTime) / CLOCKS_PER_SEC;
    Mushware::tVal finalVertices = pow((double) inWorkspace.CurrentGet().SizeGet().X(), 2);
    cout << inName << " vertices: " << count * finalVertices / elapsed << " per second (vertices=" << finalVertices << " repetitions=" << count << ')'<< endl;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
