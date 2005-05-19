//%includeGuardStart {
#ifndef MUSHCORELOG_H
#define MUSHCORELOG_H
//%includeGuardStart } Lz/+CPk+eWXGveU5A8W9jw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreLog.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } Bq8XxaaUUfoNxs2oOiSOLA
/*
 * $Id: MushcoreLog.h,v 1.1 2005/01/29 18:27:31 southa Exp $
 * $Log: MushcoreLog.h,v $
 * Revision 1.1  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreSingleton.h"

class MushcoreLog : public MushcoreSingleton<MushcoreLog>
{
public:
    MushcoreLog();
    ~MushcoreLog();
    
    std::ostream& InfoLog(void);
    
    bool InfoLog(void) const { return m_infoLog; }
    void InfoLogSet(bool inLog) { m_infoLog = inLog; }
    
    void OpenFile(const std::string& inName);
    void CloseFile(void);
    
protected:
    std::ostream& Log(void);
    
private:
    std::ofstream *m_outStream;
    std::ostream *m_nullStream;
    bool m_infoLog;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
