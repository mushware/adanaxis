//%includeGuardStart {
#ifndef MUSTLUTILS_H
#define MUSTLUTILS_H
//%includeGuardStart } rT8NVuKBLKxpFsv/Vs6yhg
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlUtils.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } taJKKmpz0oYiqfKWmLvJJA
/*
 * $Id: MustlUtils.h,v 1.12 2006/06/01 15:39:55 southa Exp $
 * $Log: MustlUtils.h,v $
 * Revision 1.12  2006/06/01 15:39:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.10  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.9  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:09:32  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/05/21 19:01:40  southa
 * Prerelease tweaks
 *
 * Revision 1.6  2003/01/14 12:40:11  southa
 * Moved ConfigDefs into Mustl
 *
 * Revision 1.5  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/17 12:53:34  southa
 * Mustl library
 *
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
    static bool FindLinkToStation(std::string& outName, const MustlAddress& inAddress);
    static std::string IPAddressToString(Mustl::U32 inAddress);
    static std::string IPAddressToLogString(Mustl::U32 inAddress);
    static std::string MsecDurationToString(Mustl::U32 inMsec);
    static std::string MakePrintable(const std::string& inStr);
    static std::string MakePrintable(const std::vector<Mustl::U8> inBytes);
    static std::string MakeXMLSafe(const std::string& inStr);
    static std::string MakeWebSafe(const std::string& inStr);
    static Mustl::U32 MakeWebSafe(Mustl::U32 inValue) { return inValue; }
    static Mustl::tVal MakeWebSafe(Mustl::tVal inValue) { return inValue; }
    static std::string RemoveMeta(const std::string& inStr);
    static std::string InsertMeta(const std::string& inStr);
    static void TruncateLogSet(bool inTruncate) { m_truncateLog=inTruncate; }
    
private:
    static bool m_truncateLog;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
