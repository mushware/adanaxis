#ifndef MUSHCOREINFO_H
#define MUSHCOREINFO_H
#ifndef COREINFO_H
#define COREINFO_H
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
 * $Id: MushcoreInfo.h,v 1.4 2002/12/29 20:30:51 southa Exp $
 * $Log: MushcoreInfo.h,v $
 * Revision 1.4  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.3  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/11/15 18:58:33  southa
 * Configuration mode
 *
 * Revision 1.1  2002/11/14 17:29:08  southa
 * Config database
 *
 */

#include "MushcoreStandard.h"

class MushcoreInfo
{
public:
    static std::string ApplicationNameGet(void) { return "Infernal Contractor II"; }
    static std::string PackageNameGet(void) { return "ic2"; }
    static std::string PackageVersionGet(void) { return "0.1.0"; }
    static std::string PackageIDGet(void) { return "ic2-macosx-0.1.0"; }
};
#endif
#endif
