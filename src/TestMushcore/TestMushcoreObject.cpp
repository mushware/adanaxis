//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreObject.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /pOiNRIbyuLcFay5YqF2HQ
/*
 * $Id: TestMushcoreObject.cpp,v 1.7 2003/09/23 22:57:57 southa Exp $
 * $Log: TestMushcoreObject.cpp,v $
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


//%outOfLineFunctions {
void
TestMushcoreObject::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "u8=" << static_cast<Mushware::U32>(m_u8) << ", ";
    ioOut << "u32=" << m_u32 << ", ";
    ioOut << "string=" << m_string << ", ";
    ioOut << "u8Vector=" << m_u8Vector << ", ";
    ioOut << "u32Vector=" << m_u32Vector << ", ";
    ioOut << "stringVector=" << m_stringVector << ", ";
    ioOut << "u8EmptyVector=" << m_u8EmptyVector << ", ";
    ioOut << "uEmpty32Vector=" << m_uEmpty32Vector << ", ";
    ioOut << "stringEmptyVector=" << m_stringEmptyVector << ", ";
    ioOut << "vectorVector=" << m_vectorVector << ", ";
    ioOut << "mapVector=" << m_mapVector << ", ";
    ioOut << "vectorMap=" << m_vectorMap;
    ioOut << "]";
}
void
TestMushcoreObject::AutoXMLDataProcess(MushcoreXMLIStream& ioIn)
{
    if (ioIn.TagNameGet() == "TestMushcoreObject")
    {
        ioIn >> *this;
    }
    else if (ioIn.TagNameGet() == "u8")
    {
        ioIn >> m_u8;
    }
    else if (ioIn.TagNameGet() == "u32")
    {
        ioIn >> m_u32;
    }
    else if (ioIn.TagNameGet() == "string")
    {
        ioIn >> m_string;
    }
    else if (ioIn.TagNameGet() == "u8Vector")
    {
        ioIn >> m_u8Vector;
    }
    else if (ioIn.TagNameGet() == "u32Vector")
    {
        ioIn >> m_u32Vector;
    }
    else if (ioIn.TagNameGet() == "stringVector")
    {
        ioIn >> m_stringVector;
    }
    else if (ioIn.TagNameGet() == "u8EmptyVector")
    {
        ioIn >> m_u8EmptyVector;
    }
    else if (ioIn.TagNameGet() == "uEmpty32Vector")
    {
        ioIn >> m_uEmpty32Vector;
    }
    else if (ioIn.TagNameGet() == "stringEmptyVector")
    {
        ioIn >> m_stringEmptyVector;
    }
    else if (ioIn.TagNameGet() == "vectorVector")
    {
        ioIn >> m_vectorVector;
    }
    else if (ioIn.TagNameGet() == "mapVector")
    {
        ioIn >> m_mapVector;
    }
    else if (ioIn.TagNameGet() == "vectorMap")
    {
        ioIn >> m_vectorMap;
    }
}
void
TestMushcoreObject::AutoXMLPrint(MushcoreXMLOStream& ioOut, const std::string& inName) const
{
    ioOut << "<TestMushcoreObject";
    if (inName != "")
    {
        ioOut << " name=" << inName;
    }
    ioOut << ">\n";
    ioOut << "<u8>" << static_cast<Mushware::U32>(m_u8) << "</u8>\n";
    ioOut << "<u32>" << m_u32 << "</u32>\n";
    ioOut << "<string>" << m_string << "</string>\n";
    ioOut << "<u8Vector>" << m_u8Vector << "</u8Vector>\n";
    ioOut << "<u32Vector>" << m_u32Vector << "</u32Vector>\n";
    ioOut << "<stringVector>" << m_stringVector << "</stringVector>\n";
    ioOut << "<u8EmptyVector>" << m_u8EmptyVector << "</u8EmptyVector>\n";
    ioOut << "<uEmpty32Vector>" << m_uEmpty32Vector << "</uEmpty32Vector>\n";
    ioOut << "<stringEmptyVector>" << m_stringEmptyVector << "</stringEmptyVector>\n";
    ioOut << "<vectorVector>" << m_vectorVector << "</vectorVector>\n";
    ioOut << "<mapVector>" << m_mapVector << "</mapVector>\n";
    ioOut << "<vectorMap>" << m_vectorMap << "</vectorMap>\n";
    ioOut << "</TestMushcoreObject>\n";
}
//%outOfLineFunctions } Sig60JxWdIF4FZnqb4hzqg
