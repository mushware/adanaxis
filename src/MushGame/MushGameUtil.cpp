//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameUtil.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } eAXK2shReRuPxk9ARzaGHA
/*
 * $Id: MushGameUtil.cpp,v 1.12 2006/06/01 15:39:27 southa Exp $
 * $Log: MushGameUtil.cpp,v $
 * Revision 1.12  2006/06/01 15:39:27  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 * Revision 1.10  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.9  2005/06/30 16:29:25  southa
 * Adanaxis work
 *
 * Revision 1.8  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.7  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.6  2005/06/23 13:56:59  southa
 * MushGame link work
 *
 * Revision 1.5  2005/06/23 11:58:29  southa
 * MushGame link work
 *
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

#include "MushGameAppHandler.h"
#include "MushGameClient.h"
#include "MushGameData.h"
#include "MushGameHostData.h"
#include "MushGameHostSaveData.h"
#include "MushGameHostVolatileData.h"
#include "MushGameJobAdmission.h"
#include "MushGameJobPlayerCreate.h"
#include "MushGameLogic.h"
#include "MushGameLink.h"
#include "MushGameMessage.h"
#include "MushGameRender.h"
#include "MushGameSaveData.h"
#include "MushGameServer.h"
#include "MushGameVolatileData.h"

using namespace Mushware;
using namespace std;

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
    DataObjectCreate<MushGameRender>(inName, inPrefix, "Render")->GroupingNameSet(inName);
    MushGameLogic *pLogic = DataObjectCreate<MushGameLogic>(inName, inPrefix, "Logic");
    pLogic->GroupingNameSet(inName);

    // Create local addresses and links
    std::string serverName = inName+"-localserver";
    std::string clientName = inName+"-localclient";
    
    pLogic->SaveData().ClientNameSet(clientName);
    pLogic->SaveData().RenderNameSet(inName);
    pLogic->SaveData().ControlMailboxNameSet(inName+"-controlmailbox");
    pLogic->HostSaveData().ServerNameSet(serverName);
    
    DataObjectCreate<MushGameAddress>(serverName, inPrefix, "Address")->NameSet(serverName);
    DataObjectCreate<MushGameAddress>(clientName, inPrefix, "Address")->NameSet(clientName);
    
    DataObjectCreate<MushGameLink>(serverName, inPrefix, "LinkLocal")->SrcDestSet(clientName, serverName);
    DataObjectCreate<MushGameLink>(clientName, inPrefix, "LinkLocal")->SrcDestSet(serverName, clientName);
    
    pLogic->ServerAddressSet(serverName);
    pLogic->ClientAddressAdd(clientName);
}

void
MushGameUtil::LocalGameJobsCreate(MushGameLogic& ioLogic)
{
    std::string admissionName = "admission";
    MushGameJobAdmission *pAdmissionCreate = new MushGameJobAdmission("j:"+admissionName);
    ioLogic.HostSaveData().JobListWRef().Give(admissionName, pAdmissionCreate);
    
    std::string localPlayerCreateName = "localplayercreate";
    MushGameJobPlayerCreate *pLocalPlayerCreate = new MushGameJobPlayerCreate("j:"+localPlayerCreateName);
    ioLogic.SaveData().JobListWRef().Give(localPlayerCreateName, pLocalPlayerCreate);
}

std::string
MushGameUtil::KeyFromString(const std::string& inStr)
{
    if (inStr.size() < 2)
    {
        throw MushcoreDataFail("Message ID '"+inStr+"' too short to extract key");
    }
    string::size_type barPos = inStr.find("|");
    if (barPos == inStr.npos || barPos < 2)
    {
        return inStr.substr(2);
    }
    else
    {
        return inStr.substr(2, barPos - 2);        
    }
}

std::string
MushGameUtil::KeyFromMessage(const MushGameMessage& inMessage)
{
    return KeyFromString(inMessage.Id());
}

std::string
MushGameUtil::ReplyIDFromMessage(const MushGameMessage& inMessage)
{
    const std::string& idRef = inMessage.Id();
    if (idRef.size() < 2)
    {
        throw MushcoreDataFail("Message ID '"+idRef+"' too short to extract key");
    }
    string::size_type barPos = idRef.find("|");
    if (barPos == idRef.npos)
    {
        barPos = 0;
    }
    return idRef.substr(barPos+1);
}

MushGameAppHandler&
MushGameUtil::AppHandler(void)
{
    MushGameAppHandler *pAppHandler=dynamic_cast<MushGameAppHandler *>(&MushcoreAppHandler::Sgl());
    if (pAppHandler == NULL)
    {
        throw MushcoreRequestFail("AppHandler of wrong type for MushGameAppHandler");
    }
    return *pAppHandler;
}

std::string
MushGameUtil::ObjectName(Mushware::U8 inPrefix, Mushware::U32 inNumber)
{
    ostringstream nameStream;
    nameStream << static_cast<char>(inPrefix) << ':' << inNumber;
    return nameStream.str();
}

void
MushGameUtil::ObjectNameDecode(Mushware::U8& outPrefix, Mushware::U32& outNumber, const std::string& inName)
{
    istringstream nameStream(inName);
    char prefixChar, colonChar;

    nameStream >> prefixChar;
    if (nameStream) nameStream >> colonChar;
    if (nameStream) nameStream >> outNumber;
    if (!nameStream || colonChar != ':')
    {
        throw MushcoreDataFail("Cannot decode object name from '"+inName+"'");
    }
    outPrefix = prefixChar;
}



