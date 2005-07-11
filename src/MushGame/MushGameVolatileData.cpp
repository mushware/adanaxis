//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameVolatileData.cpp
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
//%Header } ZLCiVmbUjo5qfJ+17ayqmA
/*
 * $Id: MushGameVolatileData.cpp,v 1.3 2005/07/02 00:42:38 southa Exp $
 * $Log: MushGameVolatileData.cpp,v $
 * Revision 1.3  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:52  southa
 * MushGame work
 *
 */

#include "MushGameVolatileData.h"

MUSHCORE_DATA_INSTANCE(MushGameVolatileData);

MushGameVolatileData::MushGameVolatileData() :
    m_playerUplinkPeriodMsec(100),
    m_lastPlayerUplinkMsec(0)
{
}

//%outOfLineFunctions {

const char *MushGameVolatileData::AutoName(void) const
{
    return "MushGameVolatileData";
}

MushcoreVirtualObject *MushGameVolatileData::AutoClone(void) const
{
    return new MushGameVolatileData(*this);
}

MushcoreVirtualObject *MushGameVolatileData::AutoCreate(void) const
{
    return new MushGameVolatileData;
}

MushcoreVirtualObject *MushGameVolatileData::AutoVirtualFactory(void)
{
    return new MushGameVolatileData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameVolatileData", MushGameVolatileData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameVolatileData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "playerUplinkPeriodMsec=" << m_playerUplinkPeriodMsec << ", ";
    ioOut << "lastPlayerUplinkMsec=" << m_lastPlayerUplinkMsec;
    ioOut << "]";
}
bool
MushGameVolatileData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "playerUplinkPeriodMsec")
    {
        ioIn >> m_playerUplinkPeriodMsec;
    }
    else if (inTagStr == "lastPlayerUplinkMsec")
    {
        ioIn >> m_lastPlayerUplinkMsec;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameVolatileData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("playerUplinkPeriodMsec");
    ioOut << m_playerUplinkPeriodMsec;
    ioOut.TagSet("lastPlayerUplinkMsec");
    ioOut << m_lastPlayerUplinkMsec;
}
//%outOfLineFunctions } Df9tUbqlhQcIRkdMumUsoA
