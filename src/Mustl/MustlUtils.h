#ifndef MUSTLUTILS_H
#define MUSTLUTILS_H
/*
 * $Id: MustlUtils.h,v 1.2 2002/12/13 19:03:06 southa Exp $
 * $Log: MustlUtils.h,v $
 * Revision 1.2  2002/12/13 19:03:06  southa
 * Mustl interface cleanup
 *
 * Revision 1.1  2002/12/12 14:00:27  southa
 * Created Mustl
 *
 * Revision 1.11  2002/12/05 13:20:13  southa
 * Client link handling
 *
 * Revision 1.10  2002/11/28 18:05:36  southa
 * Print link ages
 *
 * Revision 1.9  2002/11/27 13:23:27  southa
 * Server and client data exchange
 *
 * Revision 1.8  2002/11/25 18:02:57  southa
 * Mushware ID work
 *
 * Revision 1.7  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.6  2002/11/22 15:00:33  southa
 * Network connection handling
 *
 * Revision 1.5  2002/11/21 18:06:18  southa
 * Non-blocking network connection
 *
 * Revision 1.4  2002/11/15 11:47:55  southa
 * Web processing and error handling
 *
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

#include "MustlStandard.h"

class MustlAddress;
class MustlLink;

class MustlUtils
{
public:
    static bool FindLinkToStation(MustlLink *& outLink, const MustlAddress& inAddress);
    static bool FindLinkToStation(string& outName, const MustlAddress& inAddress);
    static string IPAddressToString(Mustl::U32 inAddress);
    static string IPAddressToLogString(Mustl::U32 inAddress);
    static string MsecDurationToString(Mustl::U32 inMsec);
    static string MakePrintable(const string& inStr);
    static string MakePrintable(const vector<Mustl::U8> inBytes);
    static string MakeXMLSafe(const string& inStr);
    static string MakeWebSafe(const string& inStr);
    static Mustl::U32 MakeWebSafe(Mustl::U32 inValue) { return inValue; }
    static string RemoveMeta(const string& inStr);
    static void TruncateLogSet(bool inTruncate) { m_truncateLog=inTruncate; }
    
private:
    static bool m_truncateLog;
};
#endif
