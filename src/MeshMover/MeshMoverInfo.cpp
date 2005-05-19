//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverInfo.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } Za6fDimTTg9RSZdgkZIdvA
/*
 * $Id: MeshMoverInfo.cpp,v 1.4 2004/01/06 20:46:52 southa Exp $
 * $Log: MeshMoverInfo.cpp,v $
 * Revision 1.4  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:10  southa
 * Source conditioning
 *
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

#include "MeshMoverSTL.h"

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
