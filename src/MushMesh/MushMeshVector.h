//%includeGuardStart {
#ifndef MUSHMESHVECTOR_H
#define MUSHMESHVECTOR_H
//%includeGuardStart } nK/gADGmzhZTGa5d81W/Tg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshVector.h
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
//%Header } kviDPnyDMDpo1Nk5cUbkVA
/*
 * $Id: MushMeshVector.h,v 1.28 2006/06/06 17:58:33 southa Exp $
 * $Log: MushMeshVector.h,v $
 * Revision 1.28  2006/06/06 17:58:33  southa
 * Ruby texture definition
 *
 * Revision 1.27  2006/06/05 11:48:25  southa
 * Noise textures
 *
 * Revision 1.26  2006/05/02 17:32:13  southa
 * Texturing
 *
 * Revision 1.25  2005/08/01 17:58:25  southa
 * Object explosion
 *
 * Revision 1.24  2005/07/19 13:44:26  southa
 * MushMesh4Chunk work
 *
 * Revision 1.23  2005/07/19 10:07:00  southa
 * Adanaxis work
 *
 * Revision 1.22  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.21  2005/06/30 14:26:36  southa
 * Adanaxis work
 *
 * Revision 1.20  2005/06/24 10:30:13  southa
 * MushGame camera work
 *
 * Revision 1.19  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.18  2005/02/27 01:01:31  southa
 * Eigenplane markers
 *
 * Revision 1.17  2005/02/26 17:53:39  southa
 * Plane sets and pairs
 *
 * Revision 1.16  2004/12/13 11:09:11  southa
 * Quaternion and vector tweaks
 *
 * Revision 1.15  2004/11/17 23:43:47  southa
 * Added outer product
 *
 * Revision 1.14  2004/10/31 09:22:51  southa
 * Added MushMeshPreMatrix
 *
 * Revision 1.13  2004/09/26 20:43:19  southa
 * TestMustl fixes
 *
 * Revision 1.12  2004/09/26 19:42:05  southa
 * Added MushMesh, fixed typenames and release target
 *
 * Revision 1.11  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.10  2004/01/02 17:31:48  southa
 * MushPie work and XML fixes
 *
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
    explicit MushMeshVector(const std::vector<T>& inVec);
	
    const T& Get(Mushware::U32 inIndex) const { BoundsCheck(inIndex); return m_value[inIndex]; }
    void Set(const T& inValue, Mushware::U32 inIndex) { BoundsCheck(inIndex); m_value[inIndex] = inValue; }
    
    const T& X(void) const { return Get(0); }
    const T& Y(void) const { return Get(1); }
    const T& Z(void) const { return Get(2); }
    const T& W(void) const { return Get(3); }
    
    void XSet(const T& inValue) { Set(inValue, 0); }
    void YSet(const T& inValue) { Set(inValue, 1); }
    void ZSet(const T& inValue) { Set(inValue, 2); }
    void WSet(const T& inValue) { Set(inValue, 3); }

    static Mushware::U32 SizeGet(void) { return D; }
    bool EqualIs(const tThis& b) const;
    bool ApproxEqual(const tThis& b, const T& inLimit) const;

    void InPlaceElementwiseMultiply(const tThis& inB);
    tThis ElementwiseProduct(const tThis& inB) const;
    Mushware::tVal Magnitude(void) const;
    Mushware::tVal MagnitudeSquared(void) const;
    void InPlaceNormalise(void);
    void ToAdditiveIdentitySet(void);
    void ToMultiplicativeIdentitySet(void);
    tThis Floor(void) const;
	tThis Ceil(void) const;
	
    static const tThis AdditiveIdentity(void);
    static const tThis MultiplicativeIdentity(void);
    
    // Unchecked array operators
    const T& operator[](Mushware::U32 inIndex) const { return m_value[inIndex]; }

protected:
    void BoundsCheck(Mushware::U32 i) const
    {
#ifdef MUSHMESH_DEBUG
        if (i >= D) MushcoreUtil::BoundaryThrow(i, D);
#endif
    }

#ifdef MUSHWARE_NO_TEMPLATE_FRIENDS
	/* Make private data public if template friends are not allowed.
	 * Other builds will catch disallowed access
	 */
public:
#endif
    T m_value[D]; // Data values.  Subclasses allowed to access for efficiency

private:

#ifndef MUSHWARE_NO_TEMPLATE_FRIENDS
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
    template <class fnT, Mushware::U32 fnD> friend const MushMeshVector<fnT, fnD> operator-(const MushMeshVector<fnT, fnD>& a);
#endif
};

template <class T, Mushware::U32 D>
MushMeshVector<T, D>::MushMeshVector(const std::vector<T>& inVec)
{
	Mushware::U32 vecSize = inVec.size();
	for (Mushware::U32 i=0; i<D; ++i)
    {
		if (i < vecSize)
		{
			m_value[i] = inVec[i];	
		}
		else
		{
			m_value[i] = T();	
		}
	}
}

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

template <class T, Mushware::U32 D>
inline bool
MushMeshVector<T, D>::ApproxEqual(const MushMeshVector& b, const T& inLimit) const
{
    for (Mushware::U32 i=0; i<D; ++i)
    {
        if (m_value[i] - b.m_value[i] > inLimit ||
            b.m_value[i] - m_value[i] > inLimit)
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

// Unary
template <class T, Mushware::U32 D>
inline const MushMeshVector<T, D>
operator-(const MushMeshVector<T, D>& a)
{
    MushMeshVector<T, D> retValue;
    for (Mushware::U32 i=0; i<D; ++i)
    {
        retValue.Set(-a.m_value[i], i);
    }
    return retValue;
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

// Inner product
template <class T, Mushware::U32 D>
inline T
operator*(const MushMeshVector<T, D>& a, const MushMeshVector<T, D>& b)
{
    T retValue = a[0]*b[0]; // Avoid using 0
    for (Mushware::U32 i=1; i<D; ++i) // Start at 1
    {
        retValue += a[i]*b[i];
    }
    return retValue;
}

// Functions which do the same thing as operators

template <class T, Mushware::U32 D>
inline void
MushMeshVector<T, D>::InPlaceElementwiseMultiply(const tThis& inB)
{
    for (Mushware::U32 i=0; i<D; ++i)
    {
        m_value[i] *= inB[i];
    }
}

template <class T, Mushware::U32 D>
inline typename MushMeshVector<T, D>::tThis
MushMeshVector<T, D>::ElementwiseProduct(const tThis& inB) const
{
    tThis retVal;
    for (Mushware::U32 i=0; i<D; ++i)
    {
        retVal.Set(m_value[i] * inB[i], i);
    }
    return retVal;
}

template <class T, Mushware::U32 D>
inline Mushware::tVal
MushMeshVector<T, D>::MagnitudeSquared(void) const
{
    Mushware::tVal retVal2 = 0;
    for (Mushware::U32 i=0; i<D; ++i)
    {
        retVal2 += m_value[i] * m_value[i];
    }
    return retVal2;
}

template <class T, Mushware::U32 D>
inline Mushware::tVal
MushMeshVector<T, D>::Magnitude(void) const
{
    return std::sqrt(MagnitudeSquared());
}

template <class T, Mushware::U32 D>
inline void
MushMeshVector<T, D>::InPlaceNormalise(void)
{
    *this /= Magnitude();
}

template <class T, Mushware::U32 D>
inline void
MushMeshVector<T, D>::ToAdditiveIdentitySet(void)
{
    for (Mushware::U32 i=0; i<D; ++i)
    {
        m_value[i] = 0;
    }
}

template <class T, Mushware::U32 D>
inline MushMeshVector<T, D>
MushMeshVector<T, D>::Floor(void) const
{
	MushMeshVector<T, D> retVal;
    for (Mushware::U32 i=0; i<D; ++i)
    {
        retVal.Set(std::floor(Get(i)), i);
    }
	return retVal;
}

template <class T, Mushware::U32 D>
inline MushMeshVector<T, D>
MushMeshVector<T, D>::Ceil(void) const
{
	tThis retVal;
    for (Mushware::U32 i=0; i<D; ++i)
    {
        retVal[i] = std::ceil(m_value[i]);
    }
	return retVal;
}

template <class T, Mushware::U32 D>
inline const MushMeshVector<T, D>
MushMeshVector<T, D>::AdditiveIdentity(void)
{
    MushMeshVector<T, D> retVal;
    for (Mushware::U32 i=0; i<D; ++i)
    {
        retVal.Set(0, i);
    }
    return retVal;
}

template <class T, Mushware::U32 D>
inline const MushMeshVector<T, D>
MushMeshVector<T, D>::MultiplicativeIdentity(void)
{
    MushMeshVector<T, D> retVal;
    for (Mushware::U32 i=0; i<D; ++i)
    {
        retVal.Set(1, i);
    }
    return retVal;
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
