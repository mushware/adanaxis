//%includeGuardStart {
#ifndef MUSHMESHMATTRESS_H
#define MUSHMESHMATTRESS_H
//%includeGuardStart } DDMflEWZfEa5FFNcLEPHYg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshMattress.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } X9UP1KNKwyumuL+woGoUdg
/*
 * $Id: MushMeshMattress.h,v 1.1 2005/07/02 00:42:38 southa Exp $
 * $Log: MushMeshMattress.h,v $
 * Revision 1.1  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshPreMatrix.h"
#include "MushMeshVector.h"

//:generate nonvirtual inline ostream xml1
template<class T, Mushware::U32 D>
class MushMeshMattress
{
public:
    typedef MushMeshMattress<T, D> tThis;
    typedef MushMeshPreMatrix<T, D, D> tMatrix;
    typedef MushMeshVector<T, D> tVector;
    typedef MushMeshVector<T, D> tOffset;

    MushMeshMattress() {}
    MushMeshMattress(const tMatrix& inMatrix, const tOffset& inOffset) :
        m_matrix(inMatrix), m_offset(inOffset) {}
    
private:
    tMatrix m_matrix; //:readwrite :wref
    tOffset m_offset; //:readwrite :wref
    
//%classPrototypes {
public:
    const tMatrix& Matrix(void) const { return m_matrix; }
    void MatrixSet(const tMatrix& inValue) { m_matrix=inValue; }
    // Writable reference for m_matrix
    tMatrix& MatrixWRef(void) { return m_matrix; }
    const tOffset& Offset(void) const { return m_offset; }
    void OffsetSet(const tOffset& inValue) { m_offset=inValue; }
    // Writable reference for m_offset
    tOffset& OffsetWRef(void) { return m_offset; }
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } MXVKJ18QwkziezQiwidJog
};

template<class T, Mushware::U32 D>
inline MushMeshVector<T, D>
operator*(const MushMeshMattress<T, D>& inMattress, const MushMeshVector<T, D>& inVector)
{
    return inMattress.Matrix() * inVector + inMattress.Offset();
}

template<class T, Mushware::U32 D>
inline MushMeshMattress<T, D>
operator*(const MushMeshMattress<T, D>& inA, const MushMeshMattress<T, D>& inB)
{
    return MushMeshMattress<T, D>(inA.Matrix() * inB.Matrix(), inA.Matrix() * inB.Offset() + inA.Offset());
}

//%inlineHeader {
template<class T, Mushware::U32 D>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshMattress<T, D>& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
template<class T, Mushware::U32 D>
inline MushcoreXMLIStream&
operator>>(MushcoreXMLIStream& ioIn, MushMeshMattress<T, D>& outObj)
{
    throw MushcoreDataFail("Cannot read XML object type 'MushMeshMattress'");
    return ioIn;
}
template<class T, Mushware::U32 D>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushMeshMattress<T, D>& inObj)
{
    inObj.AutoXMLPrint(ioOut);
    return ioOut;
}
template<class T, Mushware::U32 D>
inline void
MushMeshMattress<T, D>::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "matrix=" << m_matrix << ", ";
    ioOut << "offset=" << m_offset;
    ioOut << "]";
}
template<class T, Mushware::U32 D>
inline bool
MushMeshMattress<T, D>::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "matrix")
    {
        ioIn >> m_matrix;
    }
    else if (inTagStr == "offset")
    {
        ioIn >> m_offset;
    }
    else 
    {
        return false;
    }
    return true;
}
template<class T, Mushware::U32 D>
inline void
MushMeshMattress<T, D>::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("matrix");
    ioOut << m_matrix;
    ioOut.TagSet("offset");
    ioOut << m_offset;
}
//%inlineHeader } SP6VDzn8mXsF/jXuwugg6A

namespace Mushware
{
    typedef MushMeshMattress<tVal, 3> t3x3o3Val;
    typedef MushMeshMattress<tVal, 4> t4x4o4Val;    
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
