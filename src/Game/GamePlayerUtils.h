/*
 * $Id$
 * $Log$
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
    static void SendControl(const GameDefClient& inClient, const GamePiecePlayer& inPlayer, const GameTimer& inTimer, U32 inNumFrames);
    static void SendControlQueues(const GameTimer& inTimer, U32 inNumFrames);
    static bool VerifyOrCreateImagePlayer(const string& inName, GameDefClient& inClientDef);
    static bool VerifyPlayer(const string& inName, GamePiecePlayer& inPlayer);
    static bool VerifyOrCreateLocalPlayer(const string& inName, GameDefClient& inClientDef);
    static void ManagePlayers(GameAppHandler& inAppHandler);
};
