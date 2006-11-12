//%includeGuardStart {
#ifndef ADANAXISINTERN_H
#define ADANAXISINTERN_H
//%includeGuardStart } Y5fHmMEhJ1TgPzkZOWkZQQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisIntern.h
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } WBiqbvbumO43Eps7fHh03A
/*
 * $Id: AdanaxisIntern.h,v 1.14 2006/11/12 14:39:50 southa Exp $
 * $Log: AdanaxisIntern.h,v $
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
    @m_keyNum
    @m_speedLimit
    @m_state
    mCollisionEventConsume
    mMenuRender
    mRender
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
    Mushware::tRubyID ATm_keyNum(void) { return m_ATm_keyNum; }
    Mushware::tRubyID ATm_speedLimit(void) { return m_ATm_speedLimit; }
    Mushware::tRubyID ATm_state(void) { return m_ATm_state; }
    Mushware::tRubyID mCollisionEventConsume(void) { return m_mCollisionEventConsume; }
    Mushware::tRubyID mMenuRender(void) { return m_mMenuRender; }
    Mushware::tRubyID mRender(void) { return m_mRender; }
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
    Mushware::tRubyID m_ATm_keyNum;
    Mushware::tRubyID m_ATm_speedLimit;
    Mushware::tRubyID m_ATm_state;
    Mushware::tRubyID m_mCollisionEventConsume;
    Mushware::tRubyID m_mMenuRender;
    Mushware::tRubyID m_mRender;
//%declarations } 12c94c780123a2a7abbd6b0d57f4d64e

//%classPrototypes {
public:
//%classPrototypes } 0ImSRh0/JBpOMwe5g8vGcA
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
