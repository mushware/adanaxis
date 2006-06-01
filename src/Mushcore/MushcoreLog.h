//%includeGuardStart {
#ifndef MUSHCORELOG_H
#define MUSHCORELOG_H
//%includeGuardStart } Lz/+CPk+eWXGveU5A8W9jw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreLog.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Ix2pcy9BwhW9V5JAps97Zw
/*
 * $Id: MushcoreLog.h,v 1.6 2005/07/29 08:27:47 southa Exp $
 * $Log: MushcoreLog.h,v $
 * Revision 1.6  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.5  2005/07/14 16:55:09  southa
 * Mesh library work
 *
 * Revision 1.4  2005/06/23 11:58:29  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/14 13:25:34  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/05/19 13:02:16  southa
 * Mac release work
 *
 * Revision 1.1  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreFail.h"
#include "MushcoreSingleton.h"
#include "MushcoreXMLOStream.h"

//:generate
class MushcoreLog : public MushcoreSingleton<MushcoreLog>
{
public:
    MushcoreLog();
    ~MushcoreLog();
    
    std::ostream& ErrorLog(void);
    std::ostream& WarningLog(void);
    std::ostream& InfoLog(void);
    MushcoreXMLOStream& XMLErrorLog(void);
    MushcoreXMLOStream& XMLWarningLog(void);
    MushcoreXMLOStream& XMLInfoLog(void);
    
    void HeaderWrite(std::ostream& ioOut, const std::string inLogName);
    void PackageHasChanged(void);
    
protected:
    std::ostream& ErrorStream(void);
    std::ostream& StdStream(void);
    MushcoreXMLOStream& XMLErrorStream(void);
    MushcoreXMLOStream& XMLStdStream(void);
    
private:
    MUSHCORE_NOCOPY(MushcoreLog);
    std::ofstream *m_errorStream;
    std::ofstream *m_stdStream;
    MushcoreXMLOStream *m_xmlErrorStream;
    MushcoreXMLOStream *m_xmlStdStream;
    
    std::ostream *m_nullStream;
    
    bool m_enableErrorLog; //:readwrite
    bool m_enableWarningLog; //:readwrite
    bool m_enableInfoLog; //:readwrite
    bool m_errorHeaderDone;
    bool m_stdHeaderDone;
//%classPrototypes {
public:
    const bool& EnableErrorLog(void) const { return m_enableErrorLog; }
    void EnableErrorLogSet(const bool& inValue) { m_enableErrorLog=inValue; }
    const bool& EnableWarningLog(void) const { return m_enableWarningLog; }
    void EnableWarningLogSet(const bool& inValue) { m_enableWarningLog=inValue; }
    const bool& EnableInfoLog(void) const { return m_enableInfoLog; }
    void EnableInfoLogSet(const bool& inValue) { m_enableInfoLog=inValue; }
//%classPrototypes } MZ4jgKhQvs0+TVUvwQK45Q
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
