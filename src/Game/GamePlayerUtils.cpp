//%Header {
/*****************************************************************************
 *
 * File: src/Game/GamePlayerUtils.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } IyS+FJVMZImMJW69Nn1WCw
/*
 * $Id: GamePlayerUtils.cpp,v 1.16 2003/09/17 19:40:33 southa Exp $
 * $Log: GamePlayerUtils.cpp,v $
 * Revision 1.16  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.15  2003/08/21 23:08:51  southa
 * Fixed file headers
 *
 * Revision 1.14  2003/01/20 10:45:27  southa
 * Singleton tidying
 *
 * Revision 1.13  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.12  2003/01/12 17:32:55  southa
 * Mushcore work
 *
 * Revision 1.11  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.10  2003/01/07 17:13:43  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.9  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.8  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/12/12 14:00:40  southa
 * Created Mustl
 *
 * Revision 1.6  2002/12/10 20:38:05  southa
 * Server timing
 *
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
#include "InfernalData.h"
#include "GameDefClient.h"
#include "GameDefServer.h"
#include "GameEvent.h"
#include "InfernalFloorMap.h"
#include "InfernalMessageControlData.h"
#include "GamePiecePlayer.h"
#include "GameProtocol.h"
#include "GameSTL.h"
#include "InfernalTimer.h"
#include "GameType.h"

using namespace Mushware;
using namespace std;

void
GamePlayerUtils::FillControlQueues(const InfernalTimer& inTimer, U32 inNumFrames)
{
    InfernalTimer::tMsec frameInterval = inTimer.ConstClientGet().FrameIntervalMsecGet(); // Msec between motion frames
    InfernalTimer::tMsec currentMsec = inTimer.CurrentMsecGet(); // Current Msec
                                                            // Msec of the frame immediately before our first one
    InfernalTimer::tMsec previousFrameMsec = currentMsec - frameInterval * inNumFrames;
    // Frame number of the first frame in this sequence
    U32 startFrame = inTimer.ConstClientGet().FrameNumGet();

    GameController *localController = InfernalData::Sgl().ControllerGet("controller1");

    MushcoreData<GamePiecePlayer>::tMapIterator endValue=InfernalData::Sgl().PlayerGet().End();

    for (MushcoreData<GamePiecePlayer>::tMapIterator p=InfernalData::Sgl().PlayerGet().Begin();
         p != endValue; ++p)
    {
        MUSHCOREASSERT(p->second != NULL);
        GamePiecePlayer& playerRef = *p->second;
        if (playerRef.ImageIs())
        {
            // Image players have no contol queue
        }
        else if (localController != NULL)
        {
            InfernalTimer::tMsec frameMsec = previousFrameMsec; // Msec of frame we're working on
            for (U32 i=0; i<inNumFrames; ++i)
            {
                frameMsec += frameInterval;
                GameControlFrameDef frameDef;
                localController->StateGet(frameDef, static_cast<U32>(frameMsec)); // Not sure about that cast
                playerRef.ControlFrameDefAdd(frameDef, startFrame+i);
            }
        }
    }
}

void
GamePlayerUtils::SendControl(GameDefClient& inClient, const GamePiecePlayer& inPlayer, const InfernalTimer& inTimer, U32 inNumFrames)
{
    InfernalMessageControlData controlMessage;
    // frameNum is the first frame number in the chunk we're going to send
    U32 startFrameNum = inTimer.ConstClientGet().FrameNumGet();
    controlMessage.StartFrameSet(startFrameNum);
    
    MushcoreHistoryIterator<U32, GameControlFrameDef> p = inPlayer.ControlFrameDefIteratorGet(startFrameNum);
    U32 entryCtr=0;
    while (p.ValidIs())
    {
        U32 entryFrameNum=p.IndexGet();

        S32 frameOffset = entryFrameNum - startFrameNum;
        if (frameOffset >= 0 && frameOffset < 256)
        {
            controlMessage.DataEntryPush(frameOffset, p.StoreGet());
            if (++entryCtr >= InfernalMessageControlData::kEntryLimit) break;
        }
        p.ForwardMove();
    }
    
    MustlData netData;
    controlMessage.Pack(netData);
    //cerr << "Would send " << netData << endl;
    inClient.FastSendToServer(netData);
}

void
GamePlayerUtils::SendControlQueues(const InfernalTimer& inTimer, U32 inNumFrames)
{
    MushcoreData<GameDefClient>::tMapIterator endValue = MushcoreData<GameDefClient>::Sgl().End();

    for (MushcoreData<GameDefClient>::tMapIterator p=MushcoreData<GameDefClient>::Sgl().Begin(); p != endValue; ++p)
    {
        if (!p->second->ImageIs())
        {
            MUSHCOREASSERT(p->second != NULL);
            GamePiecePlayer *playerPtr;
            // Needs optimised lookup
            if (InfernalData::Sgl().PlayerGet().GetIfExists(playerPtr, p->first))
            {
                MUSHCOREASSERT(playerPtr != NULL);
                SendControl(*p->second, *playerPtr, inTimer, inNumFrames);
            }
        }
    }
}

bool
GamePlayerUtils::VerifyOrCreateImagePlayer(const string& inName, GameDefClient& inClientDef)
{
    bool retVal=true;
    MushcoreData<GamePiecePlayer>& playerData = InfernalData::Sgl().PlayerGet();

    if (!playerData.Exists(inName))
    {
        retVal = false;
        const GamePiecePlayer *templatePlayer=dynamic_cast<const GamePiecePlayer *>(InfernalData::Sgl().TemplateGet("player1"));
        MUSHCOREASSERT(templatePlayer != NULL);
        GamePiecePlayer *newPlayer = playerData.Give(inName, new GamePiecePlayer(*templatePlayer));
        MUSHCOREASSERT(newPlayer != NULL);
        newPlayer->ImageIsSet(inClientDef.ImageIs());
    }
    return retVal;
}

bool
GamePlayerUtils::VerifyPlayer(const string& inName, GamePiecePlayer& inPlayer)
{
    bool retVal = false;
    GameDefClient *defClient = NULL;
    if (MushcoreData<GameDefClient>::Sgl().GetIfExists(defClient, inName))
    {
        MUSHCOREASSERT(defClient != NULL);
        retVal = true;
    }
    return retVal;
}

bool
GamePlayerUtils::VerifyOrCreateLocalPlayer(const string& inName, GameDefClient& inClientDef)
{
    bool retVal=true;
    MushcoreData<GamePiecePlayer>& playerData = InfernalData::Sgl().PlayerGet();

    if (!playerData.Exists(inName))
    {
        retVal = false;
        const GamePiecePlayer *templatePlayer=dynamic_cast<const GamePiecePlayer *>(InfernalData::Sgl().TemplateGet("player1"));
        MUSHCOREASSERT(templatePlayer != NULL);
        GamePiecePlayer *newPlayer = playerData.Give(inName, new GamePiecePlayer(*templatePlayer));
        MUSHCOREASSERT(newPlayer != NULL);
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
        MushcoreData<GameDefClient>::tMapIterator endValue=MushcoreData<GameDefClient>::Sgl().End();

        for (MushcoreData<GameDefClient>::tMapIterator p=MushcoreData<GameDefClient>::Sgl().Begin(); p != endValue; ++p)
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
        MushcoreData<GamePiecePlayer>::tMapIterator endValue = InfernalData::Sgl().PlayerGet().End();
        MushcoreData<GamePiecePlayer>::tMapIterator killValue = endValue;

        for (MushcoreData<GamePiecePlayer>::tMapIterator p=InfernalData::Sgl().PlayerGet().Begin(); p != endValue; ++p)
        {
            if (!VerifyPlayer(p->first, *p->second))
            {
                killValue = p;
                break;
            }
        }
        if (killValue != endValue)
        {
            InfernalData::Sgl().PlayerGet().Delete(killValue);
        }
    }

    // Check for non-image clients on this machine
    MushcoreData<GameDefClient>::tMapIterator endValue=MushcoreData<GameDefClient>::Sgl().End();

    for (MushcoreData<GameDefClient>::tMapIterator p=MushcoreData<GameDefClient>::Sgl().Begin(); p != endValue; ++p)
    {
        if (!p->second->ImageIs())
        {
            VerifyOrCreateLocalPlayer(p->first, *p->second);
        }
    }
}

void
GamePlayerUtils::ClientMove(InfernalFloorMap& inFloorMap, InfernalTimer& inTimer, U32 inNumFrames)
{
    U32 startFrameNum = inTimer.ClientGet().FrameNumGet();

    MushcoreData<GamePiecePlayer>::tMapIterator endValue=InfernalData::Sgl().PlayerGet().End();

    for (U32 i=0; i<inNumFrames; ++i)
    {
        U32 frameNum = startFrameNum + i; // Add control delay here

        for (MushcoreData<GamePiecePlayer>::tMapIterator p=InfernalData::Sgl().PlayerGet().Begin();
             p != endValue; ++p)
        {
            GamePiecePlayer& playerRef=*p->second;

            if (!playerRef.ImageIs())
            {
                playerRef.EnvironmentRead(inFloorMap);
                GameEventStandingOn standingOn(playerRef.StandingOnGet()); // Maybe
    
                InfernalData::Sgl().TypeGet().EventHandler(standingOn); // Maybe
    
                const GameControlFrameDef *frameDef = NULL;
                if (playerRef.ControlFrameDefGet(frameDef, frameNum))
                {
                    MUSHCOREASSERT(frameDef != NULL);
    
                    InfernalMotionSpec motion;
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
GamePlayerUtils::ServerMove(InfernalFloorMap& inFloorMap, InfernalTimer& inTimer, U32 inNumFrames)
{
    U32 startFrameNum = inTimer.ServerGet().FrameNumGet();

    MushcoreData<GamePiecePlayer>::tMapIterator endValue=InfernalData::Sgl().PlayerGet().End();

    for (U32 i=0; i<inNumFrames; ++i)
    {
        U32 frameNum = startFrameNum + i; // Add control delay here

        for (MushcoreData<GamePiecePlayer>::tMapIterator p=InfernalData::Sgl().PlayerGet().Begin();
             p != endValue; ++p)
        {
            GamePiecePlayer& playerRef=*p->second;

            if (playerRef.ImageIs())
            {
                playerRef.EnvironmentRead(inFloorMap);
                GameEventStandingOn standingOn(playerRef.StandingOnGet());

                InfernalData::Sgl().TypeGet().EventHandler(standingOn);

                const GameControlFrameDef *frameDef = NULL;
                if (playerRef.ControlFrameDefGet(frameDef, frameNum))
                {
                    MUSHCOREASSERT(frameDef != NULL);

                    InfernalMotionSpec motion;
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

    MushcoreData<GamePiecePlayer>::tMapIterator endValue=InfernalData::Sgl().PlayerGet().End();
        
    for (MushcoreData<GamePiecePlayer>::tMapIterator p=InfernalData::Sgl().PlayerGet().Begin();
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
