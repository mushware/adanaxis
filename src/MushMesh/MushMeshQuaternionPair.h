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
 * $Id: MushMeshQuaternionPair.h,v 1.3 2005/02/27 01:01:31 southa Exp $
 * $Log: MushMeshQuaternionPair.h,v $
 * Revision 1.3  2005/02/27 01:01:31  southa
 * Eigenplane markers
 *
 * Revision 1.2  2005/02/10 12:34:06  southa
 * Template fixes
 *
 * Revision 1.1  2005/02/03 21:03:01  southa
 * Build fixes
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshQuaternion.h"

//:generate inline ostream basic
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
    void InPlaceNormalise(void);
    
    MushMeshQuaternionPair<T> ConjugateGet(void) const;
        
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
    
    void ObjectRead(MushcoreXMLIStream& ioIn);
    
private:
    MushMeshQuaternion<T> m_first; // :readwrite
    MushMeshQuaternion<T> m_second; // :readwrite
    
//%classPrototypes {
public:
    const MushMeshQuaternion<T>& First(void) const { return m_first; }
    void FirstSet(const MushMeshQuaternion<T>& inValue) { m_first=inValue; }
    const MushMeshQuaternion<T>& Second(void) const { return m_second; }
    void SecondSet(const MushMeshQuaternion<T>& inValue) { m_second=inValue; }
    bool AutoEquals(const MushMeshQuaternionPair& inObj) const;
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } 4abaurIVgYYyfv8JFiCIsw
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

template<class T>
inline void
MushMeshQuaternionPair<T>::InPlaceNormalise()
{
    m_first.InPlaceNormalise();
    m_second.InPlaceNormalise();
}

template<class T>
inline MushMeshQuaternionPair<T>
MushMeshQuaternionPair<T>::ConjugateGet(void) const
{
    return MushMeshQuaternionPair(m_first.ConjugateGet(), m_second.ConjugateGet());
}


// Stream operators

template <class T>
inline void
MushMeshQuaternionPair<T>::ObjectRead(MushcoreXMLIStream& ioIn)
{
    if (ioIn.ByteTake() != '(') ioIn.Throw("Expecting '('");
    ioIn >> m_first;
    if (ioIn.ByteTake() != ',') ioIn.Throw("Expecting ','");
    ioIn >> m_second;
    if (ioIn.ByteTake() != ')') ioIn.Throw("Expecting ')'");
}

template <class T>
inline void
operator>>(MushcoreXMLIStream& ioIn, MushMeshQuaternionPair<T>& outObj)
{
    outObj.ObjectRead(ioIn);
}

template <class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushMeshQuaternionPair<T>& inObj)
{
    std::string localTag = ioOut.OpeningTagWrite();
    
    ioOut.OStreamGet() << '(';
    ioOut << inObj.First();
    ioOut.OStreamGet() << ',';
    ioOut << inObj.Second();
    ioOut.OStreamGet() << ')';
    
    ioOut.ClosingTagWrite(localTag);
    
    return ioOut;
}

namespace Mushware
{
    typedef MushMeshQuaternionPair<Mushware::tVal> tQValPair;
};
//%inlineHeader {
template<class T>
inline bool
operator==(const MushMeshQuaternionPair<T>& inA, const MushMeshQuaternionPair<T>& inB)
{
    return inA.AutoEquals(inB);
}
template<class T>
inline bool
operator!=(const MushMeshQuaternionPair<T>& inA, const MushMeshQuaternionPair<T>& inB)
{
    return !inA.AutoEquals(inB);
}
template<class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshQuaternionPair<T>& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
template<class T>
inline bool
MushMeshQuaternionPair<T>::AutoEquals(const MushMeshQuaternionPair& inObj) const
{
    return 1
        && (m_first == inObj.m_first)
        && (m_second == inObj.m_second)
    ;
}
template<class T>
inline void
MushMeshQuaternionPair<T>::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "first=" << m_first << ", ";
    ioOut << "second=" << m_second;
    ioOut << "]";
}
//%inlineHeader } nX6MX/jBxb00ANRGRFi5Iw

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
