//%includeGuardStart {
#ifndef MUSHCORELOG_H
#define MUSHCORELOG_H
//%includeGuardStart } Lz/+CPk+eWXGveU5A8W9jw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreLog.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } y6BGNOaAxSnAhyj4oJSyqQ
/*
 * $Id$
 * $Log$
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
