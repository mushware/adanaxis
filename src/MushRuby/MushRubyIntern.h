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
 * $Id: MushRubyIntern.h,v 1.6 2006/06/20 19:06:55 southa Exp $
 * $Log: MushRubyIntern.h,v $
 * Revision 1.6  2006/06/20 19:06:55  southa
 * Object creation
 *
 * Revision 1.5  2006/06/19 15:57:20  southa
 * Materials
 *
 * Revision 1.4  2006/06/16 01:02:33  southa
 * Ruby mesh generation
 *
 * Revision 1.3  2006/06/14 18:45:50  southa
 * Ruby mesh generation
 *
 * Revision 1.2  2006/06/14 11:20:09  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/06/13 10:35:06  southa
 * Ruby data objects
 *
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
	MUSHRUBYINTERN_DECLARE(angular_position);
	MUSHRUBYINTERN_DECLARE(angular_velocity);
	MUSHRUBYINTERN_DECLARE(backtrace);
	MUSHRUBYINTERN_DECLARE(cToPrint);
	MUSHRUBYINTERN_DECLARE(displacement);
	MUSHRUBYINTERN_DECLARE(displacement_velocity);
	MUSHRUBYINTERN_DECLARE(mesh_name);
	MUSHRUBYINTERN_DECLARE(num_iterations);
	MUSHRUBYINTERN_DECLARE(name);
	MUSHRUBYINTERN_DECLARE(offset);
	MUSHRUBYINTERN_DECLARE(order);
	MUSHRUBYINTERN_DECLARE(position);
	MUSHRUBYINTERN_DECLARE(post);
	MUSHRUBYINTERN_DECLARE(rotation);
	MUSHRUBYINTERN_DECLARE(scale);
	MUSHRUBYINTERN_DECLARE(scale_velocity);
	MUSHRUBYINTERN_DECLARE(size);
	MUSHRUBYINTERN_DECLARE(sourceface);
	MUSHRUBYINTERN_DECLARE(texture_name);
	MUSHRUBYINTERN_DECLARE(to_ary);
	MUSHRUBYINTERN_DECLARE(to_s);
	MUSHRUBYINTERN_DECLARE(to_point);
	MUSHRUBYINTERN_DECLARE(velocity);
};

#undef MUSHRUBYINTERN_DECLARE

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
