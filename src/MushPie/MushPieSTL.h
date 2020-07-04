//%includeGuardStart {
#ifndef MUSHPIESTL_H
#define MUSHPIESTL_H
//%includeGuardStart } s1VDDs8uoifg5yG0M4Ld0Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSTL.h
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
//%Header } HA0Ox1tmBIfdAD9ylQFfqw
/*
 * $Id: MushPieSTL.h,v 1.6 2006/06/22 19:07:34 southa Exp $
 * $Log: MushPieSTL.h,v $
 * Revision 1.6  2006/06/22 19:07:34  southa
 * Build fixes
 *
 * Revision 1.5  2006/06/01 15:39:37  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/07 18:01:19  southa
 * MushModel and Infernal work
 *
 * Revision 1.2  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.1  2004/01/02 11:57:47  southa
 * Created
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/MushcoreSTL.h>
#elif defined(HAVE_MUSHCORE_H)
#include <MushcoreSTL.h>
#else
#include "Mushcore/MushcoreSTL.h"
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
