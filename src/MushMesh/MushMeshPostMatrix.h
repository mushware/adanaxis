//%includeGuardStart {
#ifndef MUSHMESHPOSTMATRIX_H
#define MUSHMESHPOSTMATRIX_H
//%includeGuardStart } l5bK1PXEUyWiXfj1w7CF4Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPostMatrix.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } FzXzTmyb4EeEYrK5+Soi7A
/*
 * $Id: MushMeshPostMatrix.h,v 1.1 2004/12/06 20:44:17 southa Exp $
 * $Log: MushMeshPostMatrix.h,v $
 * Revision 1.1  2004/12/06 20:44:17  southa
 * Quaternion and matrix operations
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshPreMatrix.h"

// A PostMatrix stores each column as a vector, so is optimised for
// the right hand side of multiplication

template<class T, Mushware::U32 C, Mushware::U32 R>
class MushMeshPostMatrix
{
public:
    typedef MushMeshPostMatrix<T, C, R> tThis;
    typedef MushMeshVector<T, R> tThisVec;
    
    MushMeshPostMatrix() {}
    
    // Allow this conversion implicitly
    MushMeshPostMatrix(const MushMeshPreMatrix<T, C, R>& inMatrix);

    explicit MushMeshPostMatrix(const tThisVec& in0)
    {
        MUSHCOREASSERT(C >= 1);
        m_value[0] = in0;
    }
    MushMeshPostMatrix(const tThisVec& in0, const tThisVec& in1)
    {
        MUSHCOREASSERT(C >= 2);
        m_value[0] = in0;
        m_value[1] = in1;
    }
    MushMeshPostMatrix(const tThisVec& in0, const tThisVec& in1, const tThisVec& in2)
    {
        MUSHCOREASSERT(C >= 3);
        m_value[0] = in0;
        m_value[1] = in1;
        m_value[2] = in2;
    }
    MushMeshPostMatrix(const tThisVec& in0, const tThisVec& in1, const tThisVec& in2, const tThisVec& in3)
    {
        MUSHCOREASSERT(C >= 4);
        m_value[0] = in0;
        m_value[1] = in1;
        m_value[2] = in2;
        m_value[3] = in3;
    }
    
    const T& RCGet(Mushware::U32 inR, Mushware::U32 inC) const
    {
        return m_value[inC][inR];
    }
    
    void RCSet(const T& inValue, Mushware::U32 inR, Mushware::U32 inC)
    {
        m_value[inC].Set(inValue, inR);
    }
    
    const tThisVec& ColumnGet(Mushware::U32 inIndex) const { return m_value[inIndex]; }
    tThisVec& ColumnGet(Mushware::U32 inIndex) { return m_value[inIndex]; }
    
private:
    MushMeshVector<T, R> m_value[C];
};

template <class T, Mushware::U32 C, Mushware::U32 R>
inline
MushMeshPostMatrix<T, C, R>::MushMeshPostMatrix(const MushMeshPreMatrix<T, C, R>& inMatrix)
{
    for (Mushware::U32 r = 0; r < R; ++r)
    {
        for (Mushware::U32 c = 0; c < C; ++c)
        {
            RCSet(inMatrix.RCGet(r, c), r, c);
        }
    }
}

template <class T, Mushware::U32 C, Mushware::U32 R>
inline MushMeshPreMatrix<T, C, R>
operator*(const MushMeshPreMatrix<T, C, R>& a, const MushMeshPostMatrix<T, C, R>& b)
{
    MushMeshPreMatrix<T, C, R> retValue;
    for (Mushware::U32 r = 0; r < R; ++r)
    {
        for (Mushware::U32 c = 0; c < C; ++c)
        {
            retValue.RCSet(a.RowGet(r) * b.ColumnGet(c), r, c);
        }
    }
    return retValue;
}

template <class T, Mushware::U32 C, Mushware::U32 R>
inline MushMeshPreMatrix<T, C, R>
operator*(const MushMeshPreMatrix<T, C, R>& a, const MushMeshPreMatrix<T, C, R>& b)
{
    return a * MushMeshPostMatrix<T, C, R>(b);
}

// Stream operators

template <class T, Mushware::U32 C, Mushware::U32 R>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshPostMatrix<T, C, R>& inMatrix)
{
    MushMeshPreMatrix<T, C, R> preMatrix(inMatrix);
    ioOut << preMatrix;
    return ioOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
