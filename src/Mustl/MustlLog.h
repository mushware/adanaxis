//%includeGuardStart {
#ifndef MUSTLLOG_H
#define MUSTLLOG_H
//%includeGuardStart } O6haGWPxiYSQQC8dveJ07g
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlLog.h
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } kn0WUen9FgYIsyUwEWj15w
/*
 * $Id: MustlLog.h,v 1.10 2003/08/21 23:09:27 southa Exp $
 * $Log: MustlLog.h,v $
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
