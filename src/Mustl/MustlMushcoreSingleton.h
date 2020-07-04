//%includeGuardStart {
#ifndef MUSTLMUSHCORESINGLETON_H
#define MUSTLMUSHCORESINGLETON_H
//%includeGuardStart } flYXKRCcGzn8LqLrF+jzMw
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlMushcoreSingleton.h
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
//%Header } V1LuC4qL1/akVr5AFOaFaA
/*
 * $Id: MustlMushcoreSingleton.h,v 1.9 2006/06/01 15:39:53 southa Exp $
 * $Log: MustlMushcoreSingleton.h,v $
 * Revision 1.9  2006/06/01 15:39:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.7  2004/09/26 21:07:15  southa
 * Mustl compilation fixes
 *
 * Revision 1.6  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.5  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:09:28  southa
 * Fixed file headers
 *
 * Revision 1.3  2003/02/05 17:36:36  southa
 * Build fixes
 *
 * Revision 1.2  2003/01/20 12:23:24  southa
 * Code and interface tidying
 *
 * Revision 1.1  2003/01/20 10:45:30  southa
 * Singleton tidying
 *
 */

#include "MustlStandard.h"

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/MushcoreSingleton.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <MushcoreSingleton.h>
#else
#include "Mushcore/MushcoreSingleton.h"
#endif
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
