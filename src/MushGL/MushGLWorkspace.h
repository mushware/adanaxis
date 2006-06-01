//%includeGuardStart {
#ifndef MUSHGLWORKSPACE_H
#define MUSHGLWORKSPACE_H
//%includeGuardStart } aJOiRZ3DsiLkf5S0mafxfw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLWorkspace.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } UgiYok4TqX0Bpi5y/7fOug
/*
 * $Id: MushGLWorkspace.h,v 1.1 2005/07/04 15:59:00 southa Exp $
 * $Log: MushGLWorkspace.h,v $
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
