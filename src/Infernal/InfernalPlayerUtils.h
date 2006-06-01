//%includeGuardStart {
#ifndef INFERNALPLAYERUTILS_H
#define INFERNALPLAYERUTILS_H
//%includeGuardStart } 3zHHkYCcKZRXNO64ZAPAAQ
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalPlayerUtils.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } OZnOIZyya8ZZqTzAe5m3VQ
/*
 * $Id: InfernalPlayerUtils.h,v 1.6 2005/05/19 13:02:05 southa Exp $
 * $Log: InfernalPlayerUtils.h,v $
 * Revision 1.6  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.4  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.3  2003/10/06 22:23:45  southa
 * Game to GameMustl move
 *
 * Revision 1.2  2003/10/04 15:32:11  southa
 * Module split
 *
 * Revision 1.1  2003/10/04 12:44:36  southa
 * File renaming
 *
 * Revision 1.9  2003/10/04 12:23:02  southa
 * File renaming
 *
 * Revision 1.8  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
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

#include "mushMushcore.h"

class GameAppHandler;
class MustlGameClient;
class InfernalFloorMap;
class InfernalPiecePlayer;
class GameTimer;

class InfernalPlayerUtils
{
public:
    static void FillControlQueues(const GameTimer& inTimer, Mushware::U32 inNumFrames);
    static void SendControl(MustlGameClient& inClient, const InfernalPiecePlayer& inPlayer, const GameTimer& inTimer, Mushware::U32 inNumFrames);
    static void SendControlQueues(const GameTimer& inTimer, Mushware::U32 inNumFrames);
    static bool VerifyOrCreateImagePlayer(const std::string& inName, MustlGameClient& inClientDef);
    static bool VerifyPlayer(const std::string& inName, InfernalPiecePlayer& inPlayer);
    static bool VerifyOrCreateLocalPlayer(const std::string& inName, MustlGameClient& inClientDef);
    static void ManagePlayers(GameAppHandler& inAppHandler);
    static void ClientMove(InfernalFloorMap& inFloorMap, GameTimer& inTimer, Mushware::U32 inNumFrames);
    static void ServerMove(InfernalFloorMap& inFloorMap, GameTimer& inTimer, Mushware::U32 inNumFrames);
    static Mushware::U32 CompleteControlFrameFind(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
