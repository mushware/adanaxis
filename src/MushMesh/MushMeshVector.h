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
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } nxVjK2Mc2cZYPq+0IdUZdQ
/*
 * $Id: MushMeshVector.h,v 1.9 2004/01/02 11:56:59 southa Exp $
 * $Log: MushMeshVector.h,v $
 * Revision 1.9  2004/01/02 11:56:59  southa
 * MushPie created
 *
 * Revision 1.8  2003/10/20 13:02:54  southa
 * Patch fixes and testing
 *
 * Revision 1.7  2003/10/18 20:28:38  southa
 * Subdivision speed tests
 *
 * Revision 1.6  2003/10/17 12:27:19  southa
 * Line end fixes and more mesh work
 *
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
    explicit MushMeshVector(const T& in0)
    {
        MUSHCOREASSERT(D >= 1);
        m_value[0] = in0;
    }
    MushMeshVector(const T& in0, const T& in1)
    {
        MUSHCOREASSERT(D >= 2);
        m_value[0] = in0;
        m_value[1] = in1;
    }
    MushMeshVector(const T& in0, const T& in1, const T& in2)
    {
        MUSHCOREASSERT(D >= 3);
        m_value[0] = in0;
        m_value[1] = in1;
        m_value[2] = in2;
    }
    MushMeshVector(const T& in0, const T& in1, const T& in2, const T& in3)
    {
        MUSHCOREASSERT(D >= 4);
        m_value[0] = in0;
        m_value[1] = in1;
        m_value[2] = in2;
        m_value[3] = in3;
    }

    const T& Get(Mushware::U32 inIndex) const { BoundsCheck(inIndex); return m_value[inIndex]; }
    T& WRefGet(Mushware::U32 inIndex) { BoundsCheck(inIndex); return m_value[inIndex]; }
    void Set(const T& inValue, Mushware::U32 inIndex) { BoundsCheck(inIndex); m_value[inIndex] = inValue; }
    
    const T& X(void) const { return Get(0); }
    const T& Y(void) const { return Get(1); }
    const T& Z(void) const { return Get(2); }

    void XSet(const T& inValue) { Set(inValue, 0); }
    void YSet(const T& inValue) { Set(inValue, 1); }
    void ZSet(const T& inValue) { Set(inValue, 2); }

    static Mushware::U32 SizeGet(void) { return D; }
    bool EqualIs(const tThis& b) const;

    // Unchecked array operators
    const T& operator[](Mushware::U32 inIndex) const { return m_value[inIndex]; }
    T& operator[](Mushware::U32 inIndex) { return m_value[inIndex]; }

protected:
    void BoundsCheck(Mushware::U32 i) const { if (i >= D) MushMeshUtils::BoundaryThrow(i, D); }

private:
    T m_value[D];

    // Declare various operators which need acess to m_value as friends
    template <class fnT, Mushware::U32 fnD, class fnI> friend const MushMeshVector<fnT, fnD>& operator+=(MushMeshVector<fnT, fnD>& a, const fnI& b);
    template <class fnT, Mushware::U32 fnD, class fnI> friend const MushMeshVector<fnT, fnD>& operator-=(MushMeshVector<fnT, fnD>& a, const fnI& b);
    template <class fnT, Mushware::U32 fnD, class fnI> friend const MushMeshVector<fnT, fnD>& operator*=(MushMeshVector<fnT, fnD>& a, const fnI& b);
    template <class fnT, Mushware::U32 fnD, class fnI> friend const MushMeshVector<fnT, fnD>& operator/=(MushMeshVector<fnT, fnD>& a, const fnI& b);
    template <class fnT, Mushware::U32 fnD> friend const MushMeshVector<fnT, fnD>& operator+=(MushMeshVector<fnT, fnD>& a, const MushMeshVector<fnT, fnD>& b);
    template <class fnT, Mushware::U32 fnD> friend const MushMeshVector<fnT, fnD>& operator-=(MushMeshVector<fnT, fnD>& a, const MushMeshVector<fnT, fnD>& b);
    template <class fnT, Mushware::U32 fnD> friend const MushMeshVector<fnT, fnD>& operator*=(MushMeshVector<fnT, fnD>& a, const MushMeshVector<fnT, fnD>& b);
    template <class fnT, Mushware::U32 fnD> friend const MushMeshVector<fnT, fnD>& operator/=(MushMeshVector<fnT, fnD>& a, const MushMeshVector<fnT, fnD>& b);
    template <class fnT, Mushware::U32 fnD> friend bool operator==(const MushMeshVector<fnT, fnD>& a, const MushMeshVector<fnT, fnD>& b);
    template <class fnT, Mushware::U32 fnD> friend bool operator!=(const MushMeshVector<fnT, fnD>& a, const MushMeshVector<fnT, fnD>& b);
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
        ioOut << inVec.Get(i);
        if (i+1 < D)
        {
            ioOut << ", ";
        }
    }
    ioOut << ']';
    return ioOut;
}

template <class T, Mushware::U32 D>
inline void
operator>>(MushcoreXMLIStream& ioIn, MushMeshVector<T, D>& outObj)
{
    std::vector<T> valueVec;
    ioIn >> valueVec;
    for (Mushware::U32 i=0; i<D; ++i)
    {
        if (i < valueVec.size())
        {
            outObj.Set(valueVec[i], i);
        }
        else
        {
            outObj.Set(0, i);
        }
    }
}

template <class T, Mushware::U32 D>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushMeshVector<T, D>& inObj)
{
    std::vector<T> valueVec(D);
    for (Mushware::U32 i=0; i<D; ++i)
    {
        valueVec[i] = inObj.Get(i);
    }
    ioOut << valueVec;
    return ioOut;
}

// Convenient types
namespace Mushware
{
    typedef MushMeshVector<Mushware::U32, 2> t2U32;
    typedef MushMeshVector<Mushware::U32, 3> t3U32;
    typedef MushMeshVector<Mushware::U32, 4> t4U32;
    
    typedef MushMeshVector<Mushware::tVal, 2> t2Val;
    typedef MushMeshVector<Mushware::tVal, 3> t3Val;
    typedef MushMeshVector<Mushware::tVal, 4> t4Val;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
