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
 * $Id$
 * $Log$
 */

#include "TestMushcoreObject.h"



//%outOfLineFunctions {
void
TestMushcoreObject::AutoXMLPrint(MushcoreXMLOStream& ioOut, const std::string& inName) const
{
    ioOut << "<TestMushcoreObject";
    if (inName != "")
    {
        ioOut << " name=\"" << inName << "\"";
    }
    ioOut << ">\n";
    ioOut << "<m_u8>" << static_cast<Mushware::U32>(m_u8) << "</m_u8>\n";
    ioOut << "<m_u32>" << m_u32 << "</m_u32>\n";
    ioOut << "</TestMushcoreObject>\n";
}
//%outOfLineFunctions } 2SqXS4OPDxLKjDKyEnzRqg
