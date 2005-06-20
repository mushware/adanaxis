//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLink.cpp
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
//%Header } 3OteCOfn1xaSDLsPZcAEYQ
/*
 * $Id: MushGameLink.cpp,v 1.1 2005/06/16 10:48:59 southa Exp $
 * $Log: MushGameLink.cpp,v $
 * Revision 1.1  2005/06/16 10:48:59  southa
 * Client/server work
 *
 */

#include "MushGameLink.h"

//%outOfLineFunctions {

const char *MushGameLink::AutoName(void) const
{
    return "MushGameLink";
}

MushcoreVirtualObject *MushGameLink::AutoClone(void) const
{
    return new MushGameLink(*this);
}

MushcoreVirtualObject *MushGameLink::AutoCreate(void) const
{
    return new MushGameLink;
}

MushcoreVirtualObject *MushGameLink::AutoVirtualFactory(void)
{
    return new MushGameLink;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameLink", MushGameLink::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameLink::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameLink::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGameLink::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } FuV8JBtRlsDDaQjLuxLqog
