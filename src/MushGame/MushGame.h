//%includeGuardStart {
#ifndef MUSHGAME_H
#define MUSHGAME_H
//%includeGuardStart } CoDoLBXzZV/yPyG+jVhw3g
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGame.h
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
//%Header } uLmHgPkxb1hNDZv1FTArRw
/*
 * $Id: MushGame.h,v 1.19 2006/10/17 11:05:55 southa Exp $
 * $Log: MushGame.h,v $
 * Revision 1.19  2006/10/17 11:05:55  southa
 * Expiry events
 *
 * Revision 1.18  2006/10/09 16:00:17  southa
 * Intern generation
 *
 * Revision 1.17  2006/10/02 17:25:04  southa
 * Object lookup and target selection
 *
 * Revision 1.16  2006/06/30 15:05:34  southa
 * Texture and buffer purge
 *
 * Revision 1.15  2006/06/01 15:39:19  southa
 * DrawArray verification and fixes
 *
 * Revision 1.14  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 * Revision 1.13  2005/07/12 12:18:18  southa
 * Projectile work
 *
 * Revision 1.12  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.11  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.10  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.9  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.8  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 * Revision 1.7  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 * Revision 1.6  2005/06/21 13:10:51  southa
 * MushGame work
 *
 * Revision 1.5  2005/06/20 16:14:30  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/20 14:30:35  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.2  2005/06/16 10:48:59  southa
 * Client/server work
 *
 * Revision 1.1  2005/06/14 20:39:41  southa
 * Adanaxis work
 *
 */

#include "MushGameAddress.h"
#include "MushGameAnimPostManip.h"
#include "MushGameAppHandler.h"
#include "MushGameAxisDef.h"
#include "MushGameBase.h"
#include "MushGameClient.h"
#include "MushGameConfigBase.h"
#include "MushGameConfigUtils.h"
#include "MushGameData.h"
#include "MushGameDespatch.h"
#include "MushGameDialogue.h"
#include "MushGameDialogueUtils.h"
#include "MushGameDigest.h"
#include "MushGameEvents.h"
#include "MushGameIntern.h"
#include "MushGameLink.h"
#include "MushGameJob.h"
#include "MushGameJobPlayerCreate.h"
#include "MushGameKeyDef.h"
#include "MushGameLink.h"
#include "MushGameLinkLocal.h"
#include "MushGameLogic.h"
#include "MushGameLogicLocal.h"
#include "MushGameMailbox.h"
#include "MushGameMessage.h"
#include "MushGameMessageCollision.h"
#include "MushGameMessageCollisionFatal.h"
#include "MushGameMessageControlInfo.h"
#include "MushGameMessageFire.h"
#include "MushGameMessageJoinConfirm.h"
#include "MushGameMessageJoinDenied.h"
#include "MushGameMessageJoinRequest.h"
#include "MushGameMessageUplinkPiece.h"
#include "MushGameMessageUplinkPlayer.h"
#include "MushGamePiecePlayer.h"
#include "MushGameReceiver.h"
#include "MushGameRef.h"
#include "MushGameRefPlayer.h"
#include "MushGameRender.h"
#include "MushGameSaveData.h"
#include "MushGameServer.h"
#include "MushGameStandard.h"
#include "MushGameUtil.h"
#include "MushGameVolatileData.h"

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
