/*
 * $Id: GamePlayerUtils.h,v 1.1 2002/12/05 13:20:12 southa Exp $
 * $Log: GamePlayerUtils.h,v $
 * Revision 1.1  2002/12/05 13:20:12  southa
 * Client link handling
 *
 */

#include "mushCore.h"

class GameAppHandler;
class GameDefClient;
class GamePiecePlayer;
class GameTimer;

class GamePlayerUtils
{
public:
    static void FillControlQueues(const GameTimer& inTimer, U32 inNumFrames);
    static void SendControl(GameDefClient& inClient, const GamePiecePlayer& inPlayer, const GameTimer& inTimer, U32 inNumFrames);
    static void SendControlQueues(const GameTimer& inTimer, U32 inNumFrames);
    static bool VerifyOrCreateImagePlayer(const string& inName, GameDefClient& inClientDef);
    static bool VerifyPlayer(const string& inName, GamePiecePlayer& inPlayer);
    static bool VerifyOrCreateLocalPlayer(const string& inName, GameDefClient& inClientDef);
    static void ManagePlayers(GameAppHandler& inAppHandler);
};
