//%includeGuardStart {
#ifndef MUSTLSTANDARD_H
#define MUSTLSTANDARD_H
//%includeGuardStart } et2J+l7uTDJO7v1niqd5zA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlStandard.h
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
//%Header } JfytyjDsrtSJUXbXSbTPtw
/*
 * $Id: MustlStandard.h,v 1.14 2006/06/22 19:07:37 southa Exp $
 * $Log: MustlStandard.h,v $
 * Revision 1.14  2006/06/22 19:07:37  southa
 * Build fixes
 *
 * Revision 1.13  2006/06/01 15:39:54  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.11  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.10  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:09:31  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.7  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.6  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.5  2003/01/17 00:41:05  southa
 * Configuration updates from POST data
 *
 * Revision 1.4  2003/01/13 15:01:20  southa
 * Fix Mustl command line build
 *
 * Revision 1.3  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/13 01:06:54  southa
 * Mustl work
 *
 * Revision 1.1  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#include <iosfwd>
#include <list>
#include <map>
#include <string>
#include <vector>


namespace Mustl
{
    typedef int tSocket;
    typedef float tVal;
    typedef double tLongVal;
    typedef signed int S32;
    typedef unsigned int U32;
    typedef signed short S16;
    typedef unsigned short U16;
    typedef signed char S8;
    typedef unsigned char U8;
    typedef double tMsec;
};

#define MUSTL_DECLARE_INLINE inline

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
