//%includeGuardStart {
#ifndef MUSHMESHQUATERNION_H
#define MUSHMESHQUATERNION_H
//%includeGuardStart } MfXOjt39LkittUvhd8Gq+A
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshQuaternion.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } rIcABVZ9p6NF41BMv39r2Q
/*
 * $Id: MushMeshQuaternion.h,v 1.6 2005/02/03 21:03:01 southa Exp $
 * $Log: MushMeshQuaternion.h,v $
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
        m_value[0] = in0;
        m_value[1] = in1;
        m_value[2] = in2;
        m_value[3] = in3;
    }
    
    void PreMultiplyBy(const MushMeshQuaternion<T>& inQuat);
    void PostMultiplyBy(const MushMeshQuaternion<T>& inQuat);
    MushMeshQuaternion<T> ConjugateGet(void) const;
    void PreMultiplyVector(tBase& ioVec) const;
    void PostMultiplyVector(tBase& ioVec) const;

    static MushMeshQuaternion AdditiveIdentityGet(void) { return MushMeshQuaternion(0,0,0,0); }
    static MushMeshQuaternion MultiplicativeIdentityGet(void) { return MushMeshQuaternion(1,0,0,0); }
    
};

template <class T>
inline
MushMeshQuaternion<T>::MushMeshQuaternion(const MushMeshVector<T, 4>& inVec)
{
    m_value[0] = inVec.Get(0);
    m_value[1] = inVec.Get(1);
    m_value[2] = inVec.Get(2);
    m_value[3] = inVec.Get(3);
}

template <class T>
inline void
MushMeshQuaternion<T>::PreMultiplyBy(const MushMeshQuaternion<T>& inQuat)
{
    T a = inQuat.X();
    T b = inQuat.Y();
    T c = inQuat.Z();
    T d = inQuat.W();
    T e = m_value[0];
    T f = m_value[1];
    T g = m_value[2];
    T h = m_value[3];
    
    // Apply expansion of (a+bi+cj+dk)(e+fi+gj+hk)
    
    m_value[0] = a*e - b*f - c*g - d*h;
    m_value[1] = a*f + b*e + c*h - d*g;
    m_value[2] = a*g + c*e - b*h + d*f;
    m_value[3] = a*h + d*e + b*g - c*f;
}

template <class T>
inline void
MushMeshQuaternion<T>::PostMultiplyBy(const MushMeshQuaternion<T>& inQuat)
{
    T a = m_value[0];
    T b = m_value[1];
    T c = m_value[2];
    T d = m_value[3];
    T e = inQuat.X();
    T f = inQuat.Y();
    T g = inQuat.Z();
    T h = inQuat.W();
    
    m_value[0] = a*e - b*f - c*g - d*h;
    m_value[1] = a*f + b*e + c*h - d*g;
    m_value[2] = a*g + c*e - b*h + d*f;
    m_value[3] = a*h + d*e + b*g - c*f;
}


template <class T>
inline void
MushMeshQuaternion<T>::PreMultiplyVector(tBase& ioVec) const
{
    T a = m_value[0];
    T b = m_value[1];
    T c = m_value[2];
    T d = m_value[3];
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
    T e = m_value[0];
    T f = m_value[1];
    T g = m_value[2];
    T h = m_value[3];
    
    // Apply expansion of (a+bi+cj+dk)(e+fi+gj+hk)
    
    ioVec.XSet(a*e - b*f - c*g - d*h);
    ioVec.YSet(a*f + b*e + c*h - d*g);
    ioVec.ZSet(a*g + c*e - b*h + d*f);
    ioVec.WSet(a*h + d*e + b*g - c*f);
}

template <class T>
inline MushMeshQuaternion<T>
MushMeshQuaternion<T>::ConjugateGet(void) const
{
    return MushMeshQuaternion<T>(m_value[0], -m_value[1], -m_value[2], -m_value[3]);
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
