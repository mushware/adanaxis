#ifndef MUSTLLOG_H
#define MUSTLLOG_H
/*
 * $Id: MustlLog.h,v 1.6 2002/11/25 10:43:28 southa Exp $
 * $Log: MustlLog.h,v $
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

#include "mushCore.h"

class MustlLog
{
public:
    MustlLog();
    ~MustlLog();

    static inline MustlLog& Instance(void);

    ostream& WebLog(void);
    ostream& NetLog(void);
    ostream& VerboseLog(void);
    bool LogFullIPGet(void) const { return m_logFullIP; }

    void NetLogSet(bool inLog) { m_netLog = inLog; }
    void WebLogSet(bool inLog) { m_webLog = inLog; }
    void VerboseLogSet(bool inLog) { m_verboseLog = inLog; }
    void LogFullIPSet(bool inFullIP) { m_logFullIP = inFullIP; }
    
    void OpenFile(const string& inName);
    void CloseFile(void);
    
    
protected:
    ostream& Log(void);

private:
    ofstream *m_outStream;
    ostringstream m_nullStream;
    bool m_netLog;
    bool m_webLog;
    bool m_verboseLog;
    bool m_logFullIP;

    static MustlLog m_gMustlLogInstance;
};

inline MustlLog&
MustlLog::Instance(void)
{
    return m_gMustlLogInstance;
}
#endif
