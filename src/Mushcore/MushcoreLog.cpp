//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreLog.cpp
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
//%Header } S1ShkioeDeCMuA2XF/bV/g
/*
 * $Id: MushcoreLog.cpp,v 1.1 2005/01/29 18:27:31 southa Exp $
 * $Log: MushcoreLog.cpp,v $
 * Revision 1.1  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
 */

#include "MushcoreLog.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushcoreLog);

MushcoreLog::MushcoreLog() :
m_outStream(NULL),
m_infoLog(true)
{
    m_nullStream = new ostringstream;
}

MushcoreLog::~MushcoreLog()
{
    if (m_outStream != NULL) delete m_outStream;
    delete m_nullStream;
}

ostream&
MushcoreLog::Log(void)
{
    ostream *retStream;
    if (m_outStream == NULL)
    {
        retStream = &std::cout;
    }
    else
    {
        retStream = m_outStream;
    }
    return *retStream;
}

ostream&
MushcoreLog::InfoLog(void)
{
    if (m_infoLog)
    {
        return Log();
    }
    else
    {
        m_nullStream->clear();
        return *m_nullStream;
    }
}

