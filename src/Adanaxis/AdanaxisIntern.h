//%includeGuardStart {
#ifndef ADANAXISINTERN_H
#define ADANAXISINTERN_H
//%includeGuardStart } Y5fHmMEhJ1TgPzkZOWkZQQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisIntern.h
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
//%Header } LHiNdhX9x3UlXVWd9U6BTw
/*
 * $Id: AdanaxisIntern.h,v 1.31 2007/06/07 13:23:03 southa Exp $
 * $Log: AdanaxisIntern.h,v $
 * Revision 1.31  2007/06/07 13:23:03  southa
 * Level 24
 *
 * Revision 1.30  2007/06/06 15:11:21  southa
 * Level 23
 *
 * Revision 1.29  2007/06/02 15:56:58  southa
 * Shader fix and prerelease work
 *
 * Revision 1.28  2007/05/22 12:59:09  southa
 * Vortex effect on player
 *
 * Revision 1.27  2007/05/09 19:24:44  southa
 * Level 14
 *
 * Revision 1.26  2007/04/18 09:22:01  southa
 * Header and level fixes
 *
 * Revision 1.25  2007/03/24 18:07:24  southa
 * Level 3 work
 *
 * Revision 1.24  2007/03/13 18:21:37  southa
 * Scanner jamming
 *
 * Revision 1.23  2007/03/13 12:22:50  southa
 * Scanner symbols
 *
 * Revision 1.22  2007/03/09 11:29:13  southa
 * Game end actions
 *
 * Revision 1.21  2007/03/08 18:38:14  southa
 * Level progression
 *
 * Revision 1.20  2007/03/07 16:59:43  southa
 * Khazi spawning and level ends
 *
 * Revision 1.19  2007/02/08 17:55:14  southa
 * Common routines in space generation
 *
 * Revision 1.18  2006/12/14 15:59:23  southa
 * Fire and cutscene fixes
 *
 * Revision 1.17  2006/11/21 10:08:23  southa
 * Initial cut scene handling
 *
 * Revision 1.16  2006/11/14 20:28:36  southa
 * Added rail gun
 *
 * Revision 1.15  2006/11/12 20:09:54  southa
 * Missile guidance
 *
 * Revision 1.14  2006/11/12 14:39:50  southa
 * Player weapons amd audio fix
 *
 * Revision 1.13  2006/11/03 18:46:33  southa
 * Damage effectors
 *
 * Revision 1.12  2006/11/02 09:47:33  southa
 * Player weapon control
 *
 * Revision 1.11  2006/10/30 17:03:50  southa
 * Remnants creation
 *
 * Revision 1.10  2006/10/19 15:41:35  southa
 * Item handling
 *
 * Revision 1.9  2006/10/17 15:28:01  southa
 * Player collisions
 *
 * Revision 1.8  2006/10/17 11:05:54  southa
 * Expiry events
 *
 * Revision 1.7  2006/10/14 16:59:44  southa
 * Ruby Deco objects
 *
 * Revision 1.6  2006/10/12 22:04:46  southa
 * Collision events
 *
 * Revision 1.5  2006/10/04 21:39:35  southa
 * Source processing
 *
 * Revision 1.4  2006/10/03 15:28:21  southa
 * Source process directives
 *
 * Revision 1.3  2006/10/03 14:06:51  southa
 * Khazi and projectile creation
 *
 * Revision 1.2  2006/10/02 17:25:04  southa
 * Object lookup and target selection
 *
 * Revision 1.1  2006/08/17 08:57:11  southa
 * Event handling
 *
 */


#include "AdanaxisStandard.h"

//:process ProcessIntern.rb
/*
:data1begin
  ids = %w{
    @m_acceleration
    @m_controlReleased
    @m_isJammer
    @m_isStealth
    @m_keyNum
    @m_rail
    @m_scannerSymbol
    @m_speedLimit
    @m_state
    @m_thrustReleased
    mCollisionEventConsume
    mCutSceneRender
    mEpilogueRender
    mGameModeTick
    mHandlePrecacheEnd
    mJammersEliminated
    mKhaziCountUpdate
    mLoad
    mMenuRender
    mReceiveSequence
    mRender
    mSpaceNameSet
  }
  classes = %w{
    AdanaxisEventFire
    AdanaxisEventKeyState
    AdanaxisPiece
    AdanaxisPieceDeco
    AdanaxisPieceEffector
    AdanaxisPieceItem
    AdanaxisPieceKhazi
    AdanaxisPiecePlayer
    AdanaxisPieceProjectile
  }
:data1end
*/

class AdanaxisIntern : public MushcoreSingleton<AdanaxisIntern>
{
public:
    AdanaxisIntern();
//%declarations {
public:
    MushRubyValue& AdanaxisEventFire(void) { return m_klassAdanaxisEventFire; }
    MushRubyValue& AdanaxisEventKeyState(void) { return m_klassAdanaxisEventKeyState; }
    MushRubyValue& AdanaxisPiece(void) { return m_klassAdanaxisPiece; }
    MushRubyValue& AdanaxisPieceDeco(void) { return m_klassAdanaxisPieceDeco; }
    MushRubyValue& AdanaxisPieceEffector(void) { return m_klassAdanaxisPieceEffector; }
    MushRubyValue& AdanaxisPieceItem(void) { return m_klassAdanaxisPieceItem; }
    MushRubyValue& AdanaxisPieceKhazi(void) { return m_klassAdanaxisPieceKhazi; }
    MushRubyValue& AdanaxisPiecePlayer(void) { return m_klassAdanaxisPiecePlayer; }
    MushRubyValue& AdanaxisPieceProjectile(void) { return m_klassAdanaxisPieceProjectile; }
    Mushware::tRubyID ATm_acceleration(void) { return m_ATm_acceleration; }
    Mushware::tRubyID ATm_controlReleased(void) { return m_ATm_controlReleased; }
    Mushware::tRubyID ATm_isJammer(void) { return m_ATm_isJammer; }
    Mushware::tRubyID ATm_isStealth(void) { return m_ATm_isStealth; }
    Mushware::tRubyID ATm_keyNum(void) { return m_ATm_keyNum; }
    Mushware::tRubyID ATm_rail(void) { return m_ATm_rail; }
    Mushware::tRubyID ATm_scannerSymbol(void) { return m_ATm_scannerSymbol; }
    Mushware::tRubyID ATm_speedLimit(void) { return m_ATm_speedLimit; }
    Mushware::tRubyID ATm_state(void) { return m_ATm_state; }
    Mushware::tRubyID ATm_thrustReleased(void) { return m_ATm_thrustReleased; }
    Mushware::tRubyID mCollisionEventConsume(void) { return m_mCollisionEventConsume; }
    Mushware::tRubyID mCutSceneRender(void) { return m_mCutSceneRender; }
    Mushware::tRubyID mEpilogueRender(void) { return m_mEpilogueRender; }
    Mushware::tRubyID mGameModeTick(void) { return m_mGameModeTick; }
    Mushware::tRubyID mHandlePrecacheEnd(void) { return m_mHandlePrecacheEnd; }
    Mushware::tRubyID mJammersEliminated(void) { return m_mJammersEliminated; }
    Mushware::tRubyID mKhaziCountUpdate(void) { return m_mKhaziCountUpdate; }
    Mushware::tRubyID mLoad(void) { return m_mLoad; }
    Mushware::tRubyID mMenuRender(void) { return m_mMenuRender; }
    Mushware::tRubyID mReceiveSequence(void) { return m_mReceiveSequence; }
    Mushware::tRubyID mRender(void) { return m_mRender; }
    Mushware::tRubyID mSpaceNameSet(void) { return m_mSpaceNameSet; }
private:
    MushRubyValue m_klassAdanaxisEventFire;
    MushRubyValue m_klassAdanaxisEventKeyState;
    MushRubyValue m_klassAdanaxisPiece;
    MushRubyValue m_klassAdanaxisPieceDeco;
    MushRubyValue m_klassAdanaxisPieceEffector;
    MushRubyValue m_klassAdanaxisPieceItem;
    MushRubyValue m_klassAdanaxisPieceKhazi;
    MushRubyValue m_klassAdanaxisPiecePlayer;
    MushRubyValue m_klassAdanaxisPieceProjectile;
    Mushware::tRubyID m_ATm_acceleration;
    Mushware::tRubyID m_ATm_controlReleased;
    Mushware::tRubyID m_ATm_isJammer;
    Mushware::tRubyID m_ATm_isStealth;
    Mushware::tRubyID m_ATm_keyNum;
    Mushware::tRubyID m_ATm_rail;
    Mushware::tRubyID m_ATm_scannerSymbol;
    Mushware::tRubyID m_ATm_speedLimit;
    Mushware::tRubyID m_ATm_state;
    Mushware::tRubyID m_ATm_thrustReleased;
    Mushware::tRubyID m_mCollisionEventConsume;
    Mushware::tRubyID m_mCutSceneRender;
    Mushware::tRubyID m_mEpilogueRender;
    Mushware::tRubyID m_mGameModeTick;
    Mushware::tRubyID m_mHandlePrecacheEnd;
    Mushware::tRubyID m_mJammersEliminated;
    Mushware::tRubyID m_mKhaziCountUpdate;
    Mushware::tRubyID m_mLoad;
    Mushware::tRubyID m_mMenuRender;
    Mushware::tRubyID m_mReceiveSequence;
    Mushware::tRubyID m_mRender;
    Mushware::tRubyID m_mSpaceNameSet;
//%declarations } 5bfadd11ed379df0d2976f869c615ca3

//%classPrototypes {
public:
//%classPrototypes } 0ImSRh0/JBpOMwe5g8vGcA
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
