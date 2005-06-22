//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAddress.cpp
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
//%Header } TnlKjaEghVGIRsAL04WswQ
/*
 * $Id$
 * $Log$
 */

#include "MushGameAddress.h"

MUSHCORE_DATA_INSTANCE(MushGameAddress);

//%outOfLineFunctions {

const char *MushGameAddress::AutoName(void) const
{
    return "MushGameAddress";
}

MushcoreVirtualObject *MushGameAddress::AutoClone(void) const
{
    return new MushGameAddress(*this);
}

MushcoreVirtualObject *MushGameAddress::AutoCreate(void) const
{
    return new MushGameAddress;
}

MushcoreVirtualObject *MushGameAddress::AutoVirtualFactory(void)
{
    return new MushGameAddress;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameAddress", MushGameAddress::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameAddress::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "name=" << m_name << ", ";
    ioOut << "linkRef=" << m_linkRef;
    ioOut << "]";
}
bool
MushGameAddress::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "name")
    {
        ioIn >> m_name;
    }
    else if (inTagStr == "linkRef")
    {
        ioIn >> m_linkRef;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGameAddress::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("name");
    ioOut << m_name;
    ioOut.TagSet("linkRef");
    ioOut << m_linkRef;
}
//%outOfLineFunctions } i+47pp6zSzmz3kGZeiceLw
