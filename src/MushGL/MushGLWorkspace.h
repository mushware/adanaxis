//%includeGuardStart {
#ifndef MUSHGLWORKSPACE_H
#define MUSHGLWORKSPACE_H
//%includeGuardStart } aJOiRZ3DsiLkf5S0mafxfw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLWorkspace.h
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
//%Header } atdflKSH927wyC2NTJ7yag
/*
 * $Id: MushGLWorkspace.h,v 1.2 2006/06/01 15:39:19 southa Exp $
 * $Log: MushGLWorkspace.h,v $
 * Revision 1.2  2006/06/01 15:39:19  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 */

#include "MushGLStandard.h"

//:generate inline nonvirtual ostream xml1
template<class T>
class MushGLWorkspace
{
public:
    
private:
    std::vector<T> m_data; //:wref
    Mushware::U32 m_tag; //:readwrite
//%classPrototypes {
public:
    // Writable reference for m_data
    std::vector<T>& DataWRef(void) { return m_data; }
    const Mushware::U32& Tag(void) const { return m_tag; }
    void TagSet(const Mushware::U32& inValue) { m_tag=inValue; }
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } HcwrYmceDWANm6igSIBogg
};
//%inlineHeader {
template<class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLWorkspace<T>& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
template<class T>
inline MushcoreXMLIStream&
operator>>(MushcoreXMLIStream& ioIn, MushGLWorkspace<T>& outObj)
{
    throw MushcoreDataFail("Cannot read XML object type 'MushGLWorkspace'");
    return ioIn;
}
template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushGLWorkspace<T>& inObj)
{
    inObj.AutoXMLPrint(ioOut);
    return ioOut;
}
template<class T>
inline void
MushGLWorkspace<T>::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "data=" << m_data << ", ";
    ioOut << "tag=" << m_tag;
    ioOut << "]";
}
template<class T>
inline bool
MushGLWorkspace<T>::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "data")
    {
        ioIn >> m_data;
    }
    else if (inTagStr == "tag")
    {
        ioIn >> m_tag;
    }
    else 
    {
        return false;
    }
    return true;
}
template<class T>
inline void
MushGLWorkspace<T>::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("data");
    ioOut << m_data;
    ioOut.TagSet("tag");
    ioOut << m_tag;
}
//%inlineHeader } xePOdy7wiHvoITXTNg1fnw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
