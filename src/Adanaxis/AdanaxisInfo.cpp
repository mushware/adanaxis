//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisInfo.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } dNl5b1jvSO1JXx9Bo8kgEw
/*
 * $Id: AdanaxisInfo.cpp,v 1.11 2007/06/11 20:06:14 southa Exp $
 * $Log: AdanaxisInfo.cpp,v $
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
#define VERSION "1.0.0"
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
