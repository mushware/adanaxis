//%includeGuardStart {
#ifndef MUSHMESHQUATERNIONPAIR_H
#define MUSHMESHQUATERNIONPAIR_H
//%includeGuardStart } aHli1TzqKemOiocJU2MN1w
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshQuaternionPair.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 7ZSBQbATpwtej064t1GYDw
/*
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"

#include "MushMeshQuaternion.h"

//:generate
template<class T>
class MushMeshQuaternionPair
{
public:
    MushMeshQuaternionPair() {}
    MushMeshQuaternionPair(const MushMeshQuaternion<T>& inFirst, const MushMeshQuaternion<T>& inSecond) :
        m_first(inFirst),
        m_second(inSecond)
    {}
    
    void InnerMultiplyBy(const MushMeshQuaternionPair& inVal);
    void OuterMultiplyBy(const MushMeshQuaternionPair& inVal);
    
    void InPlaceRotate(Mushware::t4Val& ioVec) const;
    
    static MushMeshQuaternionPair AdditiveIdentityGet()
    {
        return MushMeshQuaternionPair(MushMeshQuaternion<T>::AdditiveIdentityGet(),
                                      MushMeshQuaternion<T>::AdditiveIdentityGet());
    }
    static MushMeshQuaternionPair MultiplicativeIdentityGet()
    {
        return MushMeshQuaternionPair(MushMeshQuaternion<T>::MultiplicativeIdentityGet(),
                                      MushMeshQuaternion<T>::MultiplicativeIdentityGet());
    }
    static MushMeshQuaternionPair RotationIdentityGet()
    {
        return MultiplicativeIdentityGet();
    }
    
private:
    MushMeshQuaternion<T> m_first; // :readwrite
    MushMeshQuaternion<T> m_second; // :readwrite
    
//%classPrototypes {
public:
    const MushMeshQuaternion<T>& First(void) const { return m_first; }
    void FirstSet(const MushMeshQuaternion<T>& inValue) { m_first=inValue; }
    const MushMeshQuaternion<T>& Second(void) const { return m_second; }
    void SecondSet(const MushMeshQuaternion<T>& inValue) { m_second=inValue; }
//%classPrototypes } 8oNfFalnrQLgtQYcgRkIsQ
};

template<class T>
inline void
MushMeshQuaternionPair<T>::InnerMultiplyBy(const MushMeshQuaternionPair<T>& inVal)
{
    m_first.PostMultiplyBy(inVal.First());
    m_second.PreMultiplBy(inVal.Second());
}

template<class T>
inline void
MushMeshQuaternionPair<T>::OuterMultiplyBy(const MushMeshQuaternionPair<T>& inVal)
{
    m_first.PreMultiplyBy(inVal.First());
    m_second.PostMultiplyBy(inVal.Second());
}

template<class T>
inline void
MushMeshQuaternionPair<T>::InPlaceRotate(Mushware::t4Val& ioVec) const
{
    m_first.PreMultiplyVector(ioVec);
    m_second.PostMultiplyVector(ioVec);
}

namespace Mushware
{
    typedef MushMeshQuaternionPair<Mushware::tVal> tQValPair;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
