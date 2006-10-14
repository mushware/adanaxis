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
 * $Id: AdanaxisIntern.h,v 1.6 2006/10/12 22:04:46 southa Exp $
 * $Log: AdanaxisIntern.h,v $
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
    mCollisionEventConsume
  }
  classes = %w{
    AdanaxisPieceDeco
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
    MushRubyValue& AdanaxisPieceDeco(void) { return m_klassAdanaxisPieceDeco; }
    MushRubyValue& AdanaxisPieceKhazi(void) { return m_klassAdanaxisPieceKhazi; }
    MushRubyValue& AdanaxisPiecePlayer(void) { return m_klassAdanaxisPiecePlayer; }
    MushRubyValue& AdanaxisPieceProjectile(void) { return m_klassAdanaxisPieceProjectile; }
    Mushware::tRubyID mCollisionEventConsume(void) { return m_mCollisionEventConsume; }
private:
    MushRubyValue m_klassAdanaxisPieceDeco;
    MushRubyValue m_klassAdanaxisPieceKhazi;
    MushRubyValue m_klassAdanaxisPiecePlayer;
    MushRubyValue m_klassAdanaxisPieceProjectile;
    Mushware::tRubyID m_mCollisionEventConsume;
//%declarations } e46191660152c12dbcbbed46d185946c

//%classPrototypes {
public:
//%classPrototypes } 0ImSRh0/JBpOMwe5g8vGcA
};

#undef ADANAXISINTERN_ID
#undef ADANAXISINTERN_VALUE

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
