/*
 * $Id: MediaNetUtils.h,v 1.3 2002/11/08 11:54:40 southa Exp $
 * $Log: MediaNetUtils.h,v $
 * Revision 1.3  2002/11/08 11:54:40  southa
 * Web fixes
 *
 * Revision 1.2  2002/11/04 19:34:47  southa
 * Network link maintenance
 *
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
    static string MakePrintable(const vector<U8> inBytes);
    static string MakeWebSafe(const string& inStr);
    static U32 MakeWebSafe(U32 inValue) { return inValue; }
    static string RemoveMeta(const string& inStr);    
};