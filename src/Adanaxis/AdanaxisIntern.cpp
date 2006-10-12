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
 * $Id: AdanaxisIntern.cpp,v 1.3 2006/10/03 14:06:50 southa Exp $
 * $Log: AdanaxisIntern.cpp,v $
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
    m_klassAdanaxisPieceKhazi = MushRubyValue(MushRubyUtil::Class("AdanaxisPieceKhazi"));
    m_klassAdanaxisPiecePlayer = MushRubyValue(MushRubyUtil::Class("AdanaxisPiecePlayer"));
    m_klassAdanaxisPieceProjectile = MushRubyValue(MushRubyUtil::Class("AdanaxisPieceProjectile"));
//%initialisations } d5a206b442010e7f793fbfa25fa5e830
}
