//%includeGuardStart {
#ifndef INFERNALPLAYERUTILS_H
#define INFERNALPLAYERUTILS_H
//%includeGuardStart } 3zHHkYCcKZRXNO64ZAPAAQ
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalPlayerUtils.h
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
//%Header } WAFWY0XXN1RFNXZo45Ptyg
/*
 * $Id: InfernalPlayerUtils.h,v 1.7 2006/06/01 15:39:05 southa Exp $
 * $Log: InfernalPlayerUtils.h,v $
 * Revision 1.7  2006/06/01 15:39:05  southa
 * DrawArray verification and fixes
 *
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
