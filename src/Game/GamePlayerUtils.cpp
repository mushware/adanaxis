/*
 * $Id: GamePlayerUtils.cpp,v 1.5 2002/12/10 19:00:17 southa Exp $
 * $Log: GamePlayerUtils.cpp,v $
 * Revision 1.5  2002/12/10 19:00:17  southa
 * Split timer into client and server
 *
 * Revision 1.4  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.3  2002/12/06 17:38:00  southa
 * ControlData message unpacking
 *
 * Revision 1.2  2002/12/06 11:11:16  southa
 * Send control information
 *
 * Revision 1.1  2002/12/05 13:20:12  southa
 * Client link handling
 *
 */

#include "GamePlayerUtils.h"

#include "GameAppHandler.h"
#include "GameController.h"
#include "GameData.h"
#include "GameDefClient.h"
#include "GameDefServer.h"
#include "GameEvent.h"
#include "GameFloorMap.h"
#include "GameMessageControlData.h"
#include "GamePiecePlayer.h"
#include "GameProtocol.h"
#include "GameTimer.h"
#include "GameType.h"

void
GamePlayerUtils::FillControlQueues(const GameTimer& inTimer, U32 inNumFrames)
{
    GameTimer::tMsec frameInterval = inTimer.ConstClientGet().FrameIntervalMsecGet(); // Msec between motion frames
    GameTimer::tMsec currentMsec = inTimer.CurrentMsecGet(); // Current Msec
                                                            // Msec of the frame immediately before our first one
    GameTimer::tMsec previousFrameMsec = currentMsec - frameInterval * inNumFrames;
    // Frame number of the first frame in this sequence
    U32 startFrame = inTimer.ConstClientGet().FrameNumGet();

    GameController *localController = GameData::Instance().ControllerGet("controller1");

    CoreData<GamePiecePlayer>::tMapIterator endValue=GameData::Instance().PlayerGet().End();

    for (CoreData<GamePiecePlayer>::tMapIterator p=GameData::Instance().PlayerGet().Begin();
         p != endValue; ++p)
    {
        COREASSERT(p->second != NULL);
        GamePiecePlayer& playerRef = *p->second;
        if (playerRef.ImageIs())
        {
            // Image players have no contol queue
        }
        else if (localController != NULL)
        {
            GameTimer::tMsec frameMsec = previousFrameMsec; // Msec of frame we're working on
            for (U32 i=0; i<inNumFrames; ++i)
            {
                frameMsec += frameInterval;
                GameControlFrameDef frameDef;
                localController->StateGet(frameDef, frameMsec);
                playerRef.ControlFrameDefAdd(frameDef, startFrame+i);
            }
        }
    }
}

void
GamePlayerUtils::SendControl(GameDefClient& inClient, const GamePiecePlayer& inPlayer, const GameTimer& inTimer, U32 inNumFrames)
{
    GameMessageControlData controlMessage;
    // frameNum is the first frame number in the chunk we're going to send
    U32 startFrameNum = inTimer.ConstClientGet().FrameNumGet();
    controlMessage.StartFrameSet(startFrameNum);
    
    CoreHistoryIterator<U32, GameControlFrameDef> p = inPlayer.ControlFrameDefIteratorGet(startFrameNum);
    U32 entryCtr=0;
    while (p.ValidIs())
    {
        U32 entryFrameNum=p.IndexGet();

        S32 frameOffset = entryFrameNum - startFrameNum;
        if (frameOffset >= 0 && frameOffset < 256)
        {
            controlMessage.DataEntryPush(frameOffset, p.StoreGet());
            if (++entryCtr >= GameMessageControlData::kEntryLimit) break;
        }
        p.ForwardMove();
    }
    
    MediaNetData netData;
    controlMessage.Pack(netData);
    //cerr << "Would send " << netData << endl;
    inClient.FastSendToServer(netData);
}

void
GamePlayerUtils::SendControlQueues(const GameTimer& inTimer, U32 inNumFrames)
{
    CoreData<GameDefClient>::tMapIterator endValue = CoreData<GameDefClient>::Instance().End();

    for (CoreData<GameDefClient>::tMapIterator p=CoreData<GameDefClient>::Instance().Begin(); p != endValue; ++p)
    {
        if (!p->second->ImageIs())
        {
            COREASSERT(p->second != NULL);
            GamePiecePlayer *playerPtr;
            // Needs optimised lookup
            if (GameData::Instance().PlayerGet().GetIfExists(playerPtr, p->first))
            {
                COREASSERT(playerPtr != NULL);
                SendControl(*p->second, *playerPtr, inTimer, inNumFrames);
            }
        }
    }
}

bool
GamePlayerUtils::VerifyOrCreateImagePlayer(const string& inName, GameDefClient& inClientDef)
{
    bool retVal=true;
    CoreData<GamePiecePlayer>& playerData = GameData::Instance().PlayerGet();

    if (!playerData.Exists(inName))
    {
        retVal = false;
        const GamePiecePlayer *templatePlayer=dynamic_cast<const GamePiecePlayer *>(GameData::Instance().TemplateGet("player1"));
        COREASSERT(templatePlayer != NULL);
        GamePiecePlayer *newPlayer = playerData.Give(inName, new GamePiecePlayer(*templatePlayer));
        COREASSERT(newPlayer != NULL);
        newPlayer->ImageIsSet(inClientDef.ImageIs());
    }
    return retVal;
}

bool
GamePlayerUtils::VerifyPlayer(const string& inName, GamePiecePlayer& inPlayer)
{
    bool retVal = false;
    GameDefClient *defClient = NULL;
    if (CoreData<GameDefClient>::Instance().GetIfExists(defClient, inName))
    {
        COREASSERT(defClient != NULL);
        retVal = true;
    }
    return retVal;
}

bool
GamePlayerUtils::VerifyOrCreateLocalPlayer(const string& inName, GameDefClient& inClientDef)
{
    bool retVal=true;
    CoreData<GamePiecePlayer>& playerData = GameData::Instance().PlayerGet();

    if (!playerData.Exists(inName))
    {
        retVal = false;
        const GamePiecePlayer *templatePlayer=dynamic_cast<const GamePiecePlayer *>(GameData::Instance().TemplateGet("player1"));
        COREASSERT(templatePlayer != NULL);
        GamePiecePlayer *newPlayer = playerData.Give(inName, new GamePiecePlayer(*templatePlayer));
        COREASSERT(newPlayer != NULL);
    }
    return retVal;
}

void
GamePlayerUtils::ManagePlayers(GameAppHandler& inAppHandler)
{
    // Called for multiplayer games only

    if (inAppHandler.ServerPresent())
    {
        // Loop through the client images, checking that each one has a player attached to it
        CoreData<GameDefClient>::tMapIterator endValue=CoreData<GameDefClient>::Instance().End();

        for (CoreData<GameDefClient>::tMapIterator p=CoreData<GameDefClient>::Instance().Begin(); p != endValue; ++p)
        {
            if (p->second->ImageIs())
            {
                VerifyOrCreateImagePlayer(p->first, *p->second);
            }
        }
    }

    if (inAppHandler.ServerPresent())
    {
        // Loop through the players, checking that each one has an image
        CoreData<GamePiecePlayer>::tMapIterator endValue = GameData::Instance().PlayerGet().End();
        CoreData<GamePiecePlayer>::tMapIterator killValue = endValue;

        for (CoreData<GamePiecePlayer>::tMapIterator p=GameData::Instance().PlayerGet().Begin(); p != endValue; ++p)
        {
            if (!VerifyPlayer(p->first, *p->second))
            {
                killValue = p;
                break;
            }
        }
        if (killValue != endValue)
        {
            GameData::Instance().PlayerGet().Delete(killValue);
        }
    }

    // Check for non-image clients on this machine
    CoreData<GameDefClient>::tMapIterator endValue=CoreData<GameDefClient>::Instance().End();

    for (CoreData<GameDefClient>::tMapIterator p=CoreData<GameDefClient>::Instance().Begin(); p != endValue; ++p)
    {
        if (!p->second->ImageIs())
        {
            VerifyOrCreateLocalPlayer(p->first, *p->second);
        }
    }
}

void
GamePlayerUtils::ClientMove(GameFloorMap& inFloorMap, GameTimer& inTimer, U32 inNumFrames)
{
    U32 startFrameNum = inTimer.ClientGet().FrameNumGet();

    CoreData<GamePiecePlayer>::tMapIterator endValue=GameData::Instance().PlayerGet().End();

    for (U32 i=0; i<inNumFrames; ++i)
    {
        U32 frameNum = startFrameNum + i; // Add control delay here

        for (CoreData<GamePiecePlayer>::tMapIterator p=GameData::Instance().PlayerGet().Begin();
             p != endValue; ++p)
        {
            GamePiecePlayer& playerRef=*p->second;

            if (!playerRef.ImageIs())
            {
                playerRef.EnvironmentRead(inFloorMap);
                GameEventStandingOn standingOn(playerRef.StandingOnGet()); // Maybe
    
                GameData::Instance().TypeGet().EventHandler(standingOn); // Maybe
    
                const GameControlFrameDef *frameDef = NULL;
                if (playerRef.ControlFrameDefGet(frameDef, frameNum))
                {
                    COREASSERT(frameDef != NULL);
    
                    GameMotionSpec motion;
                    playerRef.MoveGet(motion, *frameDef);
    #if 0
                    if (m_renderDiagnostics == kDiagnosticCollision)
                    {
                        GLState::DepthSet(GLState::kDepthNone);
                        GLState::ModulationSet(GLState::kModulationColour);
                        GLState::BlendSet(GLState::kBlendLine);
                        m_floorMap->SolidMapGet().OverPlotCollisionSet(motion);
                    }
    #endif
                    inFloorMap.SolidMapGet().TrimMotion(motion);
                    playerRef.MoveConfirm(motion);
    #if 0
                    if (m_renderDiagnostics == kDiagnosticCollision)
                    {
                        motion.Render();
                    }
    #endif
                }
            }
        }
    }    
}

void
GamePlayerUtils::ServerMove(GameFloorMap& inFloorMap, GameTimer& inTimer, U32 inNumFrames)
{
    U32 startFrameNum = inTimer.ServerGet().FrameNumGet();

    CoreData<GamePiecePlayer>::tMapIterator endValue=GameData::Instance().PlayerGet().End();

    for (U32 i=0; i<inNumFrames; ++i)
    {
        U32 frameNum = startFrameNum + i; // Add control delay here

        for (CoreData<GamePiecePlayer>::tMapIterator p=GameData::Instance().PlayerGet().Begin();
             p != endValue; ++p)
        {
            GamePiecePlayer& playerRef=*p->second;

            if (playerRef.ImageIs())
            {
                playerRef.EnvironmentRead(inFloorMap);
                GameEventStandingOn standingOn(playerRef.StandingOnGet());

                GameData::Instance().TypeGet().EventHandler(standingOn);

                const GameControlFrameDef *frameDef = NULL;
                if (playerRef.ControlFrameDefGet(frameDef, frameNum))
                {
                    COREASSERT(frameDef != NULL);

                    GameMotionSpec motion;
                    playerRef.MoveGet(motion, *frameDef);
#if 0
                    if (m_renderDiagnostics == kDiagnosticCollision)
                    {
                        GLState::DepthSet(GLState::kDepthNone);
                        GLState::ModulationSet(GLState::kModulationColour);
                        GLState::BlendSet(GLState::kBlendLine);
                        inFloorMap.SolidMapGet().OverPlotCollisionSet(motion);
                    }
#endif
                    inFloorMap.SolidMapGet().TrimMotion(motion);
                    playerRef.MoveConfirm(motion);
#if 0
                    if (m_renderDiagnostics == kDiagnosticCollision)
                    {
                        motion.Render();
                    }
#endif
                }
            }
        }
    }
}

U32
GamePlayerUtils::CompleteControlFrameFind(void)
{
    U32 retFrame=0;

    CoreData<GamePiecePlayer>::tMapIterator endValue=GameData::Instance().PlayerGet().End();
        
    for (CoreData<GamePiecePlayer>::tMapIterator p=GameData::Instance().PlayerGet().Begin();
         p != endValue; ++p)
    {
        GamePiecePlayer& playerRef=*p->second;
        if (playerRef.ImageIs())
        {
            U32 lastFrame = playerRef.LastValidControlFrameGet();
            if (lastFrame > retFrame) retFrame = lastFrame;
        }
    }
    return retFrame;
}
