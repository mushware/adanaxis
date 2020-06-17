//%includeGuardStart {
#ifndef TESTMUSTLSTANDARD_H
#define TESTMUSTLSTANDARD_H
//%includeGuardStart } 3eZYJcCuEjLA1xgox18STA
//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlStandard.h
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
//%Header } CwtPkkj2+NeNAs3UjD3AQw
/*
 * $Id: TestMustlStandard.h,v 1.8 2006/06/22 19:07:39 southa Exp $
 * $Log: TestMustlStandard.h,v $
 * Revision 1.8  2006/06/22 19:07:39  southa
 * Build fixes
 *
 * Revision 1.7  2006/06/01 15:40:06  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:25  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/07 11:14:15  southa
 * Snapshot fixes
 *
 * Revision 1.4  2004/01/02 21:13:18  southa
 * Source conditioning
 *
 * Revision 1.3  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:40  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 */

// Include everything we might need to keep things simple

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#include <list>
#include <map>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#include <fstream>
#include <iomanip>
#include <iostream>

#ifdef HAVE_SSTREAM
#include <sstream>
#else
#include "sstream"
#endif

#include <typeinfo>

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <ctime>

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#else
#include "Mushcore/Mushcore.h"
#endif
#endif

#if defined(HAVE_MUSTL_MUSTL_H)
#include <Mustl/Mustl.h>
#else
#if defined(HAVE_MUSTL_H)
#include <Mustl.h>
#else
#include "Mustl/Mustl.h"
#endif
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
