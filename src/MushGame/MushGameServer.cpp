//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameServer.cpp
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
//%Header } Ib2b3u1bPJ3KuhedcK69TA
/*
 * $Id: MushGameServer.cpp,v 1.2 2005/06/20 14:30:36 southa Exp $
 * $Log: MushGameServer.cpp,v $
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:48:59  southa
 * Client/server work
 *
 */

#include "MushGameServer.h"

#include "MushGameMessageJoinRequest.h"

MUSHCORE_DATA_INSTANCE(MushGameServer);

MushGameServer::MushGameServer()
{
}

void
MushGameServer::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const MushGameMessageJoinRequest *joinRequest = dynamic_cast<const MushGameMessageJoinRequest *>(&inMessage);
    if (joinRequest != NULL)
    {
        JoinRequestConsume(ioLogic, inMessage);
    }
    else
    {
        throw MushcoreDataFail(std::string("Unhandled message type ")+inMessage.AutoName());
    }
}

void
MushGameServer::JoinRequestConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("No handler provided for ")+inMessage.AutoName());
}

//%outOfLineFunctions {

const char *MushGameServer::AutoName(void) const
{
    return "MushGameServer";
}

MushcoreVirtualObject *MushGameServer::AutoClone(void) const
{
    return new MushGameServer(*this);
}

MushcoreVirtualObject *MushGameServer::AutoCreate(void) const
{
    return new MushGameServer;
}

MushcoreVirtualObject *MushGameServer::AutoVirtualFactory(void)
{
    return new MushGameServer;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameServer", MushGameServer::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameServer::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "saveDataRef=" << m_saveDataRef;
    ioOut << "]";
}
bool
MushGameServer::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "saveDataRef")
    {
        ioIn >> m_saveDataRef;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGameServer::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("saveDataRef");
    ioOut << m_saveDataRef;
}
//%outOfLineFunctions } CSvml7QDl5mOOJ/uHA/qQw
