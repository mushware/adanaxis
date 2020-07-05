//%includeGuardStart {
#ifndef MUSTLMUSHCORE_H
#define MUSTLMUSHCORE_H
//%includeGuardStart } h+gqfDecxXjckM8W23Hqdg
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlMushcore.h
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
//%Header } ToiFXd42B1zpr3Byb1WgEQ
/*
 * $Id: MustlMushcore.h,v 1.7 2006/06/01 15:39:53 southa Exp $
 * $Log: MustlMushcore.h,v $
 * Revision 1.7  2006/06/01 15:39:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.4  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.3  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:28  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/13 15:01:20  southa
 * Fix Mustl command line build
 *
 */

#include "MustlStandard.h"

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#else
#include "Mushcore/Mushcore.h"
#endif
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
