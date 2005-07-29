//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameSaveData.cpp
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
//%Header } OWJ0lyKjoxUWAtsxD5Oexg
/*
 * $Id: MushGameSaveData.cpp,v 1.11 2005/07/06 19:08:27 southa Exp $
 * $Log: MushGameSaveData.cpp,v $
 * Revision 1.11  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.10  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.9  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.8  2005/06/24 10:30:13  southa
 * MushGame camera work
 *
 * Revision 1.7  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.6  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.5  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.3  2005/06/21 13:10:52  southa
 * MushGame work
 *
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 17:25:39  southa
 * Client/server work
 *
 */

#include "MushGameSaveData.h"

MUSHCORE_DATA_INSTANCE(MushGameSaveData);

MushGameSaveData::MushGameSaveData()
{
}

//%outOfLineFunctions {

const char *MushGameSaveData::AutoName(void) const
{
    return "MushGameSaveData";
}

MushcoreVirtualObject *MushGameSaveData::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'MushGameSaveData'");;
}

MushcoreVirtualObject *MushGameSaveData::AutoCreate(void) const
{
    return new MushGameSaveData;
}

MushcoreVirtualObject *MushGameSaveData::AutoVirtualFactory(void)
{
    return new MushGameSaveData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameSaveData", MushGameSaveData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameSaveData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "clientName=" << m_clientName << ", ";
    ioOut << "players=" << m_players << ", ";
    ioOut << "jobList=" << m_jobList << ", ";
    ioOut << "cameras=" << m_cameras << ", ";
    ioOut << "toServerMailbox=" << m_toServerMailbox << ", ";
    ioOut << "clientRef=" << m_clientRef << ", ";
    ioOut << "serverAddrRef=" << m_serverAddrRef << ", ";
    ioOut << "renderRef=" << m_renderRef << ", ";
    ioOut << "controlMailboxName=" << m_controlMailboxName;
    ioOut << "]";
}
bool
MushGameSaveData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "clientName")
    {
        ioIn >> m_clientName;
    }
    else if (inTagStr == "players")
    {
        ioIn >> m_players;
    }
    else if (inTagStr == "jobList")
    {
        ioIn >> m_jobList;
    }
    else if (inTagStr == "cameras")
    {
        ioIn >> m_cameras;
    }
    else if (inTagStr == "toServerMailbox")
    {
        ioIn >> m_toServerMailbox;
    }
    else if (inTagStr == "clientRef")
    {
        ioIn >> m_clientRef;
    }
    else if (inTagStr == "serverAddrRef")
    {
        ioIn >> m_serverAddrRef;
    }
    else if (inTagStr == "renderRef")
    {
        ioIn >> m_renderRef;
    }
    else if (inTagStr == "controlMailboxName")
    {
        ioIn >> m_controlMailboxName;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameSaveData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("clientName");
    ioOut << m_clientName;
    ioOut.TagSet("players");
    ioOut << m_players;
    ioOut.TagSet("jobList");
    ioOut << m_jobList;
    ioOut.TagSet("cameras");
    ioOut << m_cameras;
    ioOut.TagSet("toServerMailbox");
    ioOut << m_toServerMailbox;
    ioOut.TagSet("clientRef");
    ioOut << m_clientRef;
    ioOut.TagSet("serverAddrRef");
    ioOut << m_serverAddrRef;
    ioOut.TagSet("renderRef");
    ioOut << m_renderRef;
    ioOut.TagSet("controlMailboxName");
    ioOut << m_controlMailboxName;
}
//%outOfLineFunctions } o0ZngYG0x1H+8zLQkWKldg
