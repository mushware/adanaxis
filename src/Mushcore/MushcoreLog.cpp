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
 * $Id: MushcoreLog.cpp,v 1.2 2005/05/19 13:02:15 southa Exp $
 * $Log: MushcoreLog.cpp,v $
 * Revision 1.2  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.1  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
 */

#include "MushcoreLog.h"

#include "MushcoreInfo.h"
#include "MushcoreSTL.h"
#include "MushcoreUtil.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushcoreLog);

MushcoreLog::MushcoreLog() :
    m_errorStream(NULL),
    m_stdStream(NULL),
    m_enableErrorLog(true),
    m_enableInfoLog(true),
    m_errorHeaderDone(false),
    m_stdHeaderDone(false)
{
    m_nullStream = new ostringstream;
}

MushcoreLog::~MushcoreLog()
{
    delete m_nullStream;
}

void
MushcoreLog::HeaderWrite(ostream& ioOut, const std::string inLogName)
{
    ioOut << MushcoreUtil::LogTimeString() << ": Package " << MushcoreInfo::Sgl().PackageID() << " " << inLogName << endl;
}

void
MushcoreLog::PackageHasChanged(void)
{
    m_errorHeaderDone = false;
    m_stdHeaderDone = false;
}

ostream&
MushcoreLog::ErrorStream(void)
{
    ostream *retStream;
    if (m_errorStream == NULL)
    {
        retStream = &std::cerr;
    }
    else
    {
        retStream = m_errorStream;
    }
    if (!m_errorHeaderDone)
    {
        HeaderWrite(*retStream, "error log");
        m_errorHeaderDone = true;
    }
    *retStream << MushcoreUtil::LogTimeString() << ": Error: ";
    return *retStream;
}

ostream&
MushcoreLog::StdStream(void)
{
    ostream *retStream;
    if (m_stdStream == NULL)
    {
        retStream = &std::cout;
    }
    else
    {
        retStream = m_stdStream;
    }
    if (!m_stdHeaderDone)
    {
        HeaderWrite(*retStream, "standard log");
        m_stdHeaderDone = true;
    }
    *retStream << MushcoreUtil::LogTimeString() << ": Info: ";
    return *retStream;
}

ostream&
MushcoreLog::ErrorLog(void)
{
    if (m_enableErrorLog)
    {
        return ErrorStream();
    }
    else
    {
        m_nullStream->clear();
        return *m_nullStream;
    }
}

ostream&
MushcoreLog::InfoLog(void)
{
    if (m_enableInfoLog)
    {
        return StdStream();
    }
    else
    {
        m_nullStream->clear();
        return *m_nullStream;
    }
}


