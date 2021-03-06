//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLogic.cpp
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
//%Header } jNU7FmS9PiUSJX10bGAhlg
/*
 * $Id: MushGameLogic.cpp,v 1.48 2007/04/17 10:08:20 southa Exp $
 * $Log: MushGameLogic.cpp,v $
 * Revision 1.48  2007/04/17 10:08:20  southa
 * Voice work
 *
 * Revision 1.47  2007/04/16 08:41:10  southa
 * Level and header mods
 *
 * Revision 1.46  2007/03/09 11:29:13  southa
 * Game end actions
 *
 * Revision 1.45  2007/03/08 18:38:15  southa
 * Level progression
 *
 * Revision 1.44  2007/03/08 11:00:30  southa
 * Level epilogue
 *
 * Revision 1.43  2007/03/07 16:59:44  southa
 * Khazi spawning and level ends
 *
 * Revision 1.42  2007/03/06 11:34:01  southa
 * Space and precache fixes
 *
 * Revision 1.41  2007/02/08 17:55:15  southa
 * Common routines in space generation
 *
 * Revision 1.40  2006/12/14 00:33:49  southa
 * Control fix and audio pacing
 *
 * Revision 1.39  2006/12/11 18:54:18  southa
 * Positional audio
 *
 * Revision 1.38  2006/11/23 14:40:29  southa
 * Intro cutscene
 *
 * Revision 1.37  2006/11/21 10:08:24  southa
 * Initial cut scene handling
 *
 * Revision 1.36  2006/11/09 23:53:59  southa
 * Explosion and texture loading
 *
 * Revision 1.35  2006/11/08 11:35:00  southa
 * Basic frame rate independence
 *
 * Revision 1.34  2006/10/17 15:28:02  southa
 * Player collisions
 *
 * Revision 1.33  2006/10/12 22:04:48  southa
 * Collision events
 *
 * Revision 1.32  2006/10/04 13:35:24  southa
 * Selective targetting
 *
 * Revision 1.31  2006/10/02 20:28:11  southa
 * Object lookup and target selection
 *
 * Revision 1.30  2006/10/02 17:25:05  southa
 * Object lookup and target selection
 *
 * Revision 1.29  2006/07/28 16:52:23  southa
 * Options work
 *
 * Revision 1.28  2006/07/28 11:14:28  southa
 * Records for multiple spaces
 *
 * Revision 1.27  2006/07/20 12:22:21  southa
 * Precache display
 *
 * Revision 1.26  2006/07/08 16:05:59  southa
 * Ruby menus and key handling
 *
 * Revision 1.25  2006/07/07 18:13:58  southa
 * Menu start and stop
 *
 * Revision 1.24  2006/07/04 16:55:27  southa
 * Ruby key handling
 *
 * Revision 1.23  2006/06/30 17:26:10  southa
 * Render prelude
 *
 * Revision 1.22  2006/06/30 15:05:35  southa
 * Texture and buffer purge
 *
 * Revision 1.21  2006/06/01 15:39:23  southa
 * DrawArray verification and fixes
 *
 * Revision 1.20  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 * Revision 1.19  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.18  2005/07/12 12:18:18  southa
 * Projectile work
 *
 * Revision 1.17  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.16  2005/07/11 14:48:46  southa
 * Uplink work
 *
 * Revision 1.15  2005/07/07 16:54:17  southa
 * Control tweaks
 *
 * Revision 1.14  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.13  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
 * Revision 1.12  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.11  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.10  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.9  2005/06/30 16:29:25  southa
 * Adanaxis work
 *
 * Revision 1.8  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.7  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 * Revision 1.6  2005/06/24 10:30:12  southa
 * MushGame camera work
 *
 * Revision 1.5  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameLogic.h"

#include "MushGameAddress.h"
#include "MushGameAppHandler.h"
#include "MushGameAnimPostManip.h"
#include "MushGameIntern.h"
#include "MushGameJob.h"
#include "MushGameLink.h"
#include "MushGameMessageWake.h"
#include "MushGameRefPlayer.h"
#include "MushGameUtil.h"

MUSHCORE_DATA_INSTANCE(MushGameLogic);

using namespace Mushware;
using namespace std;

Mushware::U32
MushGameLogic::GameMsec(void) const
{
    return VolatileData().GameMsec();
}

MushGamePiece&
MushGameLogic::PieceLookup(const std::string& inName) const
{
    MushGamePiece *pPiece = NULL;
    std::string objType;
    Mushware::U32 objNum;
    MushGameUtil::ObjectNameDecode(objType, objNum, inName);

    MUSHCOREASSERT(objType.size() > 0);
    switch (objType[0])
    {
        case MushGameData::kCharPlayer:
            pPiece = &SaveData().PlayersList().Get(objNum);
            if (pPiece->ExpireFlag())
            {
                throw MushcoreDataFail("Expired object type '"+inName+"'");
            }
            break;

        default:
            throw MushcoreDataFail("Unknown object type '"+inName+"'");
            break;
    }
    return *pPiece;
}

void
MushGameLogic::TargetPieceSearch(std::string& ioID,
                                 Mushware::tVal& ioDistSquared,
                                 const Mushware::t4Val& inPos,
                                 const std::string& inObjType,
                                 const std::string& inExcludeID) const
{
    if (inObjType.size() < 1)
    {
        throw MushcoreDataFail("Object type of zero length");
    }
    switch (inObjType[0])
    {
        case MushGameData::kCharPlayer:
        {
            typedef MushcoreMaptor<MushGamePiecePlayer>::const_iterator tIterator;
            const MushcoreMaptor<MushGamePiecePlayer>& playerData = SaveData().PlayersList();
            for (tIterator p = playerData.begin(); p != playerData.end(); ++p)
            {
                if (!p->ExpireFlag())
                {
                    t4Val vecToObj = inPos - p->Post().Pos();
                    tVal distToObjSquared = vecToObj.MagnitudeSquared();
                    if (ioID == "" || distToObjSquared < ioDistSquared)
                    {
                        std::string newID = MushGameUtil::ObjectName(inObjType, p.Key());
                        if (newID != inExcludeID)
                        {
                            ioDistSquared = distToObjSquared;
                            ioID = newID;
                        }
                    }
                }
            }
        }
        break;

        default:
            ostringstream message;
            message <<"Unknown object type '" << inObjType << "' in TargetPieceSearch";
            throw MushcoreDataFail(message.str());
            break;
    }
}

std::string
MushGameLogic::TargetPieceSelect(const MushMeshPosticity& inPost, const std::string& inTypes,
                                 const std::string& inExcludeID) const
{
    std::string pieceID;
    tVal distToPieceSquared = 0;
    
    const t4Val& objPos = inPost.Pos();
    
    std::string::size_type pos = 0;
    std::string::size_type foundPos = 0;
    
    do
    {
        foundPos = inTypes.find_first_of("+,", pos);
        TargetPieceSearch(pieceID, distToPieceSquared, objPos, inTypes.substr(pos, foundPos - pos), inExcludeID);
        pos = foundPos + 1;
        /* Always keep searching after a plus, but only keep searching after a comma if
         * we've found nothing so far
         */
    } while (foundPos != string::npos && (inTypes[foundPos] == '+' || pieceID == ""));
    
    return pieceID;
}

void
MushGameLogic::JobListProcess(tJobList& ioList)
{
    U32 msecNow = GameMsec();
    
    for (tJobList::tIterator p = ioList.Begin(); p != ioList.End(); )
    {
        MushGameJob *pJob = p->second;
        MUSHCOREASSERT(pJob != NULL);
        if (pJob->ShouldWake())
        {
            if (pJob->WakeTime() <= msecNow)
            {
                MushGameMessageWake wakeMessage("wakeup");
                try
                {
                    pJob->MessageConsume(*this, wakeMessage);
                }
                catch (MushcoreNonFatalFail& e)
                {
                    MushcoreLog::Sgl().ErrorLog() << "Job wake consumption failure: " << e.what() << endl
                        << "Job was '" << p->first << "': " << *pJob << endl;
                    pJob->CompleteSet(true);
                }
            }
        }
        
        tJobList::tIterator oldP = p;
        ++p;

        if (pJob->Complete())
        {
            ioList.Delete(oldP);
        }
    }
}

void
MushGameLogic::PerFrameProcessing(void)
{
    JobListProcess(SaveData().JobListWRef());
    JobListProcess(HostSaveData().JobListWRef());
}

void
MushGameLogic::DefaultMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("Discarding message of type '")+inMessage.AutoName()+"' with no ID");
}

void
MushGameLogic::CollisionMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("Discarding message of type '")+inMessage.AutoName()+"' with collision ID");
}

void
MushGameLogic::JobMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    std::string jobName = MushGameUtil::KeyFromMessage(inMessage);
    
    MushGameJob *pJob;
    if (SaveData().JobList().GetIfExists(pJob, jobName))
    {
        pJob->MessageConsume(ioLogic, inMessage);
    }
    else if (HostSaveData().JobList().GetIfExists(pJob, jobName))
    {
        pJob->MessageConsume(ioLogic, inMessage);        
    }
    else
    {
        throw MushcoreDataFail(std::string("Unknown job ID '")+jobName+"' in message type '"+inMessage.AutoName()+"'");
    }
}

void
MushGameLogic::ServerPlayerMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    std::string objType;
    Mushware::U32 objNum;
    MushGameUtil::ObjectNameDecode(objType, objNum, inMessage.Id());
    
    MushGamePiecePlayer *pPlayer;
    if (HostSaveData().HostPlayersList().GetIfExists(pPlayer, objNum))
    {
        pPlayer->MessageConsume(ioLogic, inMessage);
    }
    else
    {
        throw MushcoreDataFail(std::string("Unknown player ID '")+inMessage.Id()+"' in message type '"+inMessage.AutoName()+"'");
    }
}

void
MushGameLogic::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const std::string& msgID = inMessage.Id();
    
    if (msgID == "")
    {
        DefaultMessageConsume(ioLogic, inMessage);
    }
    else
    {
        switch (msgID[0])
        {
            case MushGameData::kCharCollision:
                CollisionMessageConsume(ioLogic, inMessage);
                break;
                
            case MushGameData::kCharJob:
                JobMessageConsume(ioLogic, inMessage);
                break;
                
            case MushGameData::kCharPlayer:
                ServerPlayerMessageConsume(ioLogic, inMessage);
                break;
                
            default:
                throw MushcoreDataFail(std::string("Discarding message of type '")+inMessage.AutoName()+"' with unknown ID prefix");
                break;
        }
    }
}

void
MushGameLogic::ServerAddressSet(const std::string& inName)
{
    SaveData().ServerAddrRefWRef().NameSet(inName);    
}

void
MushGameLogic::ClientAddressAdd(const std::string& inName)
{
    MushcoreDataRef<MushGameAddress> clientAddressRef(inName);
    HostSaveData().ClientAddrRefsWRef().push_back(clientAddressRef);    
}

void
MushGameLogic::CopyAndSendToServer(const MushGameMessage& inMessage)
{
    try
    {
        // Find the link
        SaveData().ServerAddrRef().Ref().LinkRef().WRef().ToOutboxCopy(inMessage);
    }
    catch (MushcoreNonFatalFail& e)
    {
        MushcoreLog::Sgl().WarningLog() << e.what() << endl;
    }
}

void
MushGameLogic::AsReplyCopyAndSend(MushGameMessage& ioMessage, const MushGameMessage& inSrcMessage)
{
    try
    {
        ioMessage.IdSet(MushGameUtil::ReplyIDFromMessage(inSrcMessage));
        inSrcMessage.SrcAddrRef().Ref().LinkRef().WRef().ToOutboxCopy(ioMessage);
    }
    catch (MushcoreNonFatalFail& e)
    {
        MushcoreLog::Sgl().WarningLog() << e.what() << endl;
    }
}

void
MushGameLogic::CopyAndBroadcast(const MushGameMessage& inMessage)
{
    // Send message to all clients on the server's list
    typedef MushGameHostSaveData::tClientAddrRefs tClientAddrRefs;
    
    tClientAddrRefs& clientAddrRefs = HostSaveData().ClientAddrRefsWRef();
    
    for (tClientAddrRefs::iterator p = clientAddrRefs.begin(); p != clientAddrRefs.end(); ++p)
    {
        try
        {
            p->Ref().LinkRef().WRef().ToOutboxCopy(inMessage);
        }
        catch (MushcoreNonFatalFail& e)
        {
            MushcoreLog::Sgl().WarningLog() << e.what() << endl;
        }
    }
}

void
MushGameLogic::ClientMailboxConsume(MushGameMailbox& inMailbox)
{
    std::auto_ptr<MushGameMessage> aMessage;
    while (inMailbox.TakeIfAvailable(aMessage))
    {
        MUSHCOREASSERT(&*aMessage != NULL);
        aMessage->SrcAddrRefSet(inMailbox.SrcAddrRef());
        try
        {
            MessageConsume(*this, *aMessage);
        }
        catch (MushcoreNonFatalFail& e)
        {
            MushcoreLog::Sgl().WarningLog() << e.what() << ": " << *aMessage << endl;
        }
    }
}

void
MushGameLogic::ServerMailboxConsume(MushGameMailbox& inMailbox)
{
    std::auto_ptr<MushGameMessage> aMessage;
    while (inMailbox.TakeIfAvailable(aMessage))
    {
        MUSHCOREASSERT(&*aMessage != NULL);
        aMessage->SrcAddrRefSet(inMailbox.SrcAddrRef());
        try
        {
            MessageConsume(*this, *aMessage);
        }
        catch (MushcoreNonFatalFail& e)
        {
            MushcoreLog::Sgl().WarningLog() << e.what() << ": " << *aMessage << endl;
        }
    }
}

void
MushGameLogic::TimingSequence(void)
{
    Mushware::U32 timeNow = MushGameUtil::AppHandler().MillisecondsGet();
    Mushware::U32 timeDiff = timeNow - static_cast<U32>(VolatileData().LastGameMsec());
    
    VolatileData().AverageMsecPerFrameSet(VolatileData().AverageMsecPerFrame() * 0.8 + timeDiff * 0.2);
    
    // Move rate is 60Hz
    tVal msecPerMove = 1000.0 / 60.0;
    tVal idealMoveTicker = timeNow / msecPerMove;
    
    tVal idealMovesThisFrame = idealMoveTicker - VolatileData().MoveTicker();

    if (idealMovesThisFrame < 0 || idealMovesThisFrame > 100)
    {
        // Counters wrongly set - use one frame
        idealMovesThisFrame = 0;
    }

    U32 movesThisFrame = static_cast<U32>(idealMovesThisFrame + 0.49);
    
    MushcoreUtil::Constrain<U32>(movesThisFrame, 0, 5);

    VolatileData().MovesThisFrameSet(movesThisFrame);
    
    if (IsGameMode() || IsEpilogueMode())
    {
        VolatileData().GameMsecSet(VolatileData().GameMsec() +
                static_cast<tMsec>(movesThisFrame * msecPerMove));
    }
    
    tVal newMoveTicker = VolatileData().MoveTicker() + movesThisFrame;

    if (idealMoveTicker - newMoveTicker > 5.0)
    {
        // Ideal ticker running ahead - drop frames
        newMoveTicker = idealMoveTicker - 5.0;
    }
    else if (idealMoveTicker - newMoveTicker < -5.0)
    {
        // Overrun
        newMoveTicker = idealMoveTicker;
    }

    VolatileData().MoveTickerSet(newMoveTicker);

    VolatileData().LastGameMsecSet(timeNow);
    VolatileData().FrameMsecSet(VolatileData().GameMsec());
}

void
MushGameLogic::ClientReceiveSequence(void)
{
    // I am a client picking up messages from my server
    MushGameMailbox mailbox;
    const MushcoreDataRef<MushGameAddress>& addrDataRef = SaveData().ServerAddrRef();
    if (addrDataRef.Ref().LinkRef().WRef().InboxGetUnlessEmpty(mailbox))
    {
        // MushcoreLog::Sgl().InfoLog() << "Receiving from address " << addrDataRef.Ref() << endl;
        mailbox.SrcAddrRefSet(addrDataRef);
        ClientMailboxConsume(mailbox);
    }
}

void
MushGameLogic::ServerReceiveSequence(void)
{
    // I am the server picking up my messages from clients
    typedef MushGameHostSaveData::tClientAddrRefs tClientAddrRefs;
    
    tClientAddrRefs& clientAddrRefs = HostSaveData().ClientAddrRefsWRef();
        
    for (tClientAddrRefs::iterator p = clientAddrRefs.begin(); p != clientAddrRefs.end(); ++p)
    {
        MushGameMailbox mailbox;
        if (p->Ref().LinkRef().WRef().InboxGetUnlessEmpty(mailbox))
        {
            // MushcoreLog::Sgl().InfoLog() << "Receiving from address " << p->Ref() << endl;
            mailbox.SrcAddrRefSet(*p);
            ServerMailboxConsume(mailbox);
        }
    }
}

void
MushGameLogic::ClientSendSequence(void)
{
    SaveData().ServerAddrRef().Ref().LinkRef().WRef().OutboxSendUnlessEmpty();
}

void
MushGameLogic::ServerSendSequence(void)
{
    // I am the server sending my outboxes
    typedef MushGameHostSaveData::tClientAddrRefs tClientAddrRefs;
    
    tClientAddrRefs& clientAddrRefs = HostSaveData().ClientAddrRefsWRef();
    
    for (tClientAddrRefs::iterator p = clientAddrRefs.begin(); p != clientAddrRefs.end(); ++p)
    {
        p->Ref().LinkRef().WRef().OutboxSendUnlessEmpty();
    }
}

void
MushGameLogic::ReceiveSequence(void)
{
    ServerReceiveSequence();
    ClientReceiveSequence();
}

void
MushGameLogic::SendSequence(void)
{
    ServerSendSequence();
    ClientSendSequence();
}

void
MushGameLogic::PlayerUplink(MushGamePiecePlayer& inPlayer)
{
    inPlayer.UplinkSend(*this);
}    

void
MushGameLogic::PlayerUplinkSequence(void)
{
    typedef MushcoreMaptor<MushGamePiecePlayer>::iterator tIterator;
    MushcoreMaptor<MushGamePiecePlayer>& playerData = SaveData().PlayersListWRef();
    for (tIterator p = playerData.begin(); p != playerData.end(); ++p)
    {
        PlayerUplink(*p);
    }
}

void
MushGameLogic::UplinkSequence(void)
{
    tMsec msecNow = GameMsec();

    tMsec lastUplink = VolatileData().LastPlayerUplinkMsec();
    tMsec uplinkPeriod = VolatileData().PlayerUplinkPeriodMsec();

    tMsec nextUplink = lastUplink + uplinkPeriod;
    
    if (VolatileData().QuickPlayerUplinkRequired())
    {
        VolatileData().QuickPlayerUplinkRequiredSet(false);
        nextUplink = msecNow;
    }
    
    if (msecNow >= nextUplink)
    {
        if (msecNow > nextUplink + uplinkPeriod)
        {
            nextUplink = msecNow; // Catch up
        }
        // Update lastPlayerUplinkMsec now, so exceptions in the update don't cause network thrash
        VolatileData().LastPlayerUplinkMsecSet(nextUplink);
        
        PlayerUplinkSequence();
    }
}

void
MushGameLogic::PlayerMove(MushGamePiecePlayer& inPlayer)
{
    inPlayer.PreControl(*this);
    inPlayer.ControlMailboxProcess(*this);
    inPlayer.Move(*this, 1);
}

void
MushGameLogic::MoveSequence(void)
{
    typedef MushcoreMaptor<MushGamePiecePlayer>::iterator tIterator;
    MushcoreMaptor<MushGamePiecePlayer>& playerData = SaveData().PlayersListWRef();
    for (tIterator p = playerData.begin(); p != playerData.end(); ++p)
    {
        PlayerMove(*p);
    }
}

void
MushGameLogic::CollideSequence(void)
{
}

void
MushGameLogic::PlayerTicker(MushGamePiecePlayer& inPlayer)
{
    inPlayer.TickerProcess(*this);
}

void
MushGameLogic::TickerSequence(void)
{
    typedef MushcoreMaptor<MushGamePiecePlayer>::iterator tIterator;
    MushcoreMaptor<MushGamePiecePlayer>& playerData = SaveData().PlayersListWRef();
    for (tIterator p = playerData.begin(); p != playerData.end(); ++p)
    {
        PlayerTicker(*p);
    }
    
    Mushware::U32 timeNow = MushGameUtil::AppHandler().MillisecondsGet();

    if (timeNow - VolatileData().Last100msTickMsec() >= 100)
    {
        Tick100msSequence();
        VolatileData().Last100msTickMsecSet(timeNow);
    }
}

void
MushGameLogic::Tick100msSequence(void)
{
    MediaAudio::Sgl().Ticker();    
}

void
MushGameLogic::CameraMove(MushGameCamera& inCamera)
{
    inCamera.FromTiedObjectUpdate();
    MediaAudio::Sgl().ListenerPostSet(inCamera.Post());
}

void
MushGameLogic::CameraSequence(void)
{
    typedef MushcoreData<MushGameCamera>::tIterator tIterator;
    MushcoreData<MushGameCamera>& cameraData = SaveData().CamerasWRef();
    for (tIterator p = cameraData.Begin(); p != cameraData.End(); ++p)
    {
        CameraMove(*p->second);
    }
}

void
MushGameLogic::MenuSequence(void)
{
}

void
MushGameLogic::CutSceneSequence(void)
{
}

void
MushGameLogic::PrecacheSequence(void)
{
}

void
MushGameLogic::RenderSequence(void)
{
    typedef MushcoreData<MushGameCamera>::tIterator tIterator;
    MushcoreData<MushGameCamera>& cameraData = SaveData().CamerasWRef();
    for (tIterator p = cameraData.Begin(); p != cameraData.End(); ++p)
    {
        if (IsPrecacheMode())
        {
            SaveData().RenderRef().WRef().PrecacheRender(*this, *p->second);        
        }
        else
        {
            SaveData().RenderRef().WRef().FrameRender(*this, *p->second);
        }
    }
}

void
MushGameLogic::MainSequence(void)
{
    try { TimingSequence(); }
    catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "TimingSequence"); }
    try { ReceiveSequence(); }
    catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "ReceiveSequence"); }
    try { SendSequence(); }
    catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "SendSequence"); }
    
    if (!IsPrecacheMode()) // Never move during precache
    {
        if (IsGameMode() || IsEpilogueMode() || VolatileData().IsMenuBackdrop())
        {
            for (U32 i=0; i<VolatileData().MovesThisFrame(); ++i)
            {
                try { MoveSequence(); }
                catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "MoveSequence"); }
                try { CollideSequence(); }
                catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "CollideSequence"); }
                if (i>10)
                {
                    throw MushcoreLogicFail("Move overrun");
                }
            }
        }
    }
    try { TickerSequence(); }
    catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "TickerSequence"); }
    try { UplinkSequence(); }
    catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "UplinkSequence"); }
    try { SendSequence(); }
    catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "SendSequence"); }
    try { CameraSequence(); }
    catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "CameraSequence"); }
    if (IsMenuMode())
    {
        try { MenuSequence(); }
        catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "MenuSequence"); }
    }
    if (IsPrecacheMode())
    {
        try { PrecacheSequence(); }
        catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "PrecacheSequence"); }
    }
    try { RenderSequence(); }
    catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "RenderSequence"); }
    if (IsCutSceneMode())
    {
        try { CutSceneSequence(); }
        catch (MushcoreNonFatalFail& e) { ExceptionHandle(&e, "CutSceneSequence"); }
    }    
}

void
MushGameLogic::MenuModeEnter(void)
{
    MushGameUtil::AppHandler().KeyRepeatSet(true);
    VolatileData().GameModeSet(MushGameVolatileData::kGameModeMenu);
    PrecacheModeEnter();
}

void
MushGameLogic::GameModeEnter(void)
{
    MushGameUtil::AppHandler().KeyRepeatSet(false);
    VolatileData().GameModeSet(MushGameVolatileData::kGameModeGame);
    PrecacheModeEnter();
}

void
MushGameLogic::CutSceneModeEnter(void)
{
    MushGameUtil::AppHandler().KeyRepeatSet(false);
    VolatileData().GameModeSet(MushGameVolatileData::kGameModeCutScene);
    PrecacheModeEnter();
}

void
MushGameLogic::CutSceneModeExit(void)
{
    MushGameUtil::AppHandler().KeyRepeatSet(false);
    VolatileData().GameModeSet(MushGameVolatileData::kGameModeGame);
}

void
MushGameLogic::EpilogueModeEnter(Mushware::U32 inResult)
{
    if (VolatileData().GameMode() != MushGameVolatileData::kGameModeEpilogue)
    {
        VolatileData().GameModeSet(MushGameVolatileData::kGameModeEpilogue);
        VolatileData().GameResultSet(inResult);
        Mushware::tMsec timeNow = MushGameUtil::AppHandler().MillisecondsGet();
        VolatileData().EpilogueStartMsecSet(timeNow);
        
        if (inResult == MushGameData::kGameResultWon)
        {
            MushRubyExec::Sgl().Call(VolatileData().RubyGame(),
                                     MushGameIntern::Sgl().mEpilogueStartWon());
        }
        else if (inResult == MushGameData::kGameResultLost)
        {
            MushRubyExec::Sgl().Call(VolatileData().RubyGame(),
                                     MushGameIntern::Sgl().mEpilogueStartLost());
        }
        else
        {
            MushRubyExec::Sgl().Call(VolatileData().RubyGame(),
                                     MushGameIntern::Sgl().mEpilogueStartDead());
        }
    }
}

void
MushGameLogic::QuitModeEnter(void)
{
    VolatileData().GameModeSet(MushGameVolatileData::kGameModeQuit);
    MushGameUtil::AppHandler().QuitStateEnter();
}

void
MushGameLogic::PrecacheModeEnter(void)
{
    MushGLTexture::ByteCountSet(0);
    VolatileData().PrecacheSet(true);
}

void
MushGameLogic::PrecacheModeExit(void)
{
    VolatileData().PrecacheSet(false);
}

bool
MushGameLogic::IsMenuMode(void) const
{
    return VolatileData().GameMode() == MushGameVolatileData::kGameModeMenu;    
}


bool
MushGameLogic::IsPrecacheMode(void) const
{
    return VolatileData().Precache();    
}

bool
MushGameLogic::IsGameMode(void) const
{
    return VolatileData().GameMode() == MushGameVolatileData::kGameModeGame;    
}

bool
MushGameLogic::IsCutSceneMode(void) const
{
    return VolatileData().GameMode() == MushGameVolatileData::kGameModeCutScene;    
}

bool
MushGameLogic::IsEpilogueMode(void) const
{
    return VolatileData().GameMode() == MushGameVolatileData::kGameModeEpilogue;    
}

bool
MushGameLogic::EpilogueWon(void) const
{
    return VolatileData().GameResult() == MushGameData::kGameResultWon;    
}

void
MushGameLogic::ExceptionHandle(std::exception *inpFail, const std::string& inName) const
{
    MushcoreLog::Sgl().ErrorLog() << "In " << AutoName() << ": " << inpFail->what() << endl;
}

void
MushGameLogic::ClientNewPlayerHandle(Mushware::U32 inPlayerNum)
{
    MushGameCamera *pCamera = SaveData().CamerasWRef().GetOrCreate("default-camera");
                              
    MushGameRefPlayer playerRef(inPlayerNum, &SaveData().PlayersListWRef());
    pCamera->TiedRefCopy(&playerRef);
}


MushRubyValue
MushGameLogic::NewLogic(void)
{
    return MushRubyUtil::GlobalVar("$currentLogic");
}

//%outOfLineFunctions {

const char *MushGameLogic::AutoName(void) const
{
    return "MushGameLogic";
}

MushcoreVirtualObject *MushGameLogic::AutoClone(void) const
{
    return new MushGameLogic(*this);
}

MushcoreVirtualObject *MushGameLogic::AutoCreate(void) const
{
    return new MushGameLogic;
}

MushcoreVirtualObject *MushGameLogic::AutoVirtualFactory(void)
{
    return new MushGameLogic;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameLogic", MushGameLogic::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameLogic::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "dataRef=" << m_dataRef << ", ";
    ioOut << "hostDataRef=" << m_hostDataRef << ", ";
    ioOut << "rubyLogic=" << m_rubyLogic;
    ioOut << "]";
}
bool
MushGameLogic::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "dataRef")
    {
        ioIn >> m_dataRef;
    }
    else if (inTagStr == "hostDataRef")
    {
        ioIn >> m_hostDataRef;
    }
    else if (inTagStr == "rubyLogic")
    {
        ioIn >> m_rubyLogic;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameLogic::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("dataRef");
    ioOut << m_dataRef;
    ioOut.TagSet("hostDataRef");
    ioOut << m_hostDataRef;
    ioOut.TagSet("rubyLogic");
    ioOut << m_rubyLogic;
}
//%outOfLineFunctions } BkdQLiheBSdL7u0BwAwbNQ
