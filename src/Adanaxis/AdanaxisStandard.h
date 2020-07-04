//%includeGuardStart {
#ifndef ADANAXISSTANDARD_H
#define ADANAXISSTANDARD_H
//%includeGuardStart } TLqsFapGK+RvGkKMgZQ8nQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisStandard.h
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
//%Header } KTxaDRifcAIXVMuQ/k9IXA
/*
 * $Id: AdanaxisStandard.h,v 1.9 2007/04/18 09:22:04 southa Exp $
 * $Log: AdanaxisStandard.h,v $
 * Revision 1.9  2007/04/18 09:22:04  southa
 * Header and level fixes
 *
 * Revision 1.8  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 * Revision 1.7  2006/08/17 08:57:12  southa
 * Event handling
 *
 * Revision 1.6  2006/08/01 17:21:30  southa
 * River demo
 *
 * Revision 1.5  2006/06/22 19:07:28  southa
 * Build fixes
 *
 * Revision 1.4  2006/06/01 15:38:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/14 13:25:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:55  southa
 * Adanaxis creation
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#include <Mushcore/MushcoreIO.h>
#elif defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#include <MushcoreIO.h>
#else
#include "Mushcore/Mushcore.h"
#include "Mushcore/MushcoreIO.h"
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

#include "mushGame.h"

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
