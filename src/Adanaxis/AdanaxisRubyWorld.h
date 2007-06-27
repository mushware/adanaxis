//%includeGuardStart {
#ifndef ADANAXISRUBYWORLD_H
#define ADANAXISRUBYWORLD_H
//%includeGuardStart } wSaFePr/9sXFepUsX0jQCw
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRubyWorld.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.4, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } NjUIfROkf0XLlotUV9GmPg
/*
 * $Id: AdanaxisRubyWorld.h,v 1.3 2007/04/18 09:22:04 southa Exp $
 * $Log: AdanaxisRubyWorld.h,v $
 * Revision 1.3  2007/04/18 09:22:04  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/08/01 17:21:28  southa
 * River demo
 *
 * Revision 1.1  2006/07/19 10:22:15  southa
 * World objects
 *
 */

#include "AdanaxisPieceWorld.h"

#include "API/mushMushRuby.h"

class AdanaxisRubyWorld : public MushRubyMaptorObj<AdanaxisPieceWorld>
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
