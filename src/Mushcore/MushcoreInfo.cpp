/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MushcoreInfo.cpp,v 1.3 2003/01/12 17:33:00 southa Exp $
 * $Log: MushcoreInfo.cpp,v $
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
    return PackageNameGet()+"-"+PackageVersionGet();
}
