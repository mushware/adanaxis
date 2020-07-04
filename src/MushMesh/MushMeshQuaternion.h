//%includeGuardStart {
#ifndef MUSHMESHQUATERNION_H
#define MUSHMESHQUATERNION_H
//%includeGuardStart } MfXOjt39LkittUvhd8Gq+A
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshQuaternion.h
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
//%Header } pR+nQxoKZyAmgYpcpg8zgw
/*
 * $Id: MushMeshQuaternion.h,v 1.13 2006/06/01 15:39:32 southa Exp $
 * $Log: MushMeshQuaternion.h,v $
 * Revision 1.13  2006/06/01 15:39:32  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/07/19 10:07:06  southa
 * Adanaxis work
 *
 * Revision 1.11  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.10  2005/05/19 13:02:10  southa
 * Mac release work
 *
 * Revision 1.9  2005/05/18 15:53:27  southa
 * Made buildable using gcc 4.0/Mac OS X 10.4
 *
 * Revision 1.8  2005/03/08 01:24:09  southa
 * Quaternion slerp between orientations
 *
 * Revision 1.7  2005/02/27 01:01:31  southa
 * Eigenplane markers
 *
 * Revision 1.6  2005/02/03 21:03:01  southa
 * Build fixes
 *
 * Revision 1.5  2004/12/12 10:55:37  southa
 * Quaternion conversions
 *
 * Revision 1.4  2004/12/06 20:44:17  southa
 * Quaternion and matrix operations
 *
 * Revision 1.3  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 * Revision 1.2  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshVector.h"

template<class T>
class MushMeshQuaternion : public MushMeshVector<T, 4>
{
public:
    typedef MushMeshVector<T, 4> tBase;
    
    MushMeshQuaternion() {}
    explicit MushMeshQuaternion(const MushMeshVector<T, 4>& inVec);
    MushMeshQuaternion(const T& in0, const T& in1, const T& in2, const T& in3)
    {
        this->m_value[0] = in0;
        this->m_value[1] = in1;
        this->m_value[2] = in2;
        this->m_value[3] = in3;
    }
    
    void PreMultiplyBy(const MushMeshQuaternion<T>& inQuat);
    void PostMultiplyBy(const MushMeshQuaternion<T>& inQuat);
    MushMeshQuaternion<T> Conjugate(void) const;
    void InPlaceConjugate(void);
    void PreMultiplyVector(tBase& ioVec) const;
    void PostMultiplyVector(tBase& ioVec) const;
    
    static MushMeshQuaternion AdditiveIdentity(void) { return MushMeshQuaternion(0,0,0,0); }
    static MushMeshQuaternion MultiplicativeIdentity(void) { return MushMeshQuaternion(1,0,0,0); }
    
};

template <class T>
inline
MushMeshQuaternion<T>::MushMeshQuaternion(const MushMeshVector<T, 4>& inVec)
{
    this->m_value[0] = inVec.Get(0);
    this->m_value[1] = inVec.Get(1);
    this->m_value[2] = inVec.Get(2);
    this->m_value[3] = inVec.Get(3);
}

template <class T>
inline void
MushMeshQuaternion<T>::PreMultiplyBy(const MushMeshQuaternion<T>& inQuat)
{
    T a = inQuat.X();
    T b = inQuat.Y();
    T c = inQuat.Z();
    T d = inQuat.W();
    T e = this->m_value[0];
    T f = this->m_value[1];
    T g = this->m_value[2];
    T h = this->m_value[3];
    
    // Apply expansion of (a+bi+cj+dk)(e+fi+gj+hk)
    
    this->m_value[0] = a*e - b*f - c*g - d*h;
    this->m_value[1] = a*f + b*e + c*h - d*g;
    this->m_value[2] = a*g + c*e - b*h + d*f;
    this->m_value[3] = a*h + d*e + b*g - c*f;
}

template <class T>
inline void
MushMeshQuaternion<T>::PostMultiplyBy(const MushMeshQuaternion<T>& inQuat)
{
    T a = this->m_value[0];
    T b = this->m_value[1];
    T c = this->m_value[2];
    T d = this->m_value[3];
    T e = inQuat.X();
    T f = inQuat.Y();
    T g = inQuat.Z();
    T h = inQuat.W();
    
    this->m_value[0] = a*e - b*f - c*g - d*h;
    this->m_value[1] = a*f + b*e + c*h - d*g;
    this->m_value[2] = a*g + c*e - b*h + d*f;
    this->m_value[3] = a*h + d*e + b*g - c*f;
}


template <class T>
inline void
MushMeshQuaternion<T>::PreMultiplyVector(tBase& ioVec) const
{
    T a = this->m_value[0];
    T b = this->m_value[1];
    T c = this->m_value[2];
    T d = this->m_value[3];
    T e = ioVec.X();
    T f = ioVec.Y();
    T g = ioVec.Z();
    T h = ioVec.W();
    
    ioVec.XSet(a*e - b*f - c*g - d*h);
    ioVec.YSet(a*f + b*e + c*h - d*g);
    ioVec.ZSet(a*g + c*e - b*h + d*f);
    ioVec.WSet(a*h + d*e + b*g - c*f);
}

template <class T>
inline void
MushMeshQuaternion<T>::PostMultiplyVector(tBase& ioVec) const
{
    T a = ioVec.X();
    T b = ioVec.Y();
    T c = ioVec.Z();
    T d = ioVec.W();
    T e = this->m_value[0];
    T f = this->m_value[1];
    T g = this->m_value[2];
    T h = this->m_value[3];
    
    // Apply expansion of (a+bi+cj+dk)(e+fi+gj+hk)
    
    ioVec.XSet(a*e - b*f - c*g - d*h);
    ioVec.YSet(a*f + b*e + c*h - d*g);
    ioVec.ZSet(a*g + c*e - b*h + d*f);
    ioVec.WSet(a*h + d*e + b*g - c*f);
}

template <class T>
inline MushMeshQuaternion<T>
MushMeshQuaternion<T>::Conjugate(void) const
{
    return MushMeshQuaternion<T>(this->m_value[0], -this->m_value[1], -this->m_value[2], -this->m_value[3]);
}

template <class T>
inline void
MushMeshQuaternion<T>::InPlaceConjugate(void)
{
    this->m_value[1] = -this->m_value[1];
    this->m_value[2] = -this->m_value[2];
    this->m_value[3] = -this->m_value[3];
}

// Free operators

// Quaternion product
template <class T>
inline MushMeshQuaternion<T>
operator*(const MushMeshQuaternion<T>& a, const MushMeshQuaternion<T>& b)
{
    MushMeshQuaternion<T> retValue = a;

    retValue.PostMultiplyBy(b);
    
    return retValue;
}

namespace Mushware
{
    typedef MushMeshQuaternion<Mushware::tVal> tQVal;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
