/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MushcoreChildRecord.cpp,v 1.1 2003/01/09 14:57:06 southa Exp $
 * $Log: MushcoreChildRecord.cpp,v $
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.6  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.2  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 09:20:46  southa
 * Name changed to MushcoreChildRecord
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

#include "MushcoreChildRecord.h"
#include "MushcorePOSIX.h"

using namespace Mushware;
using namespace std;

MushcoreChildRecord::MushcoreChildRecord(int inPid, int inInPipe, int inOutPipe)
{
    m_pid = inPid;
    m_inPipe = inInPipe;
    m_outPipe = inOutPipe;
}

bool
MushcoreChildRecord::StatusGet(MushcoreChildStatus &outStatus)
{
#ifdef HAVE_POSIX
    int status=0;
    int rc=waitpid(m_pid, &status, WNOHANG);
    outStatus.Set(WIFEXITED(status), WIFSIGNALED(status), WEXITSTATUS(status));
    return (rc > 0);
#endif
}

bool
MushcoreChildRecord::OutputAppend(string &outStr)
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
