//%includeGuardStart {
#ifndef MUSHRUBYINTERN_H
#define MUSHRUBYINTERN_H
//%includeGuardStart } NDIj5SmGti5C1xMEp5xZHg
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyIntern.h
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
//%Header } n1eaCj2fb8dNPgbT0uOuEQ
/*
 * $Id$
 * $Log$
 */

#include "MushRubyStandard.h"

#define MUSHRUBYINTERN_DECLARE(a) \
public: \
static Mushware::tRubyID a(void) { return m_##a; } \
private: \
static Mushware::tRubyID m_##a


class MushRubyIntern
{
public:
	static void Initialise(void);
	MUSHRUBYINTERN_DECLARE(backtrace);
	MUSHRUBYINTERN_DECLARE(cToPrint);
	MUSHRUBYINTERN_DECLARE(size);
	MUSHRUBYINTERN_DECLARE(to_ary);
	MUSHRUBYINTERN_DECLARE(to_s);
};

#undef MUSHRUBYINTERN_DECLARE

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
