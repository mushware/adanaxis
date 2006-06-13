//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyIntern.cpp
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
//%Header } lqALCPGBahbk4ibyVPO8LQ
/*
 * $Id$
 * $Log$
 */

#include "MushRubyIntern.h"

#include "MushRubyRuby.h"

#define MUSHRUBYINTERN_DEFINE(a) Mushware::tRubyID MushRubyIntern::m_##a = 0
#define MUSHRUBYINTERN_INIT(a) m_##a = rb_intern(#a)

MUSHRUBYINTERN_DEFINE(backtrace);
MUSHRUBYINTERN_DEFINE(cToPrint);
MUSHRUBYINTERN_DEFINE(size);
MUSHRUBYINTERN_DEFINE(to_ary);
MUSHRUBYINTERN_DEFINE(to_s);

void
MushRubyIntern::Initialise(void)
{
	MUSHRUBYINTERN_INIT(backtrace);
	MUSHRUBYINTERN_INIT(cToPrint);
	MUSHRUBYINTERN_INIT(size);
	MUSHRUBYINTERN_INIT(to_ary);
	MUSHRUBYINTERN_INIT(to_s);
}
