//%includeGuardStart {
#ifndef MEDIASTL_H
#define MEDIASTL_H
//%includeGuardStart } 49s9eOqW2RTUoIsat9M5Ew
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaSTL.h
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
//%Header } tgMgKtFEazSsQIJI1DYDJQ
/*
 * $Id: MediaSTL.h,v 1.8 2006/06/22 19:07:31 southa Exp $
 * $Log: MediaSTL.h,v $
 * Revision 1.8  2006/06/22 19:07:31  southa
 * Build fixes
 *
 * Revision 1.7  2006/06/01 15:39:14  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.4  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.3  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:02  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/13 15:01:19  southa
 * Fix Mustl command line build
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORESTL_H)
#include <Mushcore/MushcoreSTL.h>
#else
#if defined(HAVE_MUSHCORESTL_H)
#include <MushcoreSTL.h>
#else
#include "Mushcore/MushcoreSTL.h"
#endif
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
