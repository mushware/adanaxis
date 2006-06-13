//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyStandard.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } cAZ5yAFm+lHtMzO/urDaSg
/*
 * $Id: MushRubyStandard.cpp,v 1.2 2006/04/21 00:10:43 southa Exp $
 * $Log: MushRubyStandard.cpp,v $
 * Revision 1.2  2006/04/21 00:10:43  southa
 * MushGLFont ruby module
 *
 */

#include "MushRubyStandard.h"

#include "MushRubyRuby.h"

namespace Mushware
{
	const Mushware::tRubyValue kRubyQnil = Qnil;
	const Mushware::tRubyValue kRubyQfalse = Qfalse;
	const Mushware::tRubyValue kRubyQtrue = Qtrue;	
}

const Mushware::tRubyValue MushRuby::QNil = Qnil;
const Mushware::tRubyValue MushRuby::QFalse = Qfalse;
const Mushware::tRubyValue MushRuby::QTrue = Qtrue;
