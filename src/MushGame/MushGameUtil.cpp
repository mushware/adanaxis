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
 * $Id: MushGameUtil.cpp,v 1.1 2005/06/20 16:14:31 southa Exp $
 * $Log: MushGameUtil.cpp,v $
 * Revision 1.1  2005/06/20 16:14:31  southa
 * Adanaxis work
 *
 */

#include "MushGameUtil.h"

#include "MushGameClient.h"
#include "MushGameData.h"
#include "MushGameLogic.h"
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
MushGameUtil::MailboxToServerMove(MushGameServer& ioServer, MushGameMailbox& ioBoxToMove, MushGameMailbox& ioReplyBox)
{
    MushGameMessage *pMessage;
    while (ioBoxToMove.TakeIfAvailable(pMessage))
    {
        ioServer.MessageConsume(ioReplyBox, *pMessage);
    }
}

void
MushGameUtil::MailboxToClientMove(MushGameClient& ioClient, MushGameMailbox& ioBoxToMove, MushGameMailbox& ioReplyBox)
{
    MushGameMessage *pMessage;
    while (ioBoxToMove.TakeIfAvailable(pMessage))
    {
        ioClient.MessageConsume(ioReplyBox, *pMessage);
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
    MushGameData *pData = DataObjectCreate<MushGameData>(inName, inPrefix, "Data");
    DataObjectCreate<MushGameSaveData>(inName, inPrefix, "SaveData");
    DataObjectCreate<MushGameVolatileData>(inName, inPrefix, "VolatileData");
    DataObjectCreate<MushGameServer>(inName, inPrefix, "Server");
    DataObjectCreate<MushGameClient>(inName, inPrefix, "Client");
    DataObjectCreate<MushGameLogic>(inName, inPrefix, "LogicLocal");
    
    pData->SaveDataRefWRef().NameSet(inName);
    pData->VolatileDataRefWRef().NameSet(inName);
    
    MushcoreXMLOStream xmlOut(std::cout);
    xmlOut << MushcoreData<MushGameSaveData>::Sgl();
    xmlOut << MushcoreData<MushGameVolatileData>::Sgl();
}
