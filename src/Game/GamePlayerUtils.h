#ifndef GAMEPLAYERUTILS_H
#define GAMEPLAYERUTILS_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GamePlayerUtils.h,v 1.3 2002/12/10 20:38:05 southa Exp $
 * $Log: GamePlayerUtils.h,v $
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

#include "mushCore.h"

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
    static bool VerifyOrCreateImagePlayer(const string& inName, GameDefClient& inClientDef);
    static bool VerifyPlayer(const string& inName, GamePiecePlayer& inPlayer);
    static bool VerifyOrCreateLocalPlayer(const string& inName, GameDefClient& inClientDef);
    static void ManagePlayers(GameAppHandler& inAppHandler);
    static void ClientMove(GameFloorMap& inFloorMap, GameTimer& inTimer, Mushware::U32 inNumFrames);
    static void ServerMove(GameFloorMap& inFloorMap, GameTimer& inTimer, Mushware::U32 inNumFrames);
    static Mushware::U32 CompleteControlFrameFind(void);
};
#endif
