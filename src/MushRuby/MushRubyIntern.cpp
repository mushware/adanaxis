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
 * $Id: MushRubyIntern.cpp,v 1.17 2006/08/24 13:04:38 southa Exp $
 * $Log: MushRubyIntern.cpp,v $
 * Revision 1.17  2006/08/24 13:04:38  southa
 * Event handling
 *
 * Revision 1.16  2006/08/20 14:19:22  southa
 * Seek operation
 *
 * Revision 1.15  2006/08/19 09:12:09  southa
 * Event handling
 *
 * Revision 1.14  2006/08/17 08:57:12  southa
 * Event handling
 *
 * Revision 1.13  2006/07/31 11:01:39  southa
 * Music and dialogues
 *
 * Revision 1.12  2006/07/27 13:51:36  southa
 * Menu and control fixes
 *
 * Revision 1.11  2006/07/20 12:22:22  southa
 * Precache display
 *
 * Revision 1.10  2006/07/04 16:55:28  southa
 * Ruby key handling
 *
 * Revision 1.9  2006/07/02 21:08:55  southa
 * Ruby menu work
 *
 * Revision 1.8  2006/07/02 09:43:28  southa
 * MushGLFont work
 *
 * Revision 1.7  2006/06/21 12:17:58  southa
 * Ruby object generation
 *
 * Revision 1.6  2006/06/20 19:06:54  southa
 * Object creation
 *
 * Revision 1.5  2006/06/19 15:57:19  southa
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
 * Revision 1.1  2006/06/13 10:35:05  southa
 * Ruby data objects
 *
 */

#include "MushRubyIntern.h"

#include "MushRubyRuby.h"

#define MUSHRUBYINTERN_DEFINE(a) Mushware::tRubyID MushRubyIntern::m_##a = 0
#define MUSHRUBYINTERN_DEFINE_AT(a) Mushware::tRubyID MushRubyIntern::m_AT##a = 0
#define MUSHRUBYINTERN_INIT(a) m_##a = rb_intern(#a)
#define MUSHRUBYINTERN_INIT_AT(a) m_AT##a = rb_intern("@" #a)

MUSHRUBYINTERN_DEFINE(angular_position);
MUSHRUBYINTERN_DEFINE(angular_velocity);
MUSHRUBYINTERN_DEFINE(backtrace);
MUSHRUBYINTERN_DEFINE(cRegisteredCreate);
MUSHRUBYINTERN_DEFINE(cToPrint);
MUSHRUBYINTERN_DEFINE(displacement);
MUSHRUBYINTERN_DEFINE(displacement_velocity);
MUSHRUBYINTERN_DEFINE(divide);
MUSHRUBYINTERN_DEFINE(event);
MUSHRUBYINTERN_DEFINE(extent);
MUSHRUBYINTERN_DEFINE(inspect);
MUSHRUBYINTERN_DEFINE(Integer);
MUSHRUBYINTERN_DEFINE(klass);
MUSHRUBYINTERN_DEFINE(mesh_name);
MUSHRUBYINTERN_DEFINE(mBanner);
MUSHRUBYINTERN_DEFINE(mHandleGameStart);
MUSHRUBYINTERN_DEFINE(mInitialise);
MUSHRUBYINTERN_DEFINE(mKeypress);
MUSHRUBYINTERN_DEFINE(mPreCache);
MUSHRUBYINTERN_DEFINE(mPreCacheRender);
MUSHRUBYINTERN_DEFINE(mRegisteredDestroy);
MUSHRUBYINTERN_DEFINE(mRender);
MUSHRUBYINTERN_DEFINE(mReset);
MUSHRUBYINTERN_DEFINE(name);
MUSHRUBYINTERN_DEFINE(num_iterations);
MUSHRUBYINTERN_DEFINE(offset);
MUSHRUBYINTERN_DEFINE(order);
MUSHRUBYINTERN_DEFINE(position);
MUSHRUBYINTERN_DEFINE(post);
MUSHRUBYINTERN_DEFINE(rotation);
MUSHRUBYINTERN_DEFINE(scale);
MUSHRUBYINTERN_DEFINE(scale_velocity);
MUSHRUBYINTERN_DEFINE(size);
MUSHRUBYINTERN_DEFINE(sourceface);
MUSHRUBYINTERN_DEFINE(texture_name);
MUSHRUBYINTERN_DEFINE(to_ary);
MUSHRUBYINTERN_DEFINE(to_point);
MUSHRUBYINTERN_DEFINE(to_s);
MUSHRUBYINTERN_DEFINE(velocity);

MUSHRUBYINTERN_DEFINE_AT(_embeddedDataPtr);
MUSHRUBYINTERN_DEFINE_AT(m_expireFlag);
MUSHRUBYINTERN_DEFINE_AT(m_id);
MUSHRUBYINTERN_DEFINE_AT(m_post);

void
MushRubyIntern::Initialise(void)
{
	MUSHRUBYINTERN_INIT(angular_position);
	MUSHRUBYINTERN_INIT(angular_velocity);
	MUSHRUBYINTERN_INIT(backtrace);
	MUSHRUBYINTERN_INIT(cRegisteredCreate);
	MUSHRUBYINTERN_INIT(cToPrint);
	MUSHRUBYINTERN_INIT(displacement);
	MUSHRUBYINTERN_INIT(displacement_velocity);
	MUSHRUBYINTERN_INIT(divide);
	MUSHRUBYINTERN_INIT(event);
	MUSHRUBYINTERN_INIT(extent);
	MUSHRUBYINTERN_INIT(inspect);
	MUSHRUBYINTERN_INIT(Integer);
	MUSHRUBYINTERN_INIT(klass);
	MUSHRUBYINTERN_INIT(mesh_name);
	MUSHRUBYINTERN_INIT(mBanner);
	MUSHRUBYINTERN_INIT(mHandleGameStart);
	MUSHRUBYINTERN_INIT(mInitialise);
	MUSHRUBYINTERN_INIT(mKeypress);
	MUSHRUBYINTERN_INIT(mPreCache);
	MUSHRUBYINTERN_INIT(mPreCacheRender);
	MUSHRUBYINTERN_INIT(mRegisteredDestroy);
	MUSHRUBYINTERN_INIT(mRender);
	MUSHRUBYINTERN_INIT(mReset);
	MUSHRUBYINTERN_INIT(name);
	MUSHRUBYINTERN_INIT(num_iterations);
	MUSHRUBYINTERN_INIT(offset);
	MUSHRUBYINTERN_INIT(order);
	MUSHRUBYINTERN_INIT(post);
	MUSHRUBYINTERN_INIT(position);
	MUSHRUBYINTERN_INIT(rotation);
	MUSHRUBYINTERN_INIT(scale);
	MUSHRUBYINTERN_INIT(scale_velocity);
	MUSHRUBYINTERN_INIT(size);
	MUSHRUBYINTERN_INIT(sourceface);
	MUSHRUBYINTERN_INIT(texture_name);
	MUSHRUBYINTERN_INIT(to_ary);
	MUSHRUBYINTERN_INIT(to_point);
	MUSHRUBYINTERN_INIT(to_s);
	MUSHRUBYINTERN_INIT(velocity);

	MUSHRUBYINTERN_INIT_AT(_embeddedDataPtr);
	MUSHRUBYINTERN_INIT_AT(m_expireFlag);
	MUSHRUBYINTERN_INIT_AT(m_id);
	MUSHRUBYINTERN_INIT_AT(m_post);
}

Mushware::tRubyID
MushRubyIntern::SymbolID(const char *inStr)
{
    return rb_intern(inStr);
}

Mushware::tRubyID
MushRubyIntern::SymbolID(const std::string& inStr)
{
    return rb_intern(inStr.c_str());
}
