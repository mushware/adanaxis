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
 * $Id: TestMushcoreObject.cpp,v 1.1 2003/09/21 09:51:10 southa Exp $
 * $Log: TestMushcoreObject.cpp,v $
 * Revision 1.1  2003/09/21 09:51:10  southa
 * Stream autogenerators
 *
 */

#include "TestMushcoreObject.h"

void
TestMushcoreObject::AutoXMLRead(MushcoreXMLIStream& ioIn)
{
    std::string name;

    while (ioIn.LineAvailable())
    {
        std::string line;
        line = ioIn.LineTake();

        cout << "Found line "+line+"\n";
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
 