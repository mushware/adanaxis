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
 * $Id: TestMushcoreObject.h,v 1.3 2003/09/21 15:57:12 southa Exp $
 * $Log: TestMushcoreObject.h,v $
 * Revision 1.3  2003/09/21 15:57:12  southa
 * XML autogenerator work
 *
 * Revision 1.2  2003/09/21 11:46:12  southa
 * XML input stream
 *
 * Revision 1.1  2003/09/21 09:51:10  southa
 * Stream autogenerators
 *
 */

#include "TestMushcoreStandard.h"

//:generate ostream xml1
class TestMushcoreObject : public MushcoreObject, public MushcoreXMLConsumer
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

    Mushware::U32 AutoXMLRead(const std::string& inStr);
    virtual void XMLDataProcess(MushcoreXMLIStream& ioIn);
//%classPrototypes } Z45ZX1/VtF+3hZqy6oJcFw
};

//%inlineNamespaced {
namespace Mushcore
{

inline void
Unpickle(MushcoreXMLIStream& ioIn, TestMushcoreObject& inObj)
{
    ioIn.ObjectRead(inObj);
}
inline void
Pickle(MushcoreXMLOStream& ioOut, const TestMushcoreObject& inObj, const std::string& inName="")
{
    inObj.AutoXMLPrint(ioOut, inName);
}

} // end namespace Mushcore

// Keep the standard unpickles here

inline MushcoreXMLIStream&
operator>>(MushcoreXMLIStream& ioIn, TestMushcoreObject& outObj)
{
    Mushcore::Unpickle(ioIn, outObj);
    return ioIn;
}

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
