/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: CoreChildRecord.cpp,v 1.1 2002/07/02 09:20:46 southa Exp $
 * $Log: CoreChildRecord.cpp,v $
 * Revision 1.1  2002/07/02 09:20:46  southa
 * Name changed to CoreChildRecord
 *
 * Revision 1.5  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.4  2002/06/27 00:07:06  southa
 * Catch up
 *
 * Revision 1.3  2002/06/24 16:41:13  southa
 * Fixed for mingw32
 *
 * Revision 1.2  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "CoreChildRecord.h"
#include "CorePOSIX.h"

CoreChildRecord::CoreChildRecord(int inPid, int inInPipe, int inOutPipe)
{
    m_pid = inPid;
    m_inPipe = inInPipe;
    m_outPipe = inOutPipe;
}

bool
CoreChildRecord::StatusGet(CoreChildStatus &outStatus)
{
#ifdef HAVE_POSIX
    int status=0;
    int rc=waitpid(m_pid, &status, WNOHANG);
    outStatus.Set(WIFEXITED(status), WIFSIGNALED(status), WEXITSTATUS(status));
    return (rc > 0);
#endif
}

bool
CoreChildRecord::OutputAppend(string &outStr)
{
#ifdef HAVE_POSIX
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
#endif
}
