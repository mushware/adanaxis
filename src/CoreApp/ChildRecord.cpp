/*
 * $Id: ChildRecord.cpp,v 1.1.1.1 2002/02/11 22:30:08 southa Exp $
 * $Log: ChildRecord.cpp,v $
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "ChildRecord.h"
#include "CorePOSIX.h"

ChildRecord::ChildRecord(int inPid, int inInPipe, int inOutPipe)
{
    m_pid = inPid;
    m_inPipe = inInPipe;
    m_outPipe = inOutPipe;
}

bool
ChildRecord::StatusGet(ChildStatus &outStatus)
{
    int status=0;
    int rc=waitpid(m_pid, &status, WNOHANG);
    outStatus.Set(WIFEXITED(status), WIFSIGNALED(status), WEXITSTATUS(status));
    return (rc > 0);
}

bool
ChildRecord::OutputAppend(string &outStr)
{
    int result;
    bool wasOutput=false;
    char buf[256];
    errno=0;
    while (result=read(m_inPipe, buf, sizeof(buf)), result > 0)
    {
        outStr.append(buf, result);
        wasOutput=true;
    }
    if (result < 0)
    {
        cerr << "Read from pipe failed: " << strerror(errno) << endl;
    }
    return wasOutput;
}