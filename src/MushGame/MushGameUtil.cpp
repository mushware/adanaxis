//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameUtil.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } oQaGYO8jpftpyXnIPKJgUw
/*
 * $Id: MushGameUtil.cpp,v 1.17 2006/12/14 00:33:49 southa Exp $
 * $Log: MushGameUtil.cpp,v $
 * Revision 1.17  2006/12/14 00:33:49  southa
 * Control fix and audio pacing
 *
 * Revision 1.16  2006/10/04 13:35:24  southa
 * Selective targetting
 *
 * Revision 1.15  2006/09/29 10:47:56  southa
 * Object AI
 *
 * Revision 1.14  2006/07/07 18:13:59  southa
 * Menu start and stop
 *
 * Revision 1.13  2006/06/29 11:40:40  southa
 * X11 and 64 bit fixes
 *
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

MushGameLogic&
MushGameUtil::LogicWRef(void)
{
    return AppHandler().LogicWRef();    
}

const MushGameLogic&
MushGameUtil::LogicRef(void)
{
    return AppHandler().LogicWRef();    
}

std::string
MushGameUtil::ObjectName(const std::string& inPrefix, Mushware::U32 inNumber)
{
    ostringstream nameStream;
    nameStream << inPrefix << ':' << inNumber;
    return nameStream.str();
}

void
MushGameUtil::ObjectNameDecode(std::string& outPrefix, Mushware::U32& outNumber, const std::string& inName)
{
    string::size_type pos = inName.find(':');
    if (pos == string::npos || pos == 0)
    {
        throw MushcoreDataFail("Cannot decode object name from '"+inName+"' - no colon");
    }
    
    outPrefix = inName.substr(0, pos);
    istringstream nameStream(inName.substr(pos+1));
    if (nameStream) nameStream >> outNumber;
    
    if (!nameStream)
    {
        throw MushcoreDataFail("Cannot decode object name from '"+inName+"'");
    }
}

std::string
MushGameUtil::StripFlags(std::vector<std::string> outFlags, const std::string& inString)
{
    string::size_type startPos = 0;
    string::size_type endPos = 0;
    while (inString.size() > startPos && inString[startPos] == '[')
    {
        endPos = inString.find(']', startPos);
        if (endPos == string::npos)
        {
            throw MushcoreDataFail("Malformed flags in '"+inString+"'");   
        }
        outFlags.push_back(inString.substr(startPos+1, endPos-startPos-1));
        startPos = endPos+1;
    }
    
    return inString.substr(startPos);
}

