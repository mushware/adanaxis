//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameUtil.cpp
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
//%Header } 8ZH+YByKztCX9b83kDeaRA
/*
 * $Id: MushGameUtil.cpp,v 1.4 2005/06/22 20:01:59 southa Exp $
 * $Log: MushGameUtil.cpp,v $
 * Revision 1.4  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.2  2005/06/21 13:10:52  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/20 16:14:31  southa
 * Adanaxis work
 *
 */

#include "MushGameUtil.h"

#include "MushGameClient.h"
#include "MushGameData.h"
#include "MushGameHostData.h"
#include "MushGameHostSaveData.h"
#include "MushGameHostVolatileData.h"
#include "MushGameMessage.h"
#include "MushGameLogic.h"
#include "MushGameLink.h"
#include "MushGameSaveData.h"
#include "MushGameServer.h"
#include "MushGameVolatileData.h"

void
MushGameUtil::MailboxToDigestMove(MushGameDigest& ioDigest, MushGameMailbox& ioMailbox)
{
    MushGameMessage *pMessage;
    while (ioMailbox.TakeIfAvailable(pMessage))
    {
        ioDigest.Give(pMessage);
    }
}

void
MushGameUtil::MailboxToServerMove(MushGameServer& ioServer, MushGameMailbox& ioBoxToMove, MushGameLogic& ioLogic)
{
    MushGameMessage *pMessage;
    while (ioBoxToMove.TakeIfAvailable(pMessage))
    {
        ioServer.MessageConsume(ioLogic, *pMessage);
    }
}

void
MushGameUtil::MailboxToClientMove(MushGameClient& ioClient, MushGameMailbox& ioBoxToMove, MushGameLogic& ioLogic)
{
    MushGameMessage *pMessage;
    while (ioBoxToMove.TakeIfAvailable(pMessage))
    {
        ioClient.MessageConsume(ioLogic, *pMessage);
    }
}

std::string
MushGameUtil::ObjectName(const std::string& inPrefix, const std::string& inSuffix)
{
    std::string basePrefix = "MushGame";

    std::string retName = inPrefix + inSuffix;
    if (!MushcoreFactory::Sgl().Exists(retName))
    {
        retName = basePrefix + inSuffix;
        if (!MushcoreFactory::Sgl().Exists(retName))
        {
            throw MushcoreLogicFail("Unknown object name '"+inPrefix+"/"+basePrefix+inSuffix+"'");
        }
    }
    return retName;
}

void
MushGameUtil::LocalGameCreate(const std::string& inName, const std::string& inPrefix)
{
    // Create the game objects
    DataObjectCreate<MushGameData>(inName, inPrefix, "Data")->GroupingNameSet(inName);
    DataObjectCreate<MushGameSaveData>(inName, inPrefix, "SaveData")->GroupingNameSet(inName);
    DataObjectCreate<MushGameVolatileData>(inName, inPrefix, "VolatileData")->GroupingNameSet(inName);
    DataObjectCreate<MushGameHostData>(inName, inPrefix, "HostData")->GroupingNameSet(inName);
    DataObjectCreate<MushGameHostSaveData>(inName, inPrefix, "HostSaveData")->GroupingNameSet(inName);
    DataObjectCreate<MushGameHostVolatileData>(inName, inPrefix, "HostVolatileData")->GroupingNameSet(inName);
    DataObjectCreate<MushGameServer>(inName, inPrefix, "Server")->GroupingNameSet(inName);
    DataObjectCreate<MushGameClient>(inName, inPrefix, "Client")->GroupingNameSet(inName);
    MushGameLogic *pLogic = DataObjectCreate<MushGameLogic>(inName, inPrefix, "LogicLocal");
    pLogic->GroupingNameSet(inName);

    // Create local addresses and links
    std::string serverName = inName+"-localserver";
    std::string clientName = inName+"-localclient";
    
    DataObjectCreate<MushGameAddress>(serverName, inPrefix, "Address")->NameSet(serverName);
    DataObjectCreate<MushGameAddress>(clientName, inPrefix, "Address")->NameSet(clientName);
    
    DataObjectCreate<MushGameLink>(serverName, inPrefix, "LinkLocal")->SrcDestSet(clientName, serverName);
    DataObjectCreate<MushGameLink>(clientName, inPrefix, "LinkLocal")->SrcDestSet(serverName, clientName);
    
    pLogic->ServerAddressSet(serverName);
    pLogic->ClientAddressAdd(clientName);
}

std::string
MushGameUtil::KeyFromMessage(const MushGameMessage& inMessage)
{
    const std::string& idRef = inMessage.Id();
    if (idRef.size() < 2)
    {
        throw MushcoreDataFail("Message ID '"+idRef+"' too short to extract key");
    }
    return idRef.substr(2);
}
