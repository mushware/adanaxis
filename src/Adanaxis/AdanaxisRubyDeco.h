//%includeGuardStart {
#ifndef ADANAXISRUBYDECO_H
#define ADANAXISRUBYDECO_H
//%includeGuardStart } cz/+ClBAmldMFI+VxA6heg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRubyDeco.h
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
//%Header } 65DHb4oh82NvStqKpM8hgg
/*
 * $Id: AdanaxisRubyDeco.h,v 1.1 2006/06/21 16:52:29 southa Exp $
 * $Log: AdanaxisRubyDeco.h,v $
 * Revision 1.1  2006/06/21 16:52:29  southa
 * Deco objects
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisPieceDeco.h"

#include "API/mushMushRuby.h"

class AdanaxisRubyDeco : public MushRubyMaptorObj<AdanaxisPieceDeco>
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
