//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalInfo.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 5zJGPs3Q4Kr0fA/Rcp9t6g
/*
 * $Id: InfernalInfo.cpp,v 1.4 2004/01/02 21:13:08 southa Exp $
 * $Log: InfernalInfo.cpp,v $
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
