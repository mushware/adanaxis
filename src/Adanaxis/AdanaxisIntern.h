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
 * $Id: AdanaxisIntern.h,v 1.2 2006/10/02 17:25:04 southa Exp $
 * $Log: AdanaxisIntern.h,v $
 * Revision 1.2  2006/10/02 17:25:04  southa
 * Object lookup and target selection
 *
 * Revision 1.1  2006/08/17 08:57:11  southa
 * Event handling
 *
 */

#include "AdanaxisStandard.h"

#define ADANAXISINTERN_ID(a) \
public: \
Mushware::tRubyID a(void) { return m_##a; } \
private: \
Mushware::tRubyID m_##a

#define ADANAXISINTERN_VALUE(a) \
public: \
const MushRubyValue& a(void) { return m_##a; } \
private: \
MushRubyValue m_##a


class AdanaxisIntern : public MushcoreSingleton<AdanaxisIntern>
{
public:
    AdanaxisIntern();
    ADANAXISINTERN_ID(AdanaxisPieceKhazi);
    ADANAXISINTERN_ID(AdanaxisPiecePlayer);
    ADANAXISINTERN_ID(AdanaxisPieceProjectile);
    ADANAXISINTERN_VALUE(KlassAdanaxisPieceKhazi);
    ADANAXISINTERN_VALUE(KlassAdanaxisPiecePlayer);
    ADANAXISINTERN_VALUE(KlassAdanaxisPieceProjectile);
};

#undef ADANAXISINTERN_ID
#undef ADANAXISINTERN_VALUE

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
