//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObject.cpp
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
//%Header } /C4CFFmSnufbqgXbq7HAiw
/*
 * $Id: TestMushcoreObject.cpp,v 1.24 2005/07/01 14:59:00 southa Exp $
 * $Log: TestMushcoreObject.cpp,v $
 * Revision 1.24  2005/07/01 14:59:00  southa
 * Mushcore auto_ptr and binary string fixes
 *
 * Revision 1.23  2005/06/20 14:30:39  southa
 * Adanaxis work
 *
 * Revision 1.22  2005/06/16 17:25:41  southa
 * Client/server work
 *
 * Revision 1.21  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.20  2005/02/10 12:34:22  southa
 * Template fixes
 *
 * Revision 1.19  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 * Revision 1.18  2004/01/08 16:06:11  southa
 * XML fixes
 *
 * Revision 1.17  2004/01/02 21:13:18  southa
 * Source conditioning
 *
 * Revision 1.16  2003/10/03 23:39:34  southa
 * XML polymorphs
 *
 * Revision 1.15  2003/10/02 23:33:39  southa
 * XML polymorphic objects
 *
 * Revision 1.14  2003/10/01 23:18:28  southa
 * XML object handling
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
 * Revision 1.2  2003/09/21 11:46:11  southa
 * XML input stream
 *
 * Revision 1.1  2003/09/21 09:51:10  southa
 * Stream autogenerators
 *
 */

#include "TestMushcoreObject.h"

using namespace std;
using namespace Mushware;

MUSHCORE_DATA_INSTANCE(TestMushcoreObject);

//%outOfLineFunctions {

const char *TestMushcoreObject::AutoName(void) const
{
    return "TestMushcoreObject";
}

MushcoreVirtualObject *TestMushcoreObject::AutoClone(void) const
{
    return new TestMushcoreObject(*this);
}

MushcoreVirtualObject *TestMushcoreObject::AutoCreate(void) const
{
    return new TestMushcoreObject;
}

MushcoreVirtualObject *TestMushcoreObject::AutoVirtualFactory(void)
{
    return new TestMushcoreObject;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("TestMushcoreObject", TestMushcoreObject::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
TestMushcoreObject::AutoEquals(const TestMushcoreObject& inObj) const
{
    return 1
        && (m_u8 == inObj.m_u8)
        && (m_u32 == inObj.m_u32)
        && (m_string == inObj.m_string)
        && (m_fullRangeString == inObj.m_fullRangeString)
        && (m_u8Vector == inObj.m_u8Vector)
        && (m_u32Vector == inObj.m_u32Vector)
        && (m_stringVector == inObj.m_stringVector)
        && (m_u8EmptyVector == inObj.m_u8EmptyVector)
        && (m_uEmpty32Vector == inObj.m_uEmpty32Vector)
        && (m_stringEmptyVector == inObj.m_stringEmptyVector)
        && (m_vectorVector == inObj.m_vectorVector)
        && (m_mapVector == inObj.m_mapVector)
        && (m_vectorMap == inObj.m_vectorMap)
        && (m_pU32 == inObj.m_pU32 || (m_pU32 != NULL && inObj.m_pU32 != NULL && *m_pU32 == *inObj.m_pU32))
        && (m_aU32 == inObj.m_aU32)
        && (m_pVectorU32 == inObj.m_pVectorU32 || (m_pVectorU32 != NULL && inObj.m_pVectorU32 != NULL && *m_pVectorU32 == *inObj.m_pVectorU32))
        && (m_pNull == inObj.m_pNull || (m_pNull != NULL && inObj.m_pNull != NULL && *m_pNull == *inObj.m_pNull))
        && (m_aNull == inObj.m_aNull)
        && (m_testObject == inObj.m_testObject || (m_testObject != NULL && inObj.m_testObject != NULL && *m_testObject == *inObj.m_testObject))
    ;
}
void
TestMushcoreObject::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "vectorPolymorph=" << m_vectorPolymorph << ", ";
    ioOut << "vectorTestObject=" << m_vectorTestObject << ", ";
    ioOut << "u8=" << static_cast<Mushware::U32>(m_u8) << ", ";
    ioOut << "u32=" << m_u32 << ", ";
    ioOut << "string=" << m_string << ", ";
    ioOut << "fullRangeString=" << m_fullRangeString << ", ";
    ioOut << "u8Vector=" << m_u8Vector << ", ";
    ioOut << "u32Vector=" << m_u32Vector << ", ";
    ioOut << "stringVector=" << m_stringVector << ", ";
    ioOut << "u8EmptyVector=" << m_u8EmptyVector << ", ";
    ioOut << "uEmpty32Vector=" << m_uEmpty32Vector << ", ";
    ioOut << "stringEmptyVector=" << m_stringEmptyVector << ", ";
    ioOut << "vectorVector=" << m_vectorVector << ", ";
    ioOut << "mapVector=" << m_mapVector << ", ";
    ioOut << "vectorMap=" << m_vectorMap << ", ";
    if (m_pU32 == NULL)
    {
        ioOut << "pU32=NULL"  << ", ";
    }
    else
    {
        ioOut << "pU32=" << *m_pU32 << ", ";
    }
    ioOut << "aU32=" << m_aU32 << ", ";
    if (m_pVectorU32 == NULL)
    {
        ioOut << "pVectorU32=NULL"  << ", ";
    }
    else
    {
        ioOut << "pVectorU32=" << *m_pVectorU32 << ", ";
    }
    ioOut << "vectorpU32=" << m_vectorpU32 << ", ";
    if (m_pNull == NULL)
    {
        ioOut << "pNull=NULL"  << ", ";
    }
    else
    {
        ioOut << "pNull=" << *m_pNull << ", ";
    }
    ioOut << "aNull=" << m_aNull << ", ";
    if (m_testObject == NULL)
    {
        ioOut << "testObject=NULL"  << ", ";
    }
    else
    {
        ioOut << "testObject=" << *m_testObject << ", ";
    }
    if (m_polymorph == NULL)
    {
        ioOut << "polymorph=NULL" ;
    }
    else
    {
        ioOut << "polymorph=" << *m_polymorph;
    }
    ioOut << "]";
}
bool
TestMushcoreObject::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "vectorPolymorph")
    {
        ioIn >> m_vectorPolymorph;
    }
    else if (inTagStr == "vectorTestObject")
    {
        ioIn >> m_vectorTestObject;
    }
    else if (inTagStr == "u8")
    {
        ioIn >> m_u8;
    }
    else if (inTagStr == "u32")
    {
        ioIn >> m_u32;
    }
    else if (inTagStr == "string")
    {
        ioIn >> m_string;
    }
    else if (inTagStr == "fullRangeString")
    {
        ioIn >> m_fullRangeString;
    }
    else if (inTagStr == "u8Vector")
    {
        ioIn >> m_u8Vector;
    }
    else if (inTagStr == "u32Vector")
    {
        ioIn >> m_u32Vector;
    }
    else if (inTagStr == "stringVector")
    {
        ioIn >> m_stringVector;
    }
    else if (inTagStr == "u8EmptyVector")
    {
        ioIn >> m_u8EmptyVector;
    }
    else if (inTagStr == "uEmpty32Vector")
    {
        ioIn >> m_uEmpty32Vector;
    }
    else if (inTagStr == "stringEmptyVector")
    {
        ioIn >> m_stringEmptyVector;
    }
    else if (inTagStr == "vectorVector")
    {
        ioIn >> m_vectorVector;
    }
    else if (inTagStr == "mapVector")
    {
        ioIn >> m_mapVector;
    }
    else if (inTagStr == "vectorMap")
    {
        ioIn >> m_vectorMap;
    }
    else if (inTagStr == "pU32")
    {
        ioIn >> m_pU32;
    }
    else if (inTagStr == "aU32")
    {
        ioIn >> m_aU32;
    }
    else if (inTagStr == "pVectorU32")
    {
        ioIn >> m_pVectorU32;
    }
    else if (inTagStr == "vectorpU32")
    {
        ioIn >> m_vectorpU32;
    }
    else if (inTagStr == "pNull")
    {
        ioIn >> m_pNull;
    }
    else if (inTagStr == "aNull")
    {
        ioIn >> m_aNull;
    }
    else if (inTagStr == "testObject")
    {
        ioIn >> m_testObject;
    }
    else if (inTagStr == "polymorph")
    {
        ioIn >> m_polymorph;
    }
    else 
    {
        return false;
    }
    return true;
}
void
TestMushcoreObject::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("vectorPolymorph");
    ioOut << m_vectorPolymorph;
    ioOut.TagSet("vectorTestObject");
    ioOut << m_vectorTestObject;
    ioOut.TagSet("u8");
    ioOut << m_u8;
    ioOut.TagSet("u32");
    ioOut << m_u32;
    ioOut.TagSet("string");
    ioOut << m_string;
    ioOut.TagSet("fullRangeString");
    ioOut << m_fullRangeString;
    ioOut.TagSet("u8Vector");
    ioOut << m_u8Vector;
    ioOut.TagSet("u32Vector");
    ioOut << m_u32Vector;
    ioOut.TagSet("stringVector");
    ioOut << m_stringVector;
    ioOut.TagSet("u8EmptyVector");
    ioOut << m_u8EmptyVector;
    ioOut.TagSet("uEmpty32Vector");
    ioOut << m_uEmpty32Vector;
    ioOut.TagSet("stringEmptyVector");
    ioOut << m_stringEmptyVector;
    ioOut.TagSet("vectorVector");
    ioOut << m_vectorVector;
    ioOut.TagSet("mapVector");
    ioOut << m_mapVector;
    ioOut.TagSet("vectorMap");
    ioOut << m_vectorMap;
    ioOut.TagSet("pU32");
    ioOut << m_pU32;
    ioOut.TagSet("aU32");
    ioOut << m_aU32;
    ioOut.TagSet("pVectorU32");
    ioOut << m_pVectorU32;
    ioOut.TagSet("vectorpU32");
    ioOut << m_vectorpU32;
    ioOut.TagSet("pNull");
    ioOut << m_pNull;
    ioOut.TagSet("aNull");
    ioOut << m_aNull;
    ioOut.TagSet("testObject");
    ioOut << m_testObject;
    ioOut.TagSet("polymorph");
    ioOut << m_polymorph;
}
//%outOfLineFunctions } PM0AewMPwDd7ySTS724PyA
