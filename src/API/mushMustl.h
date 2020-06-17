//%includeGuardStart {
#ifndef MUSHMUSTL_H
#define MUSHMUSTL_H
//%includeGuardStart } KBVRriTEzxvrJPJCRBYpXg
//%Header {
/*****************************************************************************
 *
 * File: src/API/mushMustl.h
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
//%Header } LZIji7MEV4YSkqIHyus4cA
/*
 * $Id: mushMustl.h,v 1.5 2006/06/22 19:07:28 southa Exp $
 * $Log: mushMustl.h,v $
 * Revision 1.5  2006/06/22 19:07:28  southa
 * Build fixes
 *
 * Revision 1.4  2006/06/01 15:38:46  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/06/14 13:25:32  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/05/19 13:01:57  southa
 * Mac release work
 *
 * Revision 1.1  2004/01/06 20:46:49  southa
 * Build fixes
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(HAVE_MUSTL_MUSTL_H)
#include <Mustl/Mustl.h>
#elif defined(HAVE_MUSTL_H)
#include <Mustl.h>
#else
#include "Mustl/Mustl.h"
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
