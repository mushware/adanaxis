//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalInfo.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } EOJCuJ1b/KV9aToD28LcXg
/*
 * $Id: InfernalInfo.cpp,v 1.6 2005/05/19 13:02:05 southa Exp $
 * $Log: InfernalInfo.cpp,v $
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
