/*
 * $Id: GameInfo.cpp,v 1.1 2003/03/11 22:15:09 southa Exp $
 * $Log: GameInfo.cpp,v $
 * Revision 1.1  2003/03/11 22:15:09  southa
 * Added GameInfo
 *
 */

#include "GameInfo.h"

#ifndef PACKAGE
#define PACKAGE "ic2"
#endif

#ifndef VERSION
#define VERSION "0.1.1"
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
