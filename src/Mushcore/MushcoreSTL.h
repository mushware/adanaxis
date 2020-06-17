//%includeGuardStart {
#ifndef MUSHCORESTL_H
#define MUSHCORESTL_H
//%includeGuardStart } Hds411lfFyYAb5qD0dZRlA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreSTL.h
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
//%Header } 6fxH9uPdcztGDO2bpX1zTw
/*
 * $Id: MushcoreSTL.h,v 1.9 2006/06/01 15:39:47 southa Exp $
 * $Log: MushcoreSTL.h,v $
 * Revision 1.9  2006/06/01 15:39:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:16  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.6  2004/01/01 21:15:46  southa
 * Created XCode project
 *
 * Revision 1.5  2003/10/06 22:50:02  southa
 * Added M_PI
 *
 * Revision 1.4  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:16  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/13 14:32:02  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.1  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 */

#include "MushcoreStandard.h"

// General purpose includes used by most files
#include <fstream>
#include <iomanip>
#include <iostream>

#ifdef MIMIC_SSTREAM
#include "sstream"
#else
#include <sstream>
#endif

#include <typeinfo>

#include <cerrno>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
