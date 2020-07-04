//%includeGuardStart {
#ifndef MUSHRUBYINTERN_H
#define MUSHRUBYINTERN_H
//%includeGuardStart } NDIj5SmGti5C1xMEp5xZHg
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyIntern.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } D1VjU91i+KHEtlsk92O6aw
/*
 * $Id: MushRubyIntern.h,v 1.25 2007/02/08 17:55:15 southa Exp $
 * $Log: MushRubyIntern.h,v $
 * Revision 1.25  2007/02/08 17:55:15  southa
 * Common routines in space generation
 *
 * Revision 1.24  2006/10/08 11:31:33  southa
 * Hit points
 *
 * Revision 1.23  2006/10/06 14:48:19  southa
 * Material animation
 *
 * Revision 1.22  2006/10/04 13:35:25  southa
 * Selective targetting
 *
 * Revision 1.21  2006/10/03 14:06:52  southa
 * Khazi and projectile creation
 *
 * Revision 1.20  2006/09/07 10:02:38  southa
 * Shader interface
 *
 * Revision 1.19  2006/08/25 01:44:57  southa
 * Khazi fire
 *
 * Revision 1.18  2006/08/24 16:30:56  southa
 * Event handling
 *
 * Revision 1.17  2006/08/24 13:04:38  southa
 * Event handling
 *
 * Revision 1.16  2006/08/20 14:19:22  southa
 * Seek operation
 *
 * Revision 1.15  2006/08/19 09:12:10  southa
 * Event handling
 *
 * Revision 1.14  2006/08/17 08:57:13  southa
 * Event handling
 *
 * Revision 1.13  2006/07/31 11:01:39  southa
 * Music and dialogues
 *
 * Revision 1.12  2006/07/27 13:51:36  southa
 * Menu and control fixes
 *
 * Revision 1.11  2006/07/20 12:22:23  southa
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
 * Revision 1.7  2006/06/21 12:17:59  southa
 * Ruby object generation
 *
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

#define MUSHRUBYINTERN_DECLARE_AT(a) \
public: \
static Mushware::tRubyID AT ## a(void) { return m_AT##a; } \
private: \
static Mushware::tRubyID m_AT##a

class MushRubyIntern
{
public:
	static void Initialise(void);
    static Mushware::tRubyID SymbolID(const char *inStr);
    static Mushware::tRubyID SymbolID(const std::string& inStr);
	MUSHRUBYINTERN_DECLARE(angular_position);
	MUSHRUBYINTERN_DECLARE(angular_velocity);
	MUSHRUBYINTERN_DECLARE(backtrace);
	MUSHRUBYINTERN_DECLARE(cRegisteredCreate);
	MUSHRUBYINTERN_DECLARE(cToPrint);
	MUSHRUBYINTERN_DECLARE(displacement);
	MUSHRUBYINTERN_DECLARE(displacement_velocity);
	MUSHRUBYINTERN_DECLARE(divide);
	MUSHRUBYINTERN_DECLARE(event);
	MUSHRUBYINTERN_DECLARE(extent);
	MUSHRUBYINTERN_DECLARE(fragment_shader);
	MUSHRUBYINTERN_DECLARE(hit_points);
	MUSHRUBYINTERN_DECLARE(id_suffix);
	MUSHRUBYINTERN_DECLARE(inspect);
	MUSHRUBYINTERN_DECLARE(Integer);
	MUSHRUBYINTERN_DECLARE(klass);
	MUSHRUBYINTERN_DECLARE(lifetime_msec);
	MUSHRUBYINTERN_DECLARE(mesh_name);
	MUSHRUBYINTERN_DECLARE(mBanner);
	MUSHRUBYINTERN_DECLARE(mHandleGameStart);
	MUSHRUBYINTERN_DECLARE(mInitialise);
	MUSHRUBYINTERN_DECLARE(mKeypress);
	MUSHRUBYINTERN_DECLARE(mPrecacheRender);
	MUSHRUBYINTERN_DECLARE(mPrecache);
	MUSHRUBYINTERN_DECLARE(mRegisteredDestroy);
	MUSHRUBYINTERN_DECLARE(mRender);
	MUSHRUBYINTERN_DECLARE(mReset);
	MUSHRUBYINTERN_DECLARE(mSave);
	MUSHRUBYINTERN_DECLARE(num_iterations);
	MUSHRUBYINTERN_DECLARE(name);
	MUSHRUBYINTERN_DECLARE(offset);
	MUSHRUBYINTERN_DECLARE(order);
	MUSHRUBYINTERN_DECLARE(owner);
	MUSHRUBYINTERN_DECLARE(position);
	MUSHRUBYINTERN_DECLARE(post);
	MUSHRUBYINTERN_DECLARE(program);
	MUSHRUBYINTERN_DECLARE(rotation);
	MUSHRUBYINTERN_DECLARE(scale);
	MUSHRUBYINTERN_DECLARE(scale_velocity);
	MUSHRUBYINTERN_DECLARE(size);
	MUSHRUBYINTERN_DECLARE(sourceface);
	MUSHRUBYINTERN_DECLARE(texture_name);
	MUSHRUBYINTERN_DECLARE(texture_names);
	MUSHRUBYINTERN_DECLARE(to_ary);
	MUSHRUBYINTERN_DECLARE(to_s);
	MUSHRUBYINTERN_DECLARE(to_point);
	MUSHRUBYINTERN_DECLARE(velocity);
	MUSHRUBYINTERN_DECLARE(vertex_shader);

	MUSHRUBYINTERN_DECLARE_AT(_embeddedDataPtr);
	MUSHRUBYINTERN_DECLARE_AT(m_expireFlag);
	MUSHRUBYINTERN_DECLARE_AT(m_hitPoints);
	MUSHRUBYINTERN_DECLARE_AT(m_id);
	MUSHRUBYINTERN_DECLARE_AT(m_idSuffix);
	MUSHRUBYINTERN_DECLARE_AT(m_initialVelocity);
    MUSHRUBYINTERN_DECLARE_AT(m_lifeMsec);
	MUSHRUBYINTERN_DECLARE_AT(m_meshName);
	MUSHRUBYINTERN_DECLARE_AT(m_owner);
	MUSHRUBYINTERN_DECLARE_AT(m_post);
};

#undef MUSHRUBYINTERN_DECLARE

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
