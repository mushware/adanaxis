//%includeGuardStart {
#ifndef MUSHGAMESTANDARD_H
#define MUSHGAMESTANDARD_H
//%includeGuardStart } PZ6kre97A1TFf2hJNDPD+Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameStandard.h
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
//%Header } diDhbsEFfTPnHV47+Pwc4g
/*
 * $Id: MushGameStandard.h,v 1.7 2006/10/09 16:00:17 southa Exp $
 * $Log: MushGameStandard.h,v $
 * Revision 1.7  2006/10/09 16:00:17  southa
 * Intern generation
 *
 * Revision 1.6  2006/06/22 19:07:32  southa
 * Build fixes
 *
 * Revision 1.5  2006/06/01 15:39:27  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/07/27 18:07:25  southa
 * Collision checking
 *
 * Revision 1.3  2005/07/01 10:36:46  southa
 * MushRender work
 *
 * Revision 1.2  2005/06/24 10:30:13  southa
 * MushGame camera work
 *
 * Revision 1.1  2005/06/14 13:25:34  southa
 * Adanaxis work
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#elif defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#else
#include "Mushcore/Mushcore.h"
#endif

#if defined(HAVE_MUSHMESH_MUSHMESH_H)
#include <MushMesh/MushMesh.h>
#elif defined(HAVE_MUSHMESH_H)
#include <MushMesh.h>
#else
#include "MushMesh/MushMesh.h"
#endif

#if defined(HAVE_MUSHRUBY_MUSHRUBY_H)
#include <MushRuby/MushRuby.h>
#elif defined(HAVE_MUSHRUBY_H)
#include <MushRuby.h>
#else
#include "MushRuby/MushRuby.h"
#endif

namespace Mushware
{
    typedef Mushware::U64 tGameUsec;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
