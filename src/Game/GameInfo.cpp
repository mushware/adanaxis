//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameInfo.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 4U+O0JZ5suGVD28zRN0UsQ
/*
 * $Id: GameInfo.cpp,v 1.3 2003/08/21 23:08:47 southa Exp $
 * $Log: GameInfo.cpp,v $
 * Revision 1.3  2003/08/21 23:08:47  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.1  2003/03/11 22:15:09  southa
 * Added GameInfo
 *
 */

#include "GameInfo.h"

#ifndef PACKAGE
#define PACKAGE "ic2"
#endif

#ifndef VERSION
#define VERSION "0.1.2"
#endif

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(GameInfo);

MushcoreInstaller GameInfoInstaller(GameInfo::Install);

string
GameInfo::ApplicationNameGet(void)
{
    return "Infernal Contractor II";
}

string
GameInfo::PackageNameGet(void)
{
    return PACKAGE;
}

string
GameInfo::PackageVersionGet(void)
{
    return VERSION;
}

void
GameInfo::Install(void)
{
   MushcoreInfo::SingletonMutate(new GameInfo);
}
