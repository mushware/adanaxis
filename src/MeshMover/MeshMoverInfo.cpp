//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverInfo.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } wI7Mmthp2jlPbJtXZQ2kuA
/*
 * $Id$
 * $Log$
 */

#include "MeshMoverInfo.h"

#ifndef PACKAGE
#define PACKAGE "meshmover"
#endif

#ifndef VERSION
#define VERSION "0.0.1"
#endif

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller MeshMoverInfoInstaller(MeshMoverInfo::Install);

string
MeshMoverInfo::ApplicationNameGet(void)
{
    return "MeshMover";
}

string
MeshMoverInfo::PackageNameGet(void)
{
    return PACKAGE;
}

string
MeshMoverInfo::PackageVersionGet(void)
{
    return VERSION;
}

void
MeshMoverInfo::Install(void)
{
    MushcoreInfo::SingletonMutate(new MeshMoverInfo);
}
