/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameInfo.cpp,v 1.2 2003/04/06 12:35:23 southa Exp $
 * $Log: GameInfo.cpp,v $
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
