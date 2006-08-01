//%includeGuardStart {
#ifndef ADANAXISRUBYKHAZI_H
#define ADANAXISRUBYKHAZI_H
//%includeGuardStart } ygxUTLnMFUKgJVIuElcxbA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRubyKhazi.h
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
//%Header } +2/2FpLVrTBmCtOQ+uRfKw
/*
 * $Id: AdanaxisRubyKhazi.h,v 1.1 2006/06/21 12:17:56 southa Exp $
 * $Log: AdanaxisRubyKhazi.h,v $
 * Revision 1.1  2006/06/21 12:17:56  southa
 * Ruby object generation
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisPieceKhazi.h"

#include "API/mushMushRuby.h"

class AdanaxisRubyKhazi : public MushRubyMaptorObj<AdanaxisPieceKhazi>
{
public:
	static void RubyInstall(void);
	static Mushware::tRubyValue post(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue post_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	
protected:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
