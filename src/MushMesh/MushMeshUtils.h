//%includeGuardStart {
#ifndef MUSHMESHUTILS_H
#define MUSHMESHUTILS_H
//%includeGuardStart } AdaxOlJ6M6/mPT5NXjubxQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshUtils.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0wfuXnSBCMb2QK1DMdaKSw
/*
 * $Id: MushMeshUtils.h,v 1.6 2003/10/24 12:39:09 southa Exp $
 * $Log: MushMeshUtils.h,v $
 * Revision 1.6  2003/10/24 12:39:09  southa
 * Triangular mesh work
 *
 * Revision 1.5  2003/10/23 20:03:58  southa
 * End mesh work
 *
 * Revision 1.4  2003/10/15 12:26:59  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.3  2003/10/15 11:54:54  southa
 * MushMeshArray neighbour testing and subdivision
 *
 * Revision 1.2  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 * Revision 1.1  2003/10/14 13:07:25  southa
 * MushMesh vector creation
 *
 */

#include "MushMeshStandard.h"

template<class T, Mushware::U32 D> class MushMeshVector;

class MushMeshUtils
{
public:
    static void BoundaryThrow(Mushware::U32 inValue, Mushware::U32 inLimit);
    static void BoundaryThrow(Mushware::U32 inValue1, Mushware::U32 inLimit1, Mushware::U32 inValue2, Mushware::U32 inLimit2);
    static Mushware::tVal SubdivisionAlphaGet(Mushware::U32 inN);
    static Mushware::tVal SubdivisionAlphaCalculate(Mushware::U32 inN);
    // static Mushware::U32 TriangleOrderGet(const MushMeshVector<Mushware::U32, 2>& inSize);
    static Mushware::U32 TriangleLimitGet(Mushware::U32 inX, Mushware::U32 inOrder);

    template<class T> static bool EqualIs(const MushwareValarray<T>& a, const MushwareValarray<T>& b);

private:
    enum
    {
        kMaxValence = 8
    };

    static const Mushware::tVal m_alphaTable[kMaxValence];
};

inline Mushware::tVal
MushMeshUtils::SubdivisionAlphaGet(Mushware::U32 inN)
{
    // Lookup version of SubdivisionAlphaCalculate
    if (inN >= kMaxValence)
    {
        return SubdivisionAlphaCalculate(inN);
    }
    return m_alphaTable[inN];
}

inline Mushware::U32
MushMeshUtils::TriangleLimitGet(Mushware::U32 inX, Mushware::U32 inOrder)
{
    return inX*inOrder;
}

template <class T>
inline bool
MushMeshUtils::EqualIs(const MushwareValarray<T>& a, const MushwareValarray<T>& b)
{
    if (a.size() != b.size())
    {
        return false;
    }

    for (Mushware::U32 i=0; i < a.size(); ++i)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
