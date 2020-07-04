//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisInfo.cpp
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
//%Header } aDpQ/gc4beLM18X5i3aMTg
/*
 * $Id: AdanaxisInfo.cpp,v 1.15 2007/06/27 12:58:22 southa Exp $
 * $Log: AdanaxisInfo.cpp,v $
 * Revision 1.15  2007/06/27 12:58:22  southa
 * Debian packaging
 *
 * Revision 1.14  2007/06/16 11:09:32  southa
 * Prerelease
 *
 * Revision 1.13  2007/06/16 07:13:40  southa
 * Licence corrections
 *
 * Revision 1.12  2007/06/15 12:45:49  southa
 * Prerelease work
 *
 * Revision 1.11  2007/06/11 20:06:14  southa
 * Compatibility fixes and level 27
 *
 * Revision 1.10  2007/06/02 15:56:58  southa
 * Shader fix and prerelease work
 *
 * Revision 1.9  2007/04/18 09:22:00  southa
 * Header and level fixes
 *
 * Revision 1.8  2007/04/16 08:41:08  southa
 * Level and header mods
 *
 * Revision 1.7  2007/03/13 22:56:47  southa
 * Release work
 *
 * Revision 1.6  2006/10/02 17:25:04  southa
 * Object lookup and target selection
 *
 * Revision 1.5  2006/08/01 13:41:15  southa
 * Pre-release updates
 *
 * Revision 1.4  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.2  2005/06/14 13:25:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisInfo.h"

#ifndef PACKAGE
#define PACKAGE "adanaxis"
#endif

#ifndef VERSION
#define VERSION "0.0.0.0"
#endif

#include "AdanaxisSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller AdanaxisInfoInstaller(AdanaxisInfo::Install);

string
AdanaxisInfo::ApplicationNameGet(void)
{
    return "Adanaxis";
}

string
AdanaxisInfo::PackageNameGet(void)
{
    return PACKAGE;
}

string
AdanaxisInfo::PackageVersionGet(void)
{
    return VERSION;
}

void
AdanaxisInfo::Install(void)
{
}
