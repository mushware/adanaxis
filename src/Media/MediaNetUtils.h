/*
 * $Id: MediaNetUtils.h,v 1.1 2002/11/03 18:43:09 southa Exp $
 * $Log: MediaNetUtils.h,v $
 * Revision 1.1  2002/11/03 18:43:09  southa
 * Network fixes
 *
 */

#include "mushCore.h"

class MediaNetUtils
{
public:
    static string IPAddressToString(U32 inAddress);
    static string MakePrintable(const string& inStr);
};
