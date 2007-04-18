//%includeGuardStart {
#ifndef TESTMUSHCOREOBJECT_H
#define TESTMUSHCOREOBJECT_H
//%includeGuardStart } ZbgVXkoAm05vlwSoai7fLw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObject.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } LGQDvQxprEyaluO52oLiZg
/*
 * $Id: TestMushcoreObject.h,v 1.25 2006/06/01 15:40:05 southa Exp $
 * $Log: TestMushcoreObject.h,v $
 * Revision 1.25  2006/06/01 15:40:05  southa
 * DrawArray verification and fixes
 *
 * Revision 1.24  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 * Revision 1.23  2005/07/01 14:59:00  southa
 * Mushcore auto_ptr and binary string fixes
 *
 * Revision 1.22  2005/06/20 14:30:39  southa
 * Adanaxis work
 *
 * Revision 1.21  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.20  2005/02/10 12:34:23  southa
 * Template fixes
 *
 * Revision 1.19  2004/09/27 22:42:11  southa
 * MSVC compilation fixes
 *
 * Revision 1.18  2004/01/08 16:06:11  southa
 * XML fixes
 *
 * Revision 1.17  2004/01/02 21:13:18  southa
 * Source conditioning
 *
 * Revision 1.16  2003/10/14 10:46:05  southa
 * MeshMover creation
 *
 * Revision 1.15  2003/10/03 23:39:34  southa
 * XML polymorphs
 *
 * Revision 1.14  2003/10/02 23:33:39  southa
 * XML polymorphic objects
 *
 * Revision 1.13  2003/09/30 22:11:30  southa
 * XML objects within objects
 *
 * Revision 1.12  2003/09/29 21:48:37  southa
 * XML work
 *
 * Revision 1.11  2003/09/27 17:50:49  southa
 * XML null pointer handling
 *
 * Revision 1.10  2003/09/26 19:18:09  southa
 * XML null pointer handling
 *
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

//:generate virtual standard basic ostream xml1
class TestMushcoreObject : public MushcoreVirtualObject
{
public:
    explicit TestMushcoreObject(Mushware::U32 inNum) :
        m_u8(1),
        m_u32(2),
        m_string("&<>&lt;ab&am,p;cde\"f</string>&,&"),
        m_pNull(NULL),
        m_testObject(NULL),
        m_polymorph(NULL)
    {
            for (Mushware::U32 i=0; i<256; ++i)
            {
                m_fullRangeString += static_cast<Mushware::U8>(i);
            }
            
            m_u8Vector.push_back(4);
            m_u8Vector.push_back(16);
            m_u8Vector.push_back(7);
            m_u32Vector.push_back(3);
            m_u32Vector.push_back(15);
            m_u32Vector.push_back(9);
            m_stringVector.push_back("hams\"ter");
            m_stringVector.push_back("ger,bil");
            m_stringVector.push_back("bad|ger");

            m_vectorVector.push_back(std::vector<Mushware::U32>());
            m_vectorVector.push_back(std::vector<Mushware::U32>());
            m_vectorVector.push_back(std::vector<Mushware::U32>());
            m_vectorVector[0].push_back(3);
            m_vectorVector[0].push_back(5);
            m_vectorVector[0].push_back(7);
            m_vectorVector[2].push_back(8);
            m_vectorVector[2].push_back(35);
            m_vectorVector[2].push_back(1);

            m_mapVector[3].push_back("three");
            m_mapVector[6] = std::vector<std::string>();
            m_mapVector[15].push_back("\"fifteen-one");
            m_mapVector[15].push_back("fifteen-two\"");

            m_vectorMap.push_back(std::map<Mushware::U32, std::string>());
            m_vectorMap.push_back(std::map<Mushware::U32, std::string>());
            m_vectorMap.push_back(std::map<Mushware::U32, std::string>());

            m_vectorMap[0][6] = "six";
            m_vectorMap[0][7] = "seven";
            m_vectorMap[2][14] = "fourt,)(\"een";

            m_pU32 = new Mushware::U32(2);
            m_aU32.reset(new Mushware::U32(17));
            m_pVectorU32 = new std::vector<Mushware::U32>;
            m_pVectorU32->push_back(4);
            m_pVectorU32->push_back(18);
            m_pVectorU32->push_back(1);

            m_vectorpU32.push_back(new Mushware::U32(2));
            m_vectorpU32.push_back(NULL);
            m_vectorpU32.push_back(new Mushware::U32(19));

            m_testObject = new TestMushcoreObject;
            m_polymorph = new TestMushcoreObject;
            m_vectorTestObject.push_back(new TestMushcoreObject);
            m_vectorPolymorph.push_back(new TestMushcoreObject);
    }

    TestMushcoreObject() :
        m_u8(0),
        m_u32(0),
        m_pU32(NULL),
        m_pVectorU32(NULL),
        m_pNull(NULL),
        m_testObject(NULL),
        m_polymorph(NULL)
    {
    }

    virtual ~TestMushcoreObject() {}
    
    void U8Set(Mushware::U8 inValue) { m_u8 = inValue; }
    
private:
    TestMushcoreObject(const TestMushcoreObject&) {     throw(MushcoreLogicFail("Forbidden assignment of TestMushcoreObject")); } // Prohibit copy construction
    TestMushcoreObject& operator=(const TestMushcoreObject&) {     throw(MushcoreLogicFail("Forbidden assignment of TestMushcoreObject")); return *this; } // Prohibit copy assignment
    
    std::vector<MushcoreVirtualObject *> m_vectorPolymorph; // nobasic;
    std::vector<TestMushcoreObject *> m_vectorTestObject; // nobasic;
    
    Mushware::U8 m_u8;
    Mushware::U32 m_u32; //:readwrite
    std::string m_string;
    std::string m_fullRangeString;
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
    std::auto_ptr<Mushware::U32> m_aU32;
    std::vector<Mushware::U32> *m_pVectorU32;
    std::vector<Mushware::U32 *> m_vectorpU32; // nobasic

    Mushware::U32 *m_pNull;
    std::auto_ptr<Mushware::U32> m_aNull;

    TestMushcoreObject *m_testObject;
    MushcoreVirtualObject *m_polymorph; // nobasic
    
//%classPrototypes {
public:
    const Mushware::U32& U32(void) const { return m_u32; }
    void U32Set(const Mushware::U32& inValue) { m_u32=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const TestMushcoreObject& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } cyOU831J5xwK6o4WilHNDw
};

template<class T>
inline bool
operator==(const std::auto_ptr<T>& inA, const std::auto_ptr<T>& inB)
{
    return (inA.get() == inB.get() || (inA.get() != NULL && inB.get() != NULL && *inA == *inB));
}

//%inlineHeader {

inline bool
operator==(const TestMushcoreObject& inA, const TestMushcoreObject& inB)
{
    return inA.AutoEquals(inB);
}

inline bool
operator!=(const TestMushcoreObject& inA, const TestMushcoreObject& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const TestMushcoreObject& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } VxPXEDFGuBjKrdnxCAovFg


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
