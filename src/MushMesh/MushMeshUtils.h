//%includeGuardStart {
#ifndef MUSHMESHUTILS_H
#define MUSHMESHUTILS_H
//%includeGuardStart } AdaxOlJ6M6/mPT5NXjubxQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshUtils.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } oDMbV4yZBqA1axMEQLMt9A
/*
 * $Id: MushMeshUtils.h,v 1.11 2005/05/19 13:02:11 southa Exp $
 * $Log: MushMeshUtils.h,v $
 * Revision 1.11  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.10  2005/01/27 21:00:39  southa
 * Division and rendering
 *
 * Revision 1.9  2005/01/26 00:48:47  southa
 * MushMeshGroup and rendering
 *
 * Revision 1.8  2004/12/13 11:09:11  southa
 * Quaternion and vector tweaks
 *
 * Revision 1.7  2004/01/02 21:13:11  southa
 * Source conditioning
 *
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

#include "MushMeshGroup.h"
#include "MushMeshVector.h"

class MushMeshUtils
{
public:


    static Mushware::tVal SubdivisionAlphaGet(Mushware::U32 inN);
    static Mushware::tVal SubdivisionAlphaCalculate(Mushware::U32 inN);
    static Mushware::U32 TriangleLimitGet(Mushware::U32 inX, Mushware::U32 inOrder);

    static void SimpleDivide4Mesh(MushMeshGroup& outGroup, const MushMeshGroup& inGroup, const Mushware::tVal inShrink);
    
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
