//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreInfo.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } AOIDXlsqqRSLMcBM0hkARw
/*
 * $Id: MushcoreInfo.cpp,v 1.7 2003/09/17 19:40:35 southa Exp $
 * $Log: MushcoreInfo.cpp,v $
 * Revision 1.7  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:13  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.4  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.3  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.2  2003/01/11 17:44:27  southa
 * Mushcore fixes
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.3  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.2  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/11/14 17:29:07  southa
 * Config database
 *
 */

#include "MushcoreInfo.h"

#ifndef PACKAGE
#define PACKAGE "unknown"
#endif

#ifndef VERSION
#define VERSION "0.0.0"
#endif

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushcoreInfo);

string
MushcoreInfo::PlatformNameGet(void)
{
#if defined(WIN32) || defined(_WIN32)
    return "win32";
#else
#if defined(__APPLE__) || defined(MACOSX)
    return "macosx";
#else
    return "x11";
#endif
#endif
}

string
MushcoreInfo::ApplicationNameGet(void)
{
    return PackageNameGet()+" "+PackageVersionGet();
}

string
MushcoreInfo::PackageNameGet(void)
{
    return PACKAGE;
}

string
MushcoreInfo::PackageVersionGet(void)
{
    return VERSION;
}

string
MushcoreInfo::PackageIDGet(void)
{
    return PackageNameGet()+"-"+PlatformNameGet()+"-"+PackageVersionGet();
}
