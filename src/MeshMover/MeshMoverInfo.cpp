//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverInfo.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } T42nM9pNHXnlv6ZlPVHIcg
/*
 * $Id: MeshMoverInfo.cpp,v 1.2 2004/01/01 21:15:46 southa Exp $
 * $Log: MeshMoverInfo.cpp,v $
 * Revision 1.2  2004/01/01 21:15:46  southa
 * Created XCode project
 *
 * Revision 1.1  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
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
}
