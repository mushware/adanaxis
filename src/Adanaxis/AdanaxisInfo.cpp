//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisInfo.cpp
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
//%Header } mRnLg4yJPsIv76AzbJAdXQ
/*
 * $Id: AdanaxisInfo.cpp,v 1.6 2005/06/08 20:59:52 southa Exp $
 * $Log: AdanaxisInfo.cpp,v $
 */

#include "AdanaxisInfo.h"

#ifndef PACKAGE
#define PACKAGE "adanaxis"
#endif

#ifndef VERSION
#define VERSION "0.1.3"
#endif

#include "AdanaxisSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller AdanaxisInfoInstaller(AdanaxisInfo::Install);

string
AdanaxisInfo::ApplicationNameGet(void)
{
    return "Adanaxis";
}

string
AdanaxisInfo::PackageNameGet(void)
{
    return PACKAGE;
}

string
AdanaxisInfo::PackageVersionGet(void)
{
    return VERSION;
}

void
AdanaxisInfo::Install(void)
{
}
