//%includeGuardStart {
#ifndef MUSHMESHMATTRESS_H
#define MUSHMESHMATTRESS_H
//%includeGuardStart } DDMflEWZfEa5FFNcLEPHYg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshMattress.h
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
//%Header } z3faz4syHkTAU7ZETVlHVw
/*
 * $Id: MushMeshMattress.h,v 1.6 2006/09/07 16:38:51 southa Exp $
 * $Log: MushMeshMattress.h,v $
 * Revision 1.6  2006/09/07 16:38:51  southa
 * Vertex shader
 *
 * Revision 1.5  2006/06/01 15:39:30  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/07/19 10:07:00  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
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
    
    void ToIdentitySet(void) { m_matrix.ToMultiplicativeIdentitySet(); m_offset.ToAdditiveIdentitySet(); }
    const tThis Inverse(void) const;
    void InPlaceInvert(void);
    
    static tThis Identity(void) { tThis retVal; retVal.ToIdentitySet(); return retVal; }
    
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

template<class T, Mushware::U32 D>
inline const MushMeshMattress<T, D>
MushMeshMattress<T, D>::Inverse(void) const
{
    MushMeshMattress<T, D> retVal;
    retVal.MatrixSet(m_matrix.Transpose());
    retVal.OffsetSet(retVal.Matrix() * -m_offset);
    return retVal;
}

template<class T, Mushware::U32 D>
inline void
MushMeshMattress<T, D>::InPlaceInvert(void)
{
    MushMeshMattress<T, D> retVal;
    m_matrix.InPlaceTranspose();
    m_offset = m_matrix * -m_offset;
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
