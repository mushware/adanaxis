//%includeGuardStart {
#ifndef MUSTLLOG_H
#define MUSTLLOG_H
//%includeGuardStart } O6haGWPxiYSQQC8dveJ07g
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlLog.h
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
//%Header } tyv/MXD0qOpieDe9GS1zDg
/*
 * $Id: MustlLog.h,v 1.14 2006/06/01 15:39:53 southa Exp $
 * $Log: MustlLog.h,v $
 * Revision 1.14  2006/06/01 15:39:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.13  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.12  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.11  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:09:27  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/01/20 10:45:30  southa
 * Singleton tidying
 *
 * Revision 1.8  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.7  2003/01/17 00:41:04  southa
 * Configuration updates from POST data
 *
 * Revision 1.6  2003/01/07 17:13:45  southa
 * Fixes for gcc 3.1
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
 * Revision 1.2  2002/12/14 15:04:34  southa
 * Mustl fixes
 *
 * Revision 1.1  2002/12/12 14:00:26  southa
 * Created Mustl
 *
 * Revision 1.6  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.5  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.4  2002/11/21 18:06:18  southa
 * Non-blocking network connection
 *
 * Revision 1.3  2002/11/08 11:54:40  southa
 * Web fixes
 *
 * Revision 1.2  2002/11/07 00:53:37  southa
 * localweb work
 *
 * Revision 1.1  2002/11/04 15:50:32  southa
 * Network log
 *
 */

#include "MustlStandard.h"

class MustlLog
{
public:
    MustlLog();
    ~MustlLog();

    static inline MustlLog& Sgl(void);

    std::ostream& WebLog(void);
    std::ostream& NetLog(void);
    std::ostream& VerboseLog(void);
    std::ostream& TrafficLog(void);
    bool LogFullIPGet(void) const { return m_logFullIP; }

    bool NetLogGet(void) const { return m_netLog; }
    void NetLogSet(bool inLog) { m_netLog = inLog; }
    bool WebLogGet(void) const { return m_webLog; }
    void WebLogSet(bool inLog) { m_webLog = inLog; }
    bool VerboseLogGet(void) const { return m_verboseLog; }
    void VerboseLogSet(bool inLog) { m_verboseLog = inLog; }
    bool TrafficLogGet(void) const { return m_trafficLog; }
    void TrafficLogSet(bool inLog) { m_trafficLog = inLog; }
    void LogFullIPSet(bool inFullIP) { m_logFullIP = inFullIP; }
    
    void OpenFile(const std::string& inName);
    void CloseFile(void);

    static void LogString(const std::string& inStr);
    static void UpdateHandler(void);
    static void Install(void);
    static void NullFunction(void);
    
protected:
    std::ostream& Log(void);

private:
    std::ofstream *m_outStream;
    std::ostream *m_nullStream;
    bool m_netLog;
    bool m_webLog;
    bool m_verboseLog;
    bool m_trafficLog;
    bool m_logFullIP;

    static MustlLog m_gMustlLogInstance;
};

inline MustlLog&
MustlLog::Sgl(void)
{
    return m_gMustlLogInstance;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
