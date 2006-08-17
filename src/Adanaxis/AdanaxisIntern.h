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
 * $Id$
 * $Log$
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
    ADANAXISINTERN_VALUE(KlassAdanaxisPieceKhazi);
};

#undef ADANAXISINTERN_ID
#undef ADANAXISINTERN_VALUE

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
