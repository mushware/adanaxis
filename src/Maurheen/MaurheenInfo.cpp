//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenInfo.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } YeIvRCtm6IDhzU/9mSe72g
/*
 * $Id: MaurheenInfo.cpp,v 1.4 2004/01/06 20:46:52 southa Exp $
 * $Log: MaurheenInfo.cpp,v $
 */

#include "MaurheenInfo.h"

#ifndef PACKAGE
#define PACKAGE "maurheen"
#endif

#ifndef VERSION
#define VERSION "0.0.1"
#endif

#include "MaurheenSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller MaurheenInfoInstaller(MaurheenInfo::Install);

string
MaurheenInfo::ApplicationNameGet(void)
{
    return "Maurheen";
}

string
MaurheenInfo::PackageNameGet(void)
{
    return PACKAGE;
}

string
MaurheenInfo::PackageVersionGet(void)
{
    return VERSION;
}

void
MaurheenInfo::Install(void)
{
}
