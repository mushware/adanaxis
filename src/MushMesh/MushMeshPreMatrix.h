//%includeGuardStart {
#ifndef MUSHMESHPREMATRIX_H
#define MUSHMESHPREMATRIX_H
//%includeGuardStart } cfQlExLemiLPwDGXXbIdWg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPreMatrix.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0u0Dmc4oDcZxueU4XtX+Cw
/*
 * $Id: MushMeshPreMatrix.h,v 1.2 2004/10/31 23:34:06 southa Exp $
 * $Log: MushMeshPreMatrix.h,v $
 * Revision 1.2  2004/10/31 23:34:06  southa
 * Hypercube rendering test
 *
 * Revision 1.1  2004/10/31 09:22:51  southa
 * Added MushMeshPreMatrix
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshVector.h"
 
// A PreMatrix stores each row as a vector, so is optimised for
// the left hand side of multiplication

template<class T, Mushware::U32 C, Mushware::U32 R>
class MushMeshPreMatrix
{
public:
    typedef MushMeshPreMatrix<T, C, R> tThis;
    typedef MushMeshVector<T, C> tThisVec;
    
    MushMeshPreMatrix() {}
    explicit MushMeshPreMatrix(const tThisVec& in0)
    {
        MUSHCOREASSERT(R >= 1);
        m_value[0] = in0;
    }
    MushMeshPreMatrix(const tThisVec& in0, const tThisVec& in1)
    {
        MUSHCOREASSERT(R >= 2);
        m_value[0] = in0;
        m_value[1] = in1;
    }
    MushMeshPreMatrix(const tThisVec& in0, const tThisVec& in1, const tThisVec& in2)
    {
        MUSHCOREASSERT(R >= 3);
        m_value[0] = in0;
        m_value[1] = in1;
        m_value[2] = in2;
    }
    MushMeshPreMatrix(const tThisVec& in0, const tThisVec& in1, const tThisVec& in2, const tThisVec& in3)
    {
        MUSHCOREASSERT(R >= 4);
        m_value[0] = in0;
        m_value[1] = in1;
        m_value[2] = in2;
        m_value[3] = in3;
    }
    
    const T& RCGet(Mushware::U32 inR, Mushware::U32 inC) const
    {
        return m_value[inR][inC];
    }
    
    void RCSet(const T& inValue, Mushware::U32 inR, Mushware::U32 inC)
    {
        m_value[inR][inC] = inValue;
    }
    
    const tThisVec& RowGet(Mushware::U32 inIndex) const { return m_value[inIndex]; }
    tThisVec& RowGet(Mushware::U32 inIndex) { return m_value[inIndex]; }
    
private:
    MushMeshVector<T, C> m_value[R];
    
    //template <class fnT, Mushware::U32 fnD, class fnI> friend const MushMeshVector<fnT, fnD>& operator*=(MushMeshVector<fnT, fnD>& a, const fnI& b);
    
};

template <class T, Mushware::U32 C, Mushware::U32 R>
inline MushMeshVector<T, R>
operator*(const MushMeshPreMatrix<T, C, R>& a, const MushMeshVector<T, C>& b)
{
    MushMeshVector<T, R> retValue;
    for (Mushware::U32 i = 0; i < R; ++i)
    {
        retValue[i] = a.RowGet(i) * b;
    }
    return retValue;
}


template <class T, Mushware::U32 C, Mushware::U32 R>
inline bool
operator==(const MushMeshPreMatrix<T, C, R>& a, const MushMeshPreMatrix<T, C, R>& b)
{
    for (Mushware::U32 r = 0; r < R; ++r)
    {
        if (a.RowGet(r) != b.RowGet(r))
        {
            return false;
        }
    }
    return true;
}

template <class T, Mushware::U32 C, Mushware::U32 R>
inline bool
operator!=(const MushMeshPreMatrix<T, C, R>& a, const MushMeshPreMatrix<T, C, R>& b)
{
    return !(a == b);
}

// Stream operators

template <class T, Mushware::U32 C, Mushware::U32 R>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshPreMatrix<T, C, R>& inMatrix)
{
    ioOut << '[';
    for (Mushware::U32 i=0; i<C; ++i)
    {
        ioOut << inMatrix.RowGet(i);
        if (i+1 < C)
        {
            ioOut << ", ";
        }
    }
    ioOut << ']';
    return ioOut;
}

namespace Mushware
{
    typedef MushMeshPreMatrix<Mushware::tVal, 2, 2> t2x2Val;
    typedef MushMeshPreMatrix<Mushware::tVal, 3, 3> t3x3Val;
    typedef MushMeshPreMatrix<Mushware::tVal, 4, 4> t4x4Val;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
