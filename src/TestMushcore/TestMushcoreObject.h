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
 * $Id: TestMushcoreObject.h,v 1.9 2003/09/25 20:02:25 southa Exp $
 * $Log: TestMushcoreObject.h,v $
 * Revision 1.9  2003/09/25 20:02:25  southa
 * XML pointer work
 *
 * Revision 1.8  2003/09/24 19:03:23  southa
 * XML map IO
 *
 * Revision 1.7  2003/09/23 22:57:57  southa
 * XML vector handling
 *
 * Revision 1.6  2003/09/22 19:40:36  southa
 * XML I/O work
 *
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
        m_string("&<>&lt;ab&am,p;cde\"f</string>&,&"),
        m_pNull(NULL)
    {
            m_u8Vector.push_back(4);
            m_u8Vector.push_back(16);
            m_u8Vector.push_back(7);
            m_u32Vector.push_back(3);
            m_u32Vector.push_back(15);
            m_u32Vector.push_back(9);
            m_stringVector.push_back("hams\"ter");
            m_stringVector.push_back("ger,bil");
            m_stringVector.push_back("bad|ger");

            m_vectorVector.push_back();
            m_vectorVector.push_back();
            m_vectorVector.push_back();
            m_vectorVector[0].push_back(3);
            m_vectorVector[0].push_back(5);
            m_vectorVector[0].push_back(7);
            m_vectorVector[2].push_back(8);
            m_vectorVector[2].push_back(35);
            m_vectorVector[2].push_back(1);

            m_mapVector[3].push_back("three");
            m_mapVector[6] = vector<std::string>();
            m_mapVector[15].push_back("\"fifteen-one\"");
            m_mapVector[15].push_back("fifteen-two");

            m_vectorMap.push_back();
            m_vectorMap.push_back();
            m_vectorMap.push_back();

            m_vectorMap[0][6] = "six";
            m_vectorMap[0][7] = "seven";
            m_vectorMap[2][14] = "fourt,)(\"een";

#if 0
            m_pVector.push_back(TestMushcoreObject(0));
#endif

            m_pU32 = new Mushware::U32(2);
            m_pVectorU32 = new vector<Mushware::U32>;
            m_pVectorU32->push_back(4);
            m_pVectorU32->push_back(18);
            m_pVectorU32->push_back(1);

            m_vectorpU32.push_back(new Mushware::U32(2));
            m_vectorpU32.push_back(new Mushware::U32(8));
            m_vectorpU32.push_back(new Mushware::U32(19));

            // m_testObject = new TestMushcoreObject(0);
    }

    explicit TestMushcoreObject(Mushware::U32 inNum) :
    m_u8(0),
    m_u32(0),
    m_string("z"),
    m_pU32(NULL),
    m_pVectorU32(NULL),
    m_pNull(NULL)
    {
    }

    virtual ~TestMushcoreObject() {}
    
private:
    Mushware::U8 m_u8;
    Mushware::U32 m_u32;
    std::string m_string;
    std::vector<Mushware::U8> m_u8Vector;
    std::vector<Mushware::U32> m_u32Vector;
    std::vector<std::string> m_stringVector;
    std::vector<Mushware::U8> m_u8EmptyVector;
    std::vector<Mushware::U32> m_uEmpty32Vector;
    std::vector<std::string> m_stringEmptyVector;

    std::vector< std::vector<Mushware::U32> > m_vectorVector;
    std::map< Mushware::U32, std::vector<std::string> > m_mapVector;
    std::vector< std::map<Mushware::U32, std::string> > m_vectorMap;

    Mushware::U32 *m_pU32;
    std::vector<Mushware::U32> *m_pVectorU32;
    std::vector<Mushware::U32 *> m_vectorpU32;

    Mushware::U32 *m_pNull;

    
    // TestMushcoreObject *m_testObject;
    
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
//%inlineHeader } ikvElCmBt/z6dJAPO9xNgw


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
