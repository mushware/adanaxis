//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSignalNumeric.cpp
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
//%Header } ayO3HxKF2plbUIsSd8qxzA
/*
 * $Id: MushPieSignalNumeric.cpp,v 1.2 2005/02/10 12:34:16 southa Exp $
 * $Log: MushPieSignalNumeric.cpp,v $
 * Revision 1.2  2005/02/10 12:34:16  southa
 * Template fixes
 *
 * Revision 1.1  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 */

#include "MushPieSignalNumeric.h"

//%outOfLineFunctions {

const char *MushPieSignalNumeric::AutoNameGet(void) const
{
    return "MushPieSignalNumeric";
}

MushcoreVirtualObject *MushPieSignalNumeric::AutoClone(void) const
{
    return new MushPieSignalNumeric(*this);
}

MushcoreVirtualObject *MushPieSignalNumeric::AutoCreate(void) const
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
//%outOfLineFunctions } LU817k75K5S+Sfs1bLUkiw
