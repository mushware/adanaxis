/*
 * $Id$
 * $Log$
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

string
GameInfo::PackageIDGet(void)
{
    return PackageNameGet()+"-"+PackageVersionGet();
}

void
GameInfo::Install(void)
{
   MushcoreInfo::SingletonMutate(new GameInfo);
}
