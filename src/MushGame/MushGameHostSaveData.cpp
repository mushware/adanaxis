//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameHostSaveData.cpp
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
//%Header } PtE5rBAXGQWHrOsXuTDTuQ
/*
 * $Id: MushGameHostSaveData.cpp,v 1.1 2005/06/21 15:57:47 southa Exp $
 * $Log: MushGameHostSaveData.cpp,v $
 * Revision 1.1  2005/06/21 15:57:47  southa
 * MushGame work
 *
 */

#include "MushGameHostSaveData.h"

MUSHCORE_DATA_INSTANCE(MushGameHostSaveData);

MushGameHostSaveData::MushGameHostSaveData()
{
}

//%outOfLineFunctions {

const char *MushGameHostSaveData::AutoName(void) const
{
    return "MushGameHostSaveData";
}

MushcoreVirtualObject *MushGameHostSaveData::AutoClone(void) const
{
    return new MushGameHostSaveData(*this);
}

MushcoreVirtualObject *MushGameHostSaveData::AutoCreate(void) const
{
    return new MushGameHostSaveData;
}

MushcoreVirtualObject *MushGameHostSaveData::AutoVirtualFactory(void)
{
    return new MushGameHostSaveData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameHostSaveData", MushGameHostSaveData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameHostSaveData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "clientAddrRefs=" << m_clientAddrRefs;
    ioOut << "]";
}
bool
MushGameHostSaveData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "clientAddrRefs")
    {
        ioIn >> m_clientAddrRefs;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGameHostSaveData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("clientAddrRefs");
    ioOut << m_clientAddrRefs;
}
//%outOfLineFunctions } F8O6L78waRGPkZw6IpPspA
