//%includeGuardStart {
#ifndef MUSHMESHVECTOR_H
#define MUSHMESHVECTOR_H
//%includeGuardStart } nK/gADGmzhZTGa5d81W/Tg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshVector.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } JlxNvBXL6uC0NayW/SROGA
/*
 * $Id: MushMeshVector.h,v 1.5 2003/10/15 12:26:59 southa Exp $
 * $Log: MushMeshVector.h,v $
 * Revision 1.5  2003/10/15 12:26:59  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.4  2003/10/15 11:54:54  southa
 * MushMeshArray neighbour testing and subdivision
 *
 * Revision 1.3  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 * Revision 1.2  2003/10/14 13:07:26  southa
 * MushMesh vector creation
 *
 * Revision 1.1  2003/10/14 10:46:05  southa
 * MeshMover creation
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshUtils.h"

template <class T, Mushware::U32 D>
class MushMeshVector
{
public:
    typedef MushMeshVector<T, D> tThis;

    MushMeshVector() {}
    MushMeshVector(const T& in0, const T& in1)
    {
        MUSHCOREASSERT(D >= 2);
        m_value[0] = in0;
        m_value[1] = in1;
    }

    const T& ValueGet(Mushware::U32 inIndex) const { BoundsCheck(inIndex); return m_value[inIndex]; }
    void ValueSet(const T& inValue, Mushware::U32 inIndex) { BoundsCheck(inIndex); m_value[inIndex] = inValue; }
    
    const T& X(void) const { return ValueGet(0); }
    const T& Y(void) const { return ValueGet(1); }
    const T& Z(void) const { return ValueGet(2); }

    void XSet(const T& inValue) { ValueSet(inValue, 0); }
    void YSet(const T& inValue) { ValueSet(inValue, 1); }
    void ZSet(const T& inValue) { ValueSet(inValue, 2); }

    bool EqualIs(const tThis& b) const;

protected:
    void BoundsCheck(Mushware::U32 i) const { if (i >= D) MushMeshUtils::BoundaryThrow(i, D); }

public:
    T m_value[D]; 
};

// Operator helper functions

template <class T, Mushware::U32 D>
inline bool
MushMeshVector<T, D>::EqualIs(const MushMeshVector& b) const
{
    for (Mushware::U32 i=0; i<D; ++i)
    {
        if (m_value[i] != b.m_value[i])
        {
            return false;
        }
    }
    return true;
}

// Bound operators

// Vector with value

template <class T, Mushware::U32 D, class I>
inline const MushMeshVector<T, D>&
operator+=(MushMeshVector<T, D>& a, const I& b)
{
    for (Mushware::U32 i=0; i<D; ++i)
    {
        a.m_value[i] += b;
    }
    return a;
}

template <class T, Mushware::U32 D, class I>
inline const MushMeshVector<T, D>&
operator-=(MushMeshVector<T, D>& a, const I& b)
{
    for (Mushware::U32 i=0; i<D; ++i)
    {
        a.m_value[i] -= b;
    }
    return a;
}

template <class T, Mushware::U32 D, class I>
inline const MushMeshVector<T, D>&
operator*=(MushMeshVector<T, D>& a, const I& b)
{
    for (Mushware::U32 i=0; i<D; ++i)
    {
        a.m_value[i] *= b;
    }
    return a;
}

template <class T, Mushware::U32 D, class I>
inline const MushMeshVector<T, D>&
operator/=(MushMeshVector<T, D>& a, const I& b)
{
    for (Mushware::U32 i=0; i<D; ++i)
    {
        a.m_value[i] /= b;
    }
    return a;
}


// Vector with vector
template <class T, Mushware::U32 D>
inline const MushMeshVector<T, D>&
operator+=(MushMeshVector<T, D>& a, const MushMeshVector<T, D>& b)
{
    for (Mushware::U32 i=0; i<D; ++i)
    {
        a.m_value[i] += b.m_value[i];
    }
    return a;
}

template <class T, Mushware::U32 D>
inline const MushMeshVector<T, D>&
operator-=(MushMeshVector<T, D>& a, const MushMeshVector<T, D>& b)
{
    for (Mushware::U32 i=0; i<D; ++i)
    {
        a.m_value[i] -= b.m_value[i];
    }
    return a;
}

template <class T, Mushware::U32 D>
inline const MushMeshVector<T, D>&
operator*=(MushMeshVector<T, D>& a, const MushMeshVector<T, D>& b)
{
    for (Mushware::U32 i=0; i<D; ++i)
    {
        a.m_value[i] *= b.m_value[i];
    }
    return a;
}

template <class T, Mushware::U32 D>
inline const MushMeshVector<T, D>&
operator/=(MushMeshVector<T, D>& a, const MushMeshVector<T, D>& b)
{
    for (Mushware::U32 i=0; i<D; ++i)
    {
        a.m_value[i] /= b.m_value[i];
    }
    return a;
}

// Free operators

template <class T, Mushware::U32 D>
inline bool
operator==(const MushMeshVector<T, D>& a, const MushMeshVector<T, D>& b)
{
    return a.EqualIs(b);
}

template <class T, Mushware::U32 D>
inline bool
operator!=(const MushMeshVector<T, D>& a, const MushMeshVector<T, D>& b)
{
    return !a.EqualIs(b);
}

// Vector with value
template <class T, Mushware::U32 D, class I>
inline MushMeshVector<T, D>
operator+(const MushMeshVector<T, D>& a, const I& b)
{
    MushMeshVector<T, D> retValue(a);
    retValue += b;
    return retValue;
}

template <class T, Mushware::U32 D, class I>
inline MushMeshVector<T, D>
operator-(const MushMeshVector<T, D>& a, const I& b)
{
    MushMeshVector<T, D> retValue(a);
    retValue -= b;
    return retValue;
}

template <class T, Mushware::U32 D, class I>
inline MushMeshVector<T, D>
operator*(const MushMeshVector<T, D>& a, const I& b)
{
    MushMeshVector<T, D> retValue(a);
    retValue *= b;
    return retValue;
}

template <class T, Mushware::U32 D, class I>
inline MushMeshVector<T, D>
operator/(const MushMeshVector<T, D>& a, const I& b)
{
    MushMeshVector<T, D> retValue(a);
    retValue /= b;
    return retValue;
}

// Value with a vector
// Only + and *.  Non-commutative operators would need further assignment operators
template <class T, Mushware::U32 D, class I>
inline MushMeshVector<T, D>
operator+(const I& a, const MushMeshVector<T, D>& b)
{
    MushMeshVector<T, D> retValue(b);
    retValue += a;
    return retValue;
}

template <class T, Mushware::U32 D, class I>
inline MushMeshVector<T, D>
operator*(const I& a, const MushMeshVector<T, D>& b)
{
    MushMeshVector<T, D> retValue(b);
    retValue *= a;
    return retValue;
}

// Vector with vector
template <class T, Mushware::U32 D>
inline MushMeshVector<T, D>
operator+(const MushMeshVector<T, D>& a, const MushMeshVector<T, D>& b)
{
    MushMeshVector<T, D> retValue(a);
    retValue += b;
    return retValue;
}

template <class T, Mushware::U32 D>
inline MushMeshVector<T, D>
operator-(const MushMeshVector<T, D>& a, const MushMeshVector<T, D>& b)
{
    MushMeshVector<T, D> retValue(a);
    retValue -= b;
    return retValue;
}

template <class T, Mushware::U32 D>
inline MushMeshVector<T, D>
operator*(const MushMeshVector<T, D>& a, const MushMeshVector<T, D>& b)
{
    MushMeshVector<T, D> retValue(a);
    retValue *= b;
    return retValue;
}

template <class T, Mushware::U32 D>
inline MushMeshVector<T, D>
operator/(const MushMeshVector<T, D>& a, const MushMeshVector<T, D>& b)
{
    MushMeshVector<T, D> retValue(a);
    retValue /= b;
    return retValue;
}

// Stream operators

template <class T, Mushware::U32 D>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshVector<T, D>& inVec)
{
    ioOut << '[';
    for (Mushware::U32 i=0; i<D; ++i)
    {
        ioOut << inVec.ValueGet(i);
        if (i+1 < D)
        {
            ioOut << ", ";
        }
    }
    ioOut << ']';
    return ioOut;
}

// Convenient types
namespace Mushware
{
    typedef MushMeshVector<Mushware::U32, 2> t2U32;
    typedef MushMeshVector<Mushware::U32, 3> t3U32;

    typedef MushMeshVector<Mushware::tVal, 2> t2Val;
    typedef MushMeshVector<Mushware::tVal, 3> t3Val;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
