//%includeGuardStart {
#ifndef ADANAXISPIECE_H
#define ADANAXISPIECE_H
//%includeGuardStart } 8Im+BPIX3SauUY+jOIyAhw
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPiece.h
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
//%Header } 2lhhIB4GRRfcCfxLJkTJ3Q
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisStandard.h"

#include "API/mushMushGame.h"

class AdanaxisPiece : public MushGamePiece
{
public:
    static Mushware::tRubyValue Klass(void);
    static void RubyInstall(void);
    
private:
    static Mushware::tRubyValue m_rubyKlass; // Must duplicate this in derived classes
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw