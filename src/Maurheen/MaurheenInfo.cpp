//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenInfo.cpp
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
//%Header } 1DKa8rq5Cgi5glC09HJq/Q
/*
 * $Id: MaurheenInfo.cpp,v 1.2 2005/05/19 13:02:07 southa Exp $
 * $Log: MaurheenInfo.cpp,v $
 * Revision 1.2  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.1  2004/03/06 14:01:42  southa
 * Maurheen created
 *
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
