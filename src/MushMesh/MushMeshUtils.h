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
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } E6hzk2Z9M26wAK6ICXOBXw
/*
 * $Id: MushMeshUtils.h,v 1.3 2003/10/15 11:54:54 southa Exp $
 * $Log: MushMeshUtils.h,v $
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

class MushMeshUtils
{
public:
    static void BoundaryThrow(Mushware::U32 inValue, Mushware::U32 inLimit);
    static Mushware::tVal SubdivisionAlphaGet(Mushware::U32 inN);
    static Mushware::tVal SubdivisionAlphaCalculate(Mushware::U32 inN); // for testing

    template <class T> static bool EqualIs(const MushwareValarray<T>& a, const MushwareValarray<T>& b);

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
    MUSHCOREASSERT(inN < kMaxValence);
    return m_alphaTable[inN];
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
