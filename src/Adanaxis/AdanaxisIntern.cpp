//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisIntern.cpp
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
//%Header } RenMbuEB4fvFF9tELjmWkw
/*
 * $Id: AdanaxisIntern.cpp,v 1.28 2007/06/07 13:23:03 southa Exp $
 * $Log: AdanaxisIntern.cpp,v $
 * Revision 1.28  2007/06/07 13:23:03  southa
 * Level 24
 *
 * Revision 1.27  2007/06/06 15:11:21  southa
 * Level 23
 *
 * Revision 1.26  2007/06/02 15:56:58  southa
 * Shader fix and prerelease work
 *
 * Revision 1.25  2007/05/22 12:59:09  southa
 * Vortex effect on player
 *
 * Revision 1.24  2007/05/09 19:24:44  southa
 * Level 14
 *
 * Revision 1.23  2007/04/18 09:22:01  southa
 * Header and level fixes
 *
 * Revision 1.22  2007/03/24 18:07:24  southa
 * Level 3 work
 *
 * Revision 1.21  2007/03/13 18:21:36  southa
 * Scanner jamming
 *
 * Revision 1.20  2007/03/13 12:22:50  southa
 * Scanner symbols
 *
 * Revision 1.19  2007/03/09 11:29:12  southa
 * Game end actions
 *
 * Revision 1.18  2007/03/08 18:38:14  southa
 * Level progression
 *
 * Revision 1.17  2007/03/07 16:59:43  southa
 * Khazi spawning and level ends
 *
 * Revision 1.16  2007/02/08 17:55:14  southa
 * Common routines in space generation
 *
 * Revision 1.15  2006/12/14 15:59:23  southa
 * Fire and cutscene fixes
 *
 * Revision 1.14  2006/11/21 10:08:23  southa
 * Initial cut scene handling
 *
 * Revision 1.13  2006/11/14 20:28:36  southa
 * Added rail gun
 *
 * Revision 1.12  2006/11/12 20:09:54  southa
 * Missile guidance
 *
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
    m_ATm_controlReleased = MushRubyIntern::SymbolID("@m_controlReleased");
    m_ATm_isJammer = MushRubyIntern::SymbolID("@m_isJammer");
    m_ATm_isStealth = MushRubyIntern::SymbolID("@m_isStealth");
    m_ATm_keyNum = MushRubyIntern::SymbolID("@m_keyNum");
    m_ATm_rail = MushRubyIntern::SymbolID("@m_rail");
    m_ATm_scannerSymbol = MushRubyIntern::SymbolID("@m_scannerSymbol");
    m_ATm_speedLimit = MushRubyIntern::SymbolID("@m_speedLimit");
    m_ATm_state = MushRubyIntern::SymbolID("@m_state");
    m_ATm_thrustReleased = MushRubyIntern::SymbolID("@m_thrustReleased");
    m_mCollisionEventConsume = MushRubyIntern::SymbolID("mCollisionEventConsume");
    m_mCutSceneRender = MushRubyIntern::SymbolID("mCutSceneRender");
    m_mEpilogueRender = MushRubyIntern::SymbolID("mEpilogueRender");
    m_mGameModeTick = MushRubyIntern::SymbolID("mGameModeTick");
    m_mHandlePrecacheEnd = MushRubyIntern::SymbolID("mHandlePrecacheEnd");
    m_mJammersEliminated = MushRubyIntern::SymbolID("mJammersEliminated");
    m_mKhaziCountUpdate = MushRubyIntern::SymbolID("mKhaziCountUpdate");
    m_mLoad = MushRubyIntern::SymbolID("mLoad");
    m_mMenuRender = MushRubyIntern::SymbolID("mMenuRender");
    m_mReceiveSequence = MushRubyIntern::SymbolID("mReceiveSequence");
    m_mRender = MushRubyIntern::SymbolID("mRender");
    m_mSpaceNameSet = MushRubyIntern::SymbolID("mSpaceNameSet");
//%initialisations } eaea143ec38d643ffb9a389254c69a09
}
 
