//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSignalNumeric.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } dHih2TKo/swBPrS9/535mQ
/*
 * $Id$
 * $Log$
 */

#include "MushPieSignalNumeric.h"

//%outOfLineFunctions {
const char *MushPieSignalNumeric::AutoNameGet(void) const
{
    return "MushPieSignalNumeric";
}
MushPieSignalNumeric *MushPieSignalNumeric::AutoClone(void) const
{
    return new MushPieSignalNumeric(*this);
}
MushPieSignalNumeric *MushPieSignalNumeric::AutoCreate(void) const
{
    return new MushPieSignalNumeric;
}
MushcoreVirtualObject *MushPieSignalNumeric::AutoVirtualFactory(void)
{
    return new MushPieSignalNumeric;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPieSignalNumeric", MushPieSignalNumeric::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushPieSignalNumeric::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "eventNumber=" << m_eventNumber;
    ioOut << "]";
}
bool
MushPieSignalNumeric::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "eventNumber")
    {
        ioIn >> m_eventNumber;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushPieSignalNumeric::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("eventNumber");
    ioOut << m_eventNumber;
}
//%outOfLineFunctions } wluUyz7SKiIdJnkhh60/uA
