//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisInfo.cpp
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } gLnaIsWRWcFfwxhJ8tzlTg
/*
 * $Id: AdanaxisInfo.cpp,v 1.2 2005/06/14 13:25:33 southa Exp $
 * $Log: AdanaxisInfo.cpp,v $
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
#define VERSION "0.0.1"
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
