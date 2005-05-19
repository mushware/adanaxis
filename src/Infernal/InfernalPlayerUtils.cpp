//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalPlayerUtils.cpp
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
//%Header } Yyqqeo2NoZVMmsAoU7DRDA
/*
 * $Id: InfernalPlayerUtils.cpp,v 1.5 2004/01/02 21:13:09 southa Exp $
 * $Log: InfernalPlayerUtils.cpp,v $
 * Revision 1.5  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.4  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
 * Revision 1.3  2003/10/06 22:23:45  southa
 * Game to GameMustl move
 *
 * Revision 1.2  2003/10/04 15:32:11  southa
 * Module split
 *
 * Revision 1.17  2003/10/04 12:23:02  southa
 * File renaming
 *
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

#include "InfernalPlayerUtils.h"

#include "InfernalData.h"
#include "InfernalEvent.h"
#include "InfernalFloorMap.h"
#include "InfernalMessageControlData.h"
#include "InfernalPiecePlayer.h"
#include "InfernalSTL.h"

#include "mushGame.h"
#include "mushMustlGame.h"

using namespace Mushware;
using namespace std;

void
InfernalPlayerUtils::FillControlQueues(const GameTimer& inTimer, U32 inNumFrames)
{
    GameTimer::tMsec frameInterval = inTimer.ConstClientGet().FrameIntervalMsecGet(); // Msec between motion frames
    GameTimer::tMsec currentMsec = inTimer.CurrentMsecGet(); // Current Msec
                                                            // Msec of the frame immediately before our first one
    GameTimer::tMsec previousFrameMsec = currentMsec - frameInterval * inNumFrames;
    // Frame number of the first frame in this sequence
    U32 startFrame = inTimer.ConstClientGet().FrameNumGet();

    GameController *localController = InfernalData::Sgl().ControllerGet("controller1");

    MushcoreData<InfernalPiecePlayer>::tMapIterator endValue=InfernalData::Sgl().PlayerGet().End();

    for (MushcoreData<InfernalPiecePlayer>::tMapIterator p=InfernalData::Sgl().PlayerGet().Begin();
         p != endValue; ++p)
    {
        MUSHCOREASSERT(p->second != NULL);
        InfernalPiecePlayer& playerRef = *p->second;
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
                localController->StateGet(frameDef, static_cast<U32>(frameMsec)); // Not sure about that cast
                playerRef.ControlFrameDefAdd(frameDef, startFrame+i);
            }
        }
    }
}

void
InfernalPlayerUtils::SendControl(MustlGameClient& inClient, const InfernalPiecePlayer& inPlayer, const GameTimer& inTimer, U32 inNumFrames)
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
InfernalPlayerUtils::SendControlQueues(const GameTimer& inTimer, U32 inNumFrames)
{
    MushcoreData<MustlGameClient>::tMapIterator endValue = MushcoreData<MustlGameClient>::Sgl().End();

    for (MushcoreData<MustlGameClient>::tMapIterator p=MushcoreData<MustlGameClient>::Sgl().Begin(); p != endValue; ++p)
    {
        if (!p->second->ImageIs())
        {
            MUSHCOREASSERT(p->second != NULL);
            InfernalPiecePlayer *playerPtr;
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
InfernalPlayerUtils::VerifyOrCreateImagePlayer(const string& inName, MustlGameClient& inClientDef)
{
    bool retVal=true;
    MushcoreData<InfernalPiecePlayer>& playerData = InfernalData::Sgl().PlayerGet();

    if (!playerData.Exists(inName))
    {
        retVal = false;
        const InfernalPiecePlayer *templatePlayer=dynamic_cast<const InfernalPiecePlayer *>(InfernalData::Sgl().TemplateGet("player1"));
        MUSHCOREASSERT(templatePlayer != NULL);
        InfernalPiecePlayer *newPlayer = playerData.Give(inName, new InfernalPiecePlayer(*templatePlayer));
        MUSHCOREASSERT(newPlayer != NULL);
        newPlayer->ImageIsSet(inClientDef.ImageIs());
    }
    return retVal;
}

bool
InfernalPlayerUtils::VerifyPlayer(const string& inName, InfernalPiecePlayer& inPlayer)
{
    bool retVal = false;
    MustlGameClient *defClient = NULL;
    if (MushcoreData<MustlGameClient>::Sgl().GetIfExists(defClient, inName))
    {
        MUSHCOREASSERT(defClient != NULL);
        retVal = true;
    }
    return retVal;
}

bool
InfernalPlayerUtils::VerifyOrCreateLocalPlayer(const string& inName, MustlGameClient& inClientDef)
{
    bool retVal=true;
    MushcoreData<InfernalPiecePlayer>& playerData = InfernalData::Sgl().PlayerGet();

    if (!playerData.Exists(inName))
    {
        retVal = false;
        const InfernalPiecePlayer *templatePlayer=dynamic_cast<const InfernalPiecePlayer *>(InfernalData::Sgl().TemplateGet("player1"));
        MUSHCOREASSERT(templatePlayer != NULL);
        InfernalPiecePlayer *newPlayer = playerData.Give(inName, new InfernalPiecePlayer(*templatePlayer));
        MUSHCOREASSERT(newPlayer != NULL);
    }
    return retVal;
}

void
InfernalPlayerUtils::ManagePlayers(GameAppHandler& inAppHandler)
{
    // Called for multiplayer games only

    if (inAppHandler.ServerPresent())
    {
        // Loop through the client images, checking that each one has a player attached to it
        MushcoreData<MustlGameClient>::tMapIterator endValue=MushcoreData<MustlGameClient>::Sgl().End();

        for (MushcoreData<MustlGameClient>::tMapIterator p=MushcoreData<MustlGameClient>::Sgl().Begin(); p != endValue; ++p)
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
        MushcoreData<InfernalPiecePlayer>::tMapIterator endValue = InfernalData::Sgl().PlayerGet().End();
        MushcoreData<InfernalPiecePlayer>::tMapIterator killValue = endValue;

        for (MushcoreData<InfernalPiecePlayer>::tMapIterator p=InfernalData::Sgl().PlayerGet().Begin(); p != endValue; ++p)
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
    MushcoreData<MustlGameClient>::tMapIterator endValue=MushcoreData<MustlGameClient>::Sgl().End();

    for (MushcoreData<MustlGameClient>::tMapIterator p=MushcoreData<MustlGameClient>::Sgl().Begin(); p != endValue; ++p)
    {
        if (!p->second->ImageIs())
        {
            VerifyOrCreateLocalPlayer(p->first, *p->second);
        }
    }
}

void
InfernalPlayerUtils::ClientMove(InfernalFloorMap& inFloorMap, GameTimer& inTimer, U32 inNumFrames)
{
    U32 startFrameNum = inTimer.ClientGet().FrameNumGet();

    MushcoreData<InfernalPiecePlayer>::tMapIterator endValue=InfernalData::Sgl().PlayerGet().End();

    for (U32 i=0; i<inNumFrames; ++i)
    {
        U32 frameNum = startFrameNum + i; // Add control delay here

        for (MushcoreData<InfernalPiecePlayer>::tMapIterator p=InfernalData::Sgl().PlayerGet().Begin();
             p != endValue; ++p)
        {
            InfernalPiecePlayer& playerRef=*p->second;

            if (!playerRef.ImageIs())
            {
                playerRef.EnvironmentRead(inFloorMap);
                InfernalEventStandingOn standingOn(playerRef.StandingOnGet()); // Maybe
    
                MushcoreAbstractSingleton<GameType>::Sgl().EventHandler(standingOn); // Maybe
    
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
InfernalPlayerUtils::ServerMove(InfernalFloorMap& inFloorMap, GameTimer& inTimer, U32 inNumFrames)
{
    U32 startFrameNum = inTimer.ServerGet().FrameNumGet();

    MushcoreData<InfernalPiecePlayer>::tMapIterator endValue=InfernalData::Sgl().PlayerGet().End();

    for (U32 i=0; i<inNumFrames; ++i)
    {
        U32 frameNum = startFrameNum + i; // Add control delay here

        for (MushcoreData<InfernalPiecePlayer>::tMapIterator p=InfernalData::Sgl().PlayerGet().Begin();
             p != endValue; ++p)
        {
            InfernalPiecePlayer& playerRef=*p->second;

            if (playerRef.ImageIs())
            {
                playerRef.EnvironmentRead(inFloorMap);
                InfernalEventStandingOn standingOn(playerRef.StandingOnGet());

                MushcoreAbstractSingleton<GameType>::Sgl().EventHandler(standingOn);

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
InfernalPlayerUtils::CompleteControlFrameFind(void)
{
    U32 retFrame=0;

    MushcoreData<InfernalPiecePlayer>::tMapIterator endValue=InfernalData::Sgl().PlayerGet().End();
        
    for (MushcoreData<InfernalPiecePlayer>::tMapIterator p=InfernalData::Sgl().PlayerGet().Begin();
         p != endValue; ++p)
    {
        InfernalPiecePlayer& playerRef=*p->second;
        if (playerRef.ImageIs())
        {
            U32 lastFrame = playerRef.LastValidControlFrameGet();
            if (lastFrame > retFrame) retFrame = lastFrame;
        }
    }
    return retFrame;
}
