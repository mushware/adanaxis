//%includeGuardStart {
#ifndef MUSHMESHOPS_H
#define MUSHMESHOPS_H
//%includeGuardStart } IAalLXeLNrtAYday/b93dg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshOps.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } V6914jNv2gxe4G7f3XN9Og
/*
 * $Id: MushMeshOps.h,v 1.9 2006/06/01 15:39:30 southa Exp $
 * $Log: MushMeshOps.h,v $
 * Revision 1.9  2006/06/01 15:39:30  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/07/30 19:06:14  southa
 * Collision checking
 *
 * Revision 1.7  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/05/19 13:02:10  southa
 * Mac release work
 *
 * Revision 1.5  2005/03/08 01:24:09  southa
 * Quaternion slerp between orientations
 *
 * Revision 1.4  2005/02/03 21:03:00  southa
 * Build fixes
 *
 * Revision 1.3  2004/12/12 10:55:37  southa
 * Quaternion conversions
 *
 * Revision 1.2  2004/11/30 00:18:06  southa
 * Additional vector operations
 *
 * Revision 1.1  2004/11/17 23:43:47  southa
 * Added outer product
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshMattress.h"
#include "MushMeshPosticity.h"
#include "MushMeshPreMatrix.h"
#include "MushMeshQuaternion.h"
#include "MushMeshQuaternionPair.h"
#include "MushMeshVector.h"

class MushMeshOps
{
public:
    static Mushware::t4Val OuterProduct(Mushware::t4Val inA, Mushware::t4Val inB, Mushware::t4Val inC);
    static void QuaternionPairToRotationMatrix(Mushware::t4x4Val& outMatrix, const Mushware::tQValPair& inPair);
    static void RotationMatrixToQuaternionPair(Mushware::tQValPair& outPair, const Mushware::t4x4Val& inMatrix);

    static Mushware::t4x4Val PreQuaternionToMatrix(const Mushware::tQVal& inQuat);
    static Mushware::t4x4Val PostQuaternionToMatrix(const Mushware::tQVal& inQuat);
    
    template <class T> static T Min(const T& inA, const T& inB) { return (inA < inB)?inA:inB; }
    template <class T> static T Max(const T& inA, const T& inB) { return (inA > inB)?inA:inB; }
    template <class T, Mushware::U32 D> static bool ApproxEquals(const MushMeshVector<T, D>& inA, const MushMeshVector<T, D>& inB);
    template <class T, Mushware::U32 C, Mushware::U32 R> static bool ApproxEquals(const MushMeshPreMatrix<T, C, R>& inA, const MushMeshPreMatrix<T, C, R>& inB);
    template <class T, Mushware::U32 D> static void Normalise(MushMeshVector<T, D>& ioVector);
    template <class T, Mushware::U32 D> static MushMeshVector<T, D> Lerp(const MushMeshVector<T, D>& inA, const MushMeshVector<T, D>& inB, const Mushware::tVal inProp);
    template <class T, Mushware::U32 D> static MushMeshVector<T, D> SlerpNormalised(const MushMeshVector<T, D>& inA, const MushMeshVector<T, D>& inB, const Mushware::tVal inProp);
    template <class T> static MushMeshQuaternionPair<T> SlerpNormalised(const MushMeshQuaternionPair<T>& inA, const MushMeshQuaternionPair<T>& inB, const Mushware::tVal inProp);

    static void PosticityToMattress(Mushware::t4x4o4Val& outMattress, const MushMeshPosticity& inPost);
    static void ObjectToWorld(Mushware::t4Val& ioVec, const MushMeshPosticity& inPost);
};

template <class T, Mushware::U32 D>
inline bool
MushMeshOps::ApproxEquals(const MushMeshVector<T, D>& inA, const MushMeshVector<T, D>& inB)
{
    Mushware::tVal maxLength2 = Max(inA * inA, inB * inB);
    MushMeshVector<T, D> diffVec = inA - inB;
    // std::cerr << diffVec << ", " << diffVec * diffVec << ", " << maxLength2 << endl;
    // true if the magnitude of the difference is < sqrt(1e10) * the largest magnitude
    return (diffVec * diffVec * 1e10 < maxLength2);
}

template <class T, Mushware::U32 C, Mushware::U32 R>
inline bool
MushMeshOps::ApproxEquals(const MushMeshPreMatrix<T, C, R>& inA, const MushMeshPreMatrix<T, C, R>& inB)
{
    for (Mushware::U32 r=0; r < R; ++r)
    {
        if (!ApproxEquals(inA.RowGet(r), inB.RowGet(r)))
        {
            return false;
        }
    }
    return true;
}

template <class T, Mushware::U32 D>
inline void
MushMeshOps::Normalise(MushMeshVector<T, D>& ioVector)
{
    Mushware::tVal length;
    
    length = std::sqrt(ioVector * ioVector);
    
    ioVector /= length;
}

template <class T, Mushware::U32 D>
inline MushMeshVector<T, D>
MushMeshOps::Lerp(const MushMeshVector<T, D>& inA, const MushMeshVector<T, D>& inB, const Mushware::tVal inProp)
{    
    return inA * (1 - inProp) + inB * inProp;
}

template <class T, Mushware::U32 D>
inline MushMeshVector<T, D>
MushMeshOps::SlerpNormalised(const MushMeshVector<T, D>& inA, const MushMeshVector<T, D>& inB, const Mushware::tVal inProp)
{
    bool normalise = false;
    Mushware::tVal inner = inA * inB;

    // Resolve colinear vectors
    if (std::fabs(inner) < 1e-6) inner = 1e-6;

    // Resolve normalisation errors leading to inner > 1
    if (inner > 1) inner = 1;
    if (inner < -1) inner = -1;
    
    Mushware::tVal omega = std::acos(inner);
    
    if (omega < 1e-6)
    {
        // Colinear vectors
        return Lerp(inA, inB, inProp);
    }
    
    Mushware::tVal sinOmega = std::sin(omega);
    
    if (omega > 1 && std::fabs(sinOmega) < 1e-6)
    {
        // Opposing vectors with omega ~= pi
        omega -= 1e-6;
        sinOmega = std::sin(omega);
    }
    
    // Renormalise vector if omega ~= pi
    normalise = (std::fabs(sinOmega) < 1e-3);

    Mushware::tVal aFactor = std::sin((1-inProp) * omega) / sinOmega;
    Mushware::tVal bFactor = std::sin(inProp * omega) / sinOmega;
    
    if (normalise)
    {
        // Opposing vectors, so tidy up
        MushMeshVector<T, D> retVal = inA * aFactor + inB * bFactor;

        if (retVal * retVal < 1e-10)
        {
            // Break directly opposing case
            if (std::fabs(inA.X()) < 0.9)
            {
                // Input not directly in X direction, so tweak X to break deadlock
                retVal.XSet(retVal.X() + 1e-5);
            }
            else
            {
                retVal.YSet(retVal.Y() + 1e-5);

            }
            Normalise(retVal);
            // Lerp to somewhere near where we should be
            if (inProp < 0.5)
            {
                retVal = Lerp(inA, retVal, 2*inProp);
            }
            else
            {
                retVal = Lerp(retVal, inB, 2*(inProp-0.5));
            }
        }
        Normalise(retVal);
        return retVal;
    }
    else
    {
        return inA * aFactor + inB * bFactor;
    }
}

template <class T>
inline MushMeshQuaternionPair<T>
MushMeshOps::SlerpNormalised(const MushMeshQuaternionPair<T>& inA,
    const MushMeshQuaternionPair<T>& inB, const Mushware::tVal inProp)
{
    Mushware::tQValPair retVal;
    
    retVal.FirstSet(Mushware::tQVal(SlerpNormalised(inA.First(), inB.First(), inProp)));
    retVal.SecondSet(Mushware::tQVal(SlerpNormalised(inA.Second(), inB.Second(), inProp)));
    
    return retVal;
}

inline void
MushMeshOps::ObjectToWorld(Mushware::t4Val& ioVec, const MushMeshPosticity& inPost)
{
    inPost.AngPos().VectorRotate(ioVec);
    ioVec += inPost.Pos();
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
