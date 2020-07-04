//%includeGuardStart {
#ifndef MUSHMESHQUATERNIONPAIR_H
#define MUSHMESHQUATERNIONPAIR_H
//%includeGuardStart } aHli1TzqKemOiocJU2MN1w
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshQuaternionPair.h
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
//%Header } OEofZZhS00qJwcSriN7ebA
/*
 * $Id: MushMeshQuaternionPair.h,v 1.14 2006/06/14 11:20:07 southa Exp $
 * $Log: MushMeshQuaternionPair.h,v $
 * Revision 1.14  2006/06/14 11:20:07  southa
 * Ruby mesh generation
 *
 * Revision 1.13  2006/06/01 15:39:32  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/08/01 17:58:25  southa
 * Object explosion
 *
 * Revision 1.11  2005/07/30 19:06:15  southa
 * Collision checking
 *
 * Revision 1.10  2005/07/19 10:07:00  southa
 * Adanaxis work
 *
 * Revision 1.9  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.8  2005/07/14 16:55:08  southa
 * Mesh library work
 *
 * Revision 1.7  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.6  2005/06/24 10:30:13  southa
 * MushGame camera work
 *
 * Revision 1.5  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.4  2005/03/08 01:24:09  southa
 * Quaternion slerp between orientations
 *
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

//:generate inline nonvirtual ostream basic
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
    
    void VectorRotate(Mushware::t4Val& ioVec) const;
    Mushware::t4Val RotatedVector(const Mushware::t4Val& inVec) const;
    
    void InPlaceNormalise(void);
    void ToRotationIdentitySet(void);
    
    MushMeshQuaternionPair<T> Conjugate(void) const;
    void InPlaceConjugate(void);
        
    static MushMeshQuaternionPair AdditiveIdentity(void)
    {
        return MushMeshQuaternionPair(MushMeshQuaternion<T>::AdditiveIdentity(),
                                      MushMeshQuaternion<T>::AdditiveIdentity());
    }
    static MushMeshQuaternionPair MultiplicativeIdentity()
    {
        return MushMeshQuaternionPair(MushMeshQuaternion<T>::MultiplicativeIdentity(),
                                      MushMeshQuaternion<T>::MultiplicativeIdentity());
    }
    static MushMeshQuaternionPair RotationIdentity(void)
    {
        return MultiplicativeIdentity();
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
MushMeshQuaternionPair<T>::VectorRotate(Mushware::t4Val& ioVec) const
{
    m_first.PreMultiplyVector(ioVec);
    m_second.PostMultiplyVector(ioVec);
}

template<class T>
inline Mushware::t4Val
MushMeshQuaternionPair<T>::RotatedVector(const Mushware::t4Val& inVec) const
{
    Mushware::t4Val retVal(inVec);
    VectorRotate(retVal);
    return retVal;
}

template<class T>
inline void
MushMeshQuaternionPair<T>::InPlaceNormalise()
{
    m_first.InPlaceNormalise();
    m_second.InPlaceNormalise();
}

template<class T>
inline void
MushMeshQuaternionPair<T>::ToRotationIdentitySet()
{
    m_first = MushMeshQuaternion<T>::MultiplicativeIdentity();
    m_second = MushMeshQuaternion<T>::MultiplicativeIdentity();
}

template<class T>
inline MushMeshQuaternionPair<T>
MushMeshQuaternionPair<T>::Conjugate(void) const
{
    return MushMeshQuaternionPair(m_first.Conjugate(), m_second.Conjugate());
}

template<class T>
inline void
MushMeshQuaternionPair<T>::InPlaceConjugate(void)
{
    m_first.InPlaceConjugate();
    m_second.InPlaceConjugate();
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
    
    ioOut.OStream() << '(';
    ioOut << inObj.First();
    ioOut.OStream() << ',';
    ioOut << inObj.Second();
    ioOut.OStream() << ')';
    
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
