/*
 * $Id: CoreInfo.h,v 1.1 2002/11/14 17:29:08 southa Exp $
 * $Log: CoreInfo.h,v $
 * Revision 1.1  2002/11/14 17:29:08  southa
 * Config database
 *
 */

#include "CoreStandard.h"

class CoreInfo
{
public:
    static string ApplicationNameGet(void) { return "Infernal Contractor II"; }
    static string PackageNameGet(void) { return "ic2"; }
    static string PackageVersionGet(void) { return "0.1.0"; }
    static string PackageIDGet(void) { return "ic2-macosx-0.1.0"; }
};
