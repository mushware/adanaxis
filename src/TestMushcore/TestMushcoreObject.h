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
 * $Id: TestMushcoreObject.h,v 1.5 2003/09/21 23:15:08 southa Exp $
 * $Log: TestMushcoreObject.h,v $
 * Revision 1.5  2003/09/21 23:15:08  southa
 * XML input stream improvements
 *
 * Revision 1.4  2003/09/21 18:49:41  southa
 * XML input stream work
 *
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

//:generate ostream xml1 basic
class TestMushcoreObject : public MushcoreObject, public MushcoreXMLConsumer
{
public:
    TestMushcoreObject() :
        m_u8(1),
        m_u32(2),
        m_string("&<>&lt;ab&amp;cdef</string>&&")
    {}

    explicit TestMushcoreObject(Mushware::U32 inNum) :
    m_u8(0),
    m_u32(0),
    m_string("z")
    {}

    virtual ~TestMushcoreObject() {}
    
private:
    Mushware::U8 m_u8;
    Mushware::U32 m_u32;
    std::string m_string;

//%classPrototypes {
public:
    bool AutoEquals(const TestMushcoreObject& inObj) const;
    void AutoPrint(std::ostream& ioOut) const;
    void AutoXMLDataProcess(MushcoreXMLIStream& ioIn);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut, const std::string& inName) const;
//%classPrototypes } t1PvWvwqFnZBtsD92H+mKA
};
//%inlineNamespaced {
namespace Mushcore
{

inline void
Pickle(MushcoreXMLOStream& ioOut, const TestMushcoreObject& inObj, const std::string& inName="")
{
    inObj.AutoXMLPrint(ioOut, inName);
}

} // end namespace Mushcore
//%inlineNamespaced } +Fjvv2DYljqARHYMR/7PLA
//%inlineHeader {
inline bool
TestMushcoreObject::AutoEquals(const TestMushcoreObject& inObj) const
{
    return (m_u8 == inObj.m_u8) &&
           (m_u32 == inObj.m_u32) &&
           (m_string == inObj.m_string);
}
inline bool
operator==(const TestMushcoreObject& inA, const TestMushcoreObject& inB)
{
    return inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const TestMushcoreObject& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } bH/ocKUu9DucE3oHrPE2Jg

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
