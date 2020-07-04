//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalInfo.cpp
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
//%Header } lsSFO/cH/zLeY6adsJ0+yg
/*
 * $Id: InfernalInfo.cpp,v 1.7 2006/06/01 15:39:03 southa Exp $
 * $Log: InfernalInfo.cpp,v $
 * Revision 1.7  2006/06/01 15:39:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.4  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.3  2004/01/01 21:15:46  southa
 * Created XCode project
 *
 * Revision 1.2  2003/10/04 12:44:35  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:05  southa
 * File renaming
 *
 * Revision 1.4  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:08:47  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.1  2003/03/11 22:15:09  southa
 * Added InfernalInfo
 *
 */

#include "InfernalInfo.h"

#ifndef PACKAGE
#define PACKAGE "ic2"
#endif

#ifndef VERSION
#define VERSION "0.1.2"
#endif

#include "InfernalSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(InfernalInfo);

MushcoreInstaller GameInfoInstaller(InfernalInfo::Install);

string
InfernalInfo::ApplicationNameGet(void)
{
    return "Infernal Contractor II";
}

string
InfernalInfo::PackageNameGet(void)
{
    return PACKAGE;
}

string
InfernalInfo::PackageVersionGet(void)
{
    return VERSION;
}

void
InfernalInfo::Install(void)
{
}
