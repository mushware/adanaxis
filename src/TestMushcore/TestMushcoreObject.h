//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECT_H
#define TESTMUSHCOREOBJECT_H
//%includeGuardStart } ZbgVXkoAm05vlwSoai7fLw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObject.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 6Pvz7HiimjBXCxXQxlnIcA
/*
 * $Id: TestMushcoreObject.h,v 1.1 2003/09/21 09:51:10 southa Exp $
 * $Log: TestMushcoreObject.h,v $
 * Revision 1.1  2003/09/21 09:51:10  southa
 * Stream autogenerators
 *
 */

#include "Mushcore.h"

//:generate ostream xml1
class TestMushcoreObject : public MushcoreObject
{
public:
    TestMushcoreObject() :
        m_u8(1),
        m_u32(2)
    {}

    explicit TestMushcoreObject(Mushware::U32 inNum) :
    m_u8(0),
    m_u32(0)
    {}
    
    
private:
    Mushware::U8 m_u8;
    Mushware::U32 m_u32;
//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
    void AutoXMLRead(MushcoreXMLIStream& ioIn);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut, const std::string& inName) const;
//%classPrototypes } Z45ZX1/VtF+3hZqy6oJcFw
};

//%inlineNamespaced {
namespace Mushcore
{

inline void
Unpickle(MushcoreXMLIStream& ioIn, TestMushcoreObject& inObj)
{
    inObj.AutoXMLRead(ioIn);
}
inline void
Pickle(MushcoreXMLOStream& ioOut, const TestMushcoreObject& inObj, const std::string& inName="")
{
    inObj.AutoXMLPrint(ioOut, inName);
}

} // end namespace Mushcore
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const TestMushcoreObject& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } wtIj6sOLlmWIa4+bx30Igg
//%inlineNamespaced } 4C5axkZwqb1pfTNuy9sneg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
