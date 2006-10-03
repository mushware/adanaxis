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
 * $Id: AdanaxisIntern.cpp,v 1.2 2006/10/02 17:25:04 southa Exp $
 * $Log: AdanaxisIntern.cpp,v $
 * Revision 1.2  2006/10/02 17:25:04  southa
 * Object lookup and target selection
 *
 * Revision 1.1  2006/08/17 08:57:11  southa
 * Event handling
 *
 */

#include "AdanaxisIntern.h"

MUSHCORE_SINGLETON_INSTANCE(AdanaxisIntern);

#define ADANAXISINTERN_INIT_ID(a) m_##a = MushRubyIntern::SymbolID(#a)

AdanaxisIntern::AdanaxisIntern() :
    m_KlassAdanaxisPieceKhazi(MushRubyUtil::Class("AdanaxisPieceKhazi")),
    m_KlassAdanaxisPiecePlayer(MushRubyUtil::Class("AdanaxisPiecePlayer")),
    m_KlassAdanaxisPieceProjectile(MushRubyUtil::Class("AdanaxisPieceProjectile"))
{
    ADANAXISINTERN_INIT_ID(AdanaxisPieceKhazi);
    ADANAXISINTERN_INIT_ID(AdanaxisPiecePlayer);
    ADANAXISINTERN_INIT_ID(AdanaxisPieceProjectile);
}
