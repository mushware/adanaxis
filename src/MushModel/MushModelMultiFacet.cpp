//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelMultiFacet.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } nzBRybN+TNZbotLpZcw3Eg
/*
 * $Id$
 * $Log$
 */

#include "MushModelMultiFacet.h"

#include "MushModelIO.h"

MUSHCORE_DATA_INSTANCE(MushModelMultiFacet);

//%outOfLineFunctions {
const char *MushModelMultiFacet::AutoNameGet(void) const
{
    return "MushModelMultiFacet";
}
MushModelMultiFacet *MushModelMultiFacet::AutoClone(void) const
{
    return new MushModelMultiFacet(*this);
}
MushModelMultiFacet *MushModelMultiFacet::AutoCreate(void) const
{
    return new MushModelMultiFacet;
}
MushcoreVirtualObject *MushModelMultiFacet::AutoVirtualFactory(void)
{
    return new MushModelMultiFacet;
}
namespace
{
void Install(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushModelMultiFacet", MushModelMultiFacet::AutoVirtualFactory);
}
MushcoreInstaller Installer(Install);
} // end anonymous namespace
void
MushModelMultiFacet::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "facets=" << m_facets;
    ioOut << "]";
}
bool
MushModelMultiFacet::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "facets")
    {
        ioIn >> m_facets;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushModelMultiFacet::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("facets");
    ioOut << m_facets;
}
//%outOfLineFunctions } PhRUMR0c8U9HaTQlLS+FEg
