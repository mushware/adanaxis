/*
 * $Id: ChildRecord.h,v 1.2 2002/05/09 17:10:38 southa Exp $
 * $Log: ChildRecord.h,v $
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "CoreStandard.h"
using namespace std;

class ChildStatus
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

inline ostream& operator<<(ostream &s, ChildStatus cs)
{
    return s << "exited=" << cs.Exited() << ", " <<
    "signalled=" << cs.Signalled() << ", " <<
    "dead=" << cs.Dead() << ", " <<
    "returncode=" << cs.ReturnCode();
}

class ChildRecord
{
public:
    ChildRecord(int inPid, int inInPipe, int inOutPipe);
    bool StatusGet(ChildStatus& outStatus);
    bool OutputAppend(string &outStr);

private:
    int m_pid;
    int m_inPipe;
    int m_outPipe;
};