//%includeGuardStart {
#ifndef GAMEPLAYERUTILS_H
#define GAMEPLAYERUTILS_H
//%includeGuardStart } u/cKd4KD2FACTxMGfkaE/g
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GamePlayerUtils.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 9drEiigj4IJrzoCcFHHBBA
/*
 * $Id: GamePlayerUtils.h,v 1.7 2003/08/21 23:08:52 southa Exp $
 * $Log: GamePlayerUtils.h,v $
 * Revision 1.7  2003/08/21 23:08:52  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.5  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/10 20:38:05  southa
 * Server timing
 *
 * Revision 1.2  2002/12/06 11:11:16  southa
 * Send control information
 *
 * Revision 1.1  2002/12/05 13:20:12  southa
 * Client link handling
 *
 */

#include "Mushcore.h"

class GameAppHandler;
class GameDefClient;
class GameFloorMap;
class GamePiecePlayer;
class GameTimer;

class GamePlayerUtils
{
public:
    static void FillControlQueues(const GameTimer& inTimer, Mushware::U32 inNumFrames);
    static void SendControl(GameDefClient& inClient, const GamePiecePlayer& inPlayer, const GameTimer& inTimer, Mushware::U32 inNumFrames);
    static void SendControlQueues(const GameTimer& inTimer, Mushware::U32 inNumFrames);
    static bool VerifyOrCreateImagePlayer(const std::string& inName, GameDefClient& inClientDef);
    static bool VerifyPlayer(const std::string& inName, GamePiecePlayer& inPlayer);
    static bool VerifyOrCreateLocalPlayer(const std::string& inName, GameDefClient& inClientDef);
    static void ManagePlayers(GameAppHandler& inAppHandler);
    static void ClientMove(GameFloorMap& inFloorMap, GameTimer& inTimer, Mushware::U32 inNumFrames);
    static void ServerMove(GameFloorMap& inFloorMap, GameTimer& inTimer, Mushware::U32 inNumFrames);
    static Mushware::U32 CompleteControlFrameFind(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
