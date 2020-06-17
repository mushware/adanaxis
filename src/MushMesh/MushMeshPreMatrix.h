//%includeGuardStart {
#ifndef MUSHMESHPREMATRIX_H
#define MUSHMESHPREMATRIX_H
//%includeGuardStart } cfQlExLemiLPwDGXXbIdWg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPreMatrix.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } q3SlT3M/++c8SCc7yNLVFA
/*
 * $Id: MushMeshPreMatrix.h,v 1.13 2006/06/01 15:39:31 southa Exp $
 * $Log: MushMeshPreMatrix.h,v $
 * Revision 1.13  2006/06/01 15:39:31  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/08/01 17:58:31  southa
 * Object explosion
 *
 * Revision 1.11  2005/07/19 10:07:06  southa
 * Adanaxis work
 *
 * Revision 1.10  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.9  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.8  2005/07/01 10:03:30  southa
 * Projection work
 *
 * Revision 1.7  2005/05/19 13:02:10  southa
 * Mac release work
 *
 * Revision 1.6  2005/01/29 14:06:12  southa
 * OpenGL buffers and extensions
 *
 * Revision 1.5  2004/12/13 11:09:11  southa
 * Quaternion and vector tweaks
 *
 * Revision 1.4  2004/12/12 10:55:37  southa
 * Quaternion conversions
 *
 * Revision 1.3  2004/12/06 20:44:17  southa
 * Quaternion and matrix operations
 *
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
        RCBoundsCheck(inR, inC);
        return m_value[inR][inC];
    }
    
    void RCSet(const T& inValue, Mushware::U32 inR, Mushware::U32 inC)
    {
        RCBoundsCheck(inR, inC);
        m_value[inR].Set(inValue, inC);
    }
    
    const tThisVec& RowGet(Mushware::U32 inR) const { RowBoundsCheck(inR); return m_value[inR]; }
    tThisVec ColumnGet(Mushware::U32 inC) const;

    void RowSet(const tThisVec& inVec, Mushware::U32 inR) { RowBoundsCheck(inR); m_value[inR] = inVec; }
    
    void PreMultiply(MushMeshVector<T, C>& ioVec) const;
    void ToMultiplicativeIdentitySet(void);
    
    const MushMeshPreMatrix<T, R, C> Transpose(void) const;
    void InPlaceTranspose(void);
    
    static const tThis Identity(void);
    
protected:
    void RowBoundsCheck(Mushware::U32 inR) const {
#ifdef MUSHMESH_DEBUG
        if (inR >= R) MushcoreUtil::BoundaryThrow(inR, R);
#endif
    }
    void ColumnBoundsCheck(Mushware::U32 inC) const {
#ifdef MUSHMESH_DEBUG
        if (inC >= C) MushcoreUtil::BoundaryThrow(inC, C);
#endif
    }
    void RCBoundsCheck(Mushware::U32 inR, Mushware::U32 inC) const { RowBoundsCheck(inR); ColumnBoundsCheck(inC); }
    
private:
    tThisVec m_value[R];
};

template <class T, Mushware::U32 C, Mushware::U32 R>
inline typename MushMeshPreMatrix<T, C, R>::tThisVec
MushMeshPreMatrix<T, C, R>::ColumnGet(Mushware::U32 inC) const
{
    ColumnBoundsCheck(inC);
    MushMeshVector<T, R> retValue;
    for (Mushware::U32 r = 0; r < R; ++r)
    {
        retValue.Set(m_value[r][inC], r);
    }
    return retValue;
}

template <class T, Mushware::U32 C, Mushware::U32 R>
inline void
MushMeshPreMatrix<T, C, R>::PreMultiply(MushMeshVector<T, C>& ioVec) const
{
    MushMeshVector<T, R> vecCopy(ioVec);
    for (Mushware::U32 i = 0; i < R; ++i)
    {
        ioVec.Set(RowGet(i) * vecCopy, i);
    }
}

template <class T, Mushware::U32 C, Mushware::U32 R>
inline void
MushMeshPreMatrix<T, C, R>::ToMultiplicativeIdentitySet(void)
{
    for (Mushware::U32 r = 0; r < R; ++r)
    {
        for (Mushware::U32 c = 0; c < C; ++c)
        {
            if (r == c)
            {
                RCSet(1, r, c);
            }
            else
            {
                RCSet(0, r, c);
            }
        }
    }
}



template <class T, Mushware::U32 C, Mushware::U32 R>
inline const typename MushMeshPreMatrix<T, C, R>::tThis
MushMeshPreMatrix<T, C, R>::Identity(void)
{
    MushMeshPreMatrix<T, C, R> retValue;
    for (Mushware::U32 r = 0; r < R; ++r)
    {
        for (Mushware::U32 c = 0; c < C; ++c)
        {
            if (r == c)
            {
                retValue.RCSet(1, r, c);
            }
            else
            {
                retValue.RCSet(0, r, c);
            }
        }
    }
    return retValue;
}

template <class T, Mushware::U32 C, Mushware::U32 R>
inline MushMeshVector<T, R>
operator*(const MushMeshPreMatrix<T, C, R>& a, const MushMeshVector<T, C>& b)
{
    MushMeshVector<T, R> retValue;
    for (Mushware::U32 i = 0; i < R; ++i)
    {
        retValue.Set(a.RowGet(i) * b, i);
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

template <class T, Mushware::U32 C, Mushware::U32 R>
inline const MushMeshPreMatrix<T, R, C>
MushMeshPreMatrix<T, C, R>::Transpose(void) const
{
    MushMeshPreMatrix<T, R, C> retValue;
    for (Mushware::U32 r = 0; r < R; ++r)
    {
        for (Mushware::U32 c = 0; c < C; ++c)
        {
            retValue.RCSet(RCGet(r, c), c, r);
        }
    }
    return retValue;
}

template <class T, Mushware::U32 C, Mushware::U32 R>
inline void
MushMeshPreMatrix<T, C, R>::InPlaceTranspose(void)
{
    MUSHCOREASSERT(R == C);
    for (Mushware::U32 r = 0; r < R; ++r)
    {
        for (Mushware::U32 c = r+1; c < C; ++c)
        {
            T temp = RCGet(r, c);
            RCSet(RCGet(c, r), r, c);
            RCSet(temp, c, r);
        }
    }
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

template <class T, Mushware::U32 C, Mushware::U32 R>
inline void
operator>>(MushcoreXMLIStream& ioIn, MushMeshPreMatrix<T, C, R>& outMatrix)
{
    std::vector< std::vector<T> > valueVec;
    ioIn >> valueVec;
    for (Mushware::U32 r=0; r<R; ++r)
    {
        for (Mushware::U32 c=0; c<C; ++c)
        {
            if (r < valueVec.size() && c < valueVec[r].size())
            {
                outMatrix.RCSet(valueVec[r][c], r, c);
            }
            else
            {
                outMatrix.RCSet(0, r, c);
            }
        }
    }
}

template <class T, Mushware::U32 C, Mushware::U32 R>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushMeshPreMatrix<T, C, R>& inMatrix)
{
    std::vector< std::vector<T> > valueVec(R);
    for (Mushware::U32 r=0; r<R; ++r)
    {
        valueVec[r].resize(C);
        for (Mushware::U32 c=0; c<C; ++c)
        {
            valueVec[r][c] = inMatrix.RCGet(r, c);
        }
    }
    ioOut << valueVec;
    
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
