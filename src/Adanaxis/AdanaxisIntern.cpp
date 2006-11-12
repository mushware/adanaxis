//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisIntern.cpp
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
//%Header } mqRyosjSblx9ADjVCHc1/g
/*
 * $Id: AdanaxisIntern.cpp,v 1.11 2006/11/12 14:39:50 southa Exp $
 * $Log: AdanaxisIntern.cpp,v $
 * Revision 1.11  2006/11/12 14:39:50  southa
 * Player weapons amd audio fix
 *
 * Revision 1.10  2006/11/03 18:46:33  southa
 * Damage effectors
 *
 * Revision 1.9  2006/11/02 09:47:33  southa
 * Player weapon control
 *
 * Revision 1.8  2006/10/30 17:03:50  southa
 * Remnants creation
 *
 * Revision 1.7  2006/10/19 15:41:35  southa
 * Item handling
 *
 * Revision 1.6  2006/10/17 15:28:01  southa
 * Player collisions
 *
 * Revision 1.5  2006/10/14 16:59:44  southa
 * Ruby Deco objects
 *
 * Revision 1.4  2006/10/12 22:04:46  southa
 * Collision events
 *
 * Revision 1.3  2006/10/03 14:06:50  southa
 * Khazi and projectile creation
 *
 * Revision 1.2  2006/10/02 17:25:04  southa
 * Object lookup and target selection
 *
 * Revision 1.1  2006/08/17 08:57:11  southa
 * Event handling
 *
 */

#include "AdanaxisIntern.h"

//:process ProcessIntern.rb

MUSHCORE_SINGLETON_INSTANCE(AdanaxisIntern);

AdanaxisIntern::AdanaxisIntern()
{
//%initialisations {
    m_klassAdanaxisEventFire = MushRubyValue(MushRubyUtil::Class("AdanaxisEventFire"));
    m_klassAdanaxisEventKeyState = MushRubyValue(MushRubyUtil::Class("AdanaxisEventKeyState"));
    m_klassAdanaxisPiece = MushRubyValue(MushRubyUtil::Class("AdanaxisPiece"));
    m_klassAdanaxisPieceDeco = MushRubyValue(MushRubyUtil::Class("AdanaxisPieceDeco"));
    m_klassAdanaxisPieceEffector = MushRubyValue(MushRubyUtil::Class("AdanaxisPieceEffector"));
    m_klassAdanaxisPieceItem = MushRubyValue(MushRubyUtil::Class("AdanaxisPieceItem"));
    m_klassAdanaxisPieceKhazi = MushRubyValue(MushRubyUtil::Class("AdanaxisPieceKhazi"));
    m_klassAdanaxisPiecePlayer = MushRubyValue(MushRubyUtil::Class("AdanaxisPiecePlayer"));
    m_klassAdanaxisPieceProjectile = MushRubyValue(MushRubyUtil::Class("AdanaxisPieceProjectile"));
    m_ATm_acceleration = MushRubyIntern::SymbolID("@m_acceleration");
    m_ATm_keyNum = MushRubyIntern::SymbolID("@m_keyNum");
    m_ATm_speedLimit = MushRubyIntern::SymbolID("@m_speedLimit");
    m_ATm_state = MushRubyIntern::SymbolID("@m_state");
    m_mCollisionEventConsume = MushRubyIntern::SymbolID("mCollisionEventConsume");
    m_mMenuRender = MushRubyIntern::SymbolID("mMenuRender");
    m_mRender = MushRubyIntern::SymbolID("mRender");
//%initialisations } c898401baa98222ba41f31af3786662b
}
