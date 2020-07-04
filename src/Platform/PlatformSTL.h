//%includeGuardStart {
#ifndef PLATFORMSTL_H
#define PLATFORMSTL_H
//%includeGuardStart } c6BJvuqH/nmO1Ri2q+FOMg
//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformSTL.h
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
//%Header } ANPO2L/dIVw5RlGOuUyO3Q
/*
 * $Id: PlatformSTL.h,v 1.8 2006/06/22 19:07:37 southa Exp $
 * $Log: PlatformSTL.h,v $
 * Revision 1.8  2006/06/22 19:07:37  southa
 * Build fixes
 *
 * Revision 1.7  2006/06/01 15:39:57  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.4  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.3  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:34  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/13 14:32:03  southa
 * Build frameworks for Mac OS X
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
