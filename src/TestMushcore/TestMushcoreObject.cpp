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
 * $Id: TestMushcoreObject.cpp,v 1.3 2003/09/21 15:57:12 southa Exp $
 * $Log: TestMushcoreObject.cpp,v $
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

void
TestMushcoreObject::XMLDataProcess(MushcoreXMLIStream& ioIn)
{
    cout << "Tag " << ioIn.TagNameGet() << endl;
    if (ioIn.TagNameGet() == "TestMushcoreObject")
    {
        // MushcoreXMLIStream xmlIStream(&ioIn.DataStreamGet());
        // Mushcore::Unpickle(xmlIStream, *this);

        ioIn.ObjectRead(*this);
    }
    else if (ioIn.TagNameGet() == "u8")
    {
        ioIn >> m_u8;
    }
    else if (ioIn.TagNameGet() == "u32")
    {
        ioIn >> m_u32;
    }
}

//%outOfLineFunctions {
void
TestMushcoreObject::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "u8=" << static_cast<Mushware::U32>(m_u8) << ", ";
    ioOut << "u32=" << m_u32;
    ioOut << "]";
}

void
TestMushcoreObject::AutoXMLPrint(MushcoreXMLOStream& ioOut, const std::string& inName) const
{
    ioOut << "<TestMushcoreObject";
    if (inName != "")
    {
        ioOut << " name=\"" << inName << "\"";
    }
    ioOut << ">\n";
    ioOut << "<u8>" << static_cast<Mushware::U32>(m_u8) << "</u8>\n";
    ioOut << "<u32>" << m_u32 << "</u32>\n";
    ioOut << "</TestMushcoreObject>\n";
}
//%outOfLineFunctions } NfPFVErs7nlMep7H2sGyqw
 