#ifndef MUSHCORECHILDRECORD_H
#define MUSHCORECHILDRECORD_H
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
 * $Id: MushcoreChildRecord.h,v 1.2 2003/01/11 13:03:16 southa Exp $
 * $Log: MushcoreChildRecord.h,v $
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
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
 * Revision 1.3  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.2  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 09:20:46  southa
 * Name changed to MushcoreChildRecord
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

#include "MushcoreStandard.h"

class MushcoreChildStatus
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

inline std::ostream& operator<<(std::ostream &s, MushcoreChildStatus cs)
{
    return s << "exited=" << cs.Exited() << ", " <<
    "signalled=" << cs.Signalled() << ", " <<
    "dead=" << cs.Dead() << ", " <<
    "returncode=" << cs.ReturnCode();
}

class MushcoreChildRecord
{
public:
    MushcoreChildRecord(int inPid, int inInPipe, int inOutPipe);
    bool StatusGet(MushcoreChildStatus& outStatus);
    bool OutputAppend(std::string &outStr);

private:
    int m_pid;
    int m_inPipe;
    int m_outPipe;
};
#endif
