#ifndef CORECHILDRECORD_H
#define CORECHILDRECORD_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: CoreChildRecord.h,v 1.4 2002/08/27 08:56:16 southa Exp $
 * $Log: CoreChildRecord.h,v $
 * Revision 1.4  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.2  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 09:20:46  southa
 * Name changed to CoreChildRecord
 *
 * Revision 1.2  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "CoreStandard.h"

class CoreChildStatus
{
public:
    bool Exited(void) {return m_exited;}
    bool Signalled(void) {return m_signalled;}
    bool Dead(void) {return m_exited || m_signalled;}
    int ReturnCode(void) {return m_returnCode;}
    void Set(bool inExited, bool inSignalled, int inReturnCode)
        {m_exited=inExited; m_signalled=inSignalled; m_returnCode=inReturnCode;}
    
private:
    bool m_exited;
    bool m_signalled;
    int m_returnCode;
};

inline ostream& operator<<(ostream &s, CoreChildStatus cs)
{
    return s << "exited=" << cs.Exited() << ", " <<
    "signalled=" << cs.Signalled() << ", " <<
    "dead=" << cs.Dead() << ", " <<
    "returncode=" << cs.ReturnCode();
}

class CoreChildRecord
{
public:
    CoreChildRecord(int inPid, int inInPipe, int inOutPipe);
    bool StatusGet(CoreChildStatus& outStatus);
    bool OutputAppend(string &outStr);

private:
    int m_pid;
    int m_inPipe;
    int m_outPipe;
};
#endif
