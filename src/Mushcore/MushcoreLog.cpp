//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreLog.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } QzCSzO8xeorzgPZAxeLVvw
/*
 * $Id$
 * $Log$
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

