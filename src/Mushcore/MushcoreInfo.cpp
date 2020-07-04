//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreInfo.cpp
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
//%Header } AryaiV4fSY1GLGAXWhsKkg
/*
 * $Id: MushcoreInfo.cpp,v 1.10 2006/06/01 15:39:44 southa Exp $
 * $Log: MushcoreInfo.cpp,v $
 * Revision 1.10  2006/06/01 15:39:44  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:13  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.4  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.3  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.2  2003/01/11 17:44:27  southa
 * Mushcore fixes
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.3  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.2  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/11/14 17:29:07  southa
 * Config database
 *
 */

#include "MushcoreInfo.h"

#ifndef PACKAGE
#define PACKAGE "unknown"
#endif

#ifndef VERSION
#define VERSION "0.0.0"
#endif

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushcoreInfo);

string
MushcoreInfo::PlatformNameGet(void)
{
#if defined(WIN32) || defined(_WIN32)
    return "win32";
#else
#if defined(__APPLE__) || defined(MACOSX)
    return "macosx";
#else
    return "x11";
#endif
#endif
}

string
MushcoreInfo::ApplicationNameGet(void)
{
    return PackageNameGet()+" "+PackageVersionGet();
}

string
MushcoreInfo::PackageNameGet(void)
{
    return PACKAGE;
}

string
MushcoreInfo::PackageVersionGet(void)
{
    return VERSION;
}

string
MushcoreInfo::PackageIDGet(void)
{
    return PackageNameGet()+"-"+PlatformNameGet()+"-"+PackageVersionGet();
}
