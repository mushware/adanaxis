//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreLog.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } dbTHd+LeRoodIg9tkOmqTQ
/*
 * $Id: MushcoreLog.cpp,v 1.8 2006/08/02 15:41:47 southa Exp $
 * $Log: MushcoreLog.cpp,v $
 * Revision 1.8  2006/08/02 15:41:47  southa
 * Prerelease work
 *
 * Revision 1.7  2006/06/01 15:39:45  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/14 16:55:09  southa
 * Mesh library work
 *
 * Revision 1.5  2005/06/23 13:56:59  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/23 11:58:29  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/14 13:25:34  southa
 * Adanaxis work
 *
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
    m_xmlErrorStream(NULL),
    m_xmlStdStream(NULL),
    m_enableErrorLog(true),
#ifdef MUSHCORE_DEBUG
    m_enableWarningLog(true),
    m_enableInfoLog(true),
#else
    m_enableWarningLog(false),
    m_enableInfoLog(false),
#endif
    m_errorHeaderDone(false),
    m_stdHeaderDone(false)
{
    m_nullStream = new ostringstream;
}

MushcoreLog::~MushcoreLog()
{
    delete m_nullStream;
    delete m_xmlErrorStream;
    delete m_xmlStdStream;    
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
    return *retStream;
}

MushcoreXMLOStream&
MushcoreLog::XMLErrorStream(void)
{
    if (m_xmlErrorStream == NULL)
    {
        m_xmlErrorStream = new MushcoreXMLOStream(ErrorStream());
    }
    
    return *m_xmlErrorStream;
}

MushcoreXMLOStream&
MushcoreLog::XMLStdStream(void)
{
    if (m_xmlStdStream == NULL)
    {
        m_xmlStdStream = new MushcoreXMLOStream(StdStream());
    }
    
    return *m_xmlStdStream;
}

ostream&
MushcoreLog::ErrorLog(void)
{
    ostream *retStream;
    if (m_enableErrorLog)
    {
        retStream = &ErrorStream();
    }
    else
    {
        m_nullStream->clear();
        retStream = m_nullStream;
    }
    *retStream << MushcoreUtil::LogTimeString() << ": Error: ";
    return *retStream;
}

ostream&
MushcoreLog::WarningLog(void)
{
    ostream *retStream;
    if (m_enableWarningLog)
    {
        retStream = &ErrorStream();
    }
    else
    {
        m_nullStream->clear();
        retStream = m_nullStream;
    }
    *retStream << MushcoreUtil::LogTimeString() << ": Warning: ";
    return *retStream;
}

ostream&
MushcoreLog::InfoLog(void)
{
    ostream *retStream;
    if (m_enableInfoLog)
    {
        retStream = &StdStream();
    }
    else
    {
        m_nullStream->clear();
        retStream = m_nullStream;
    }
    *retStream << MushcoreUtil::LogTimeString() << ": Info: ";
    return *retStream;
}

MushcoreXMLOStream&
MushcoreLog::XMLErrorLog(void)
{
    MushcoreXMLOStream *retStream = &XMLErrorStream();
    retStream->OStream() << MushcoreUtil::LogTimeString() << ": Error: ";
    return *retStream;
}


MushcoreXMLOStream&
MushcoreLog::XMLWarningLog(void)
{
    MushcoreXMLOStream *retStream = &XMLErrorStream();
    retStream->OStream() << MushcoreUtil::LogTimeString() << ": Warning: ";
    return *retStream;
}

MushcoreXMLOStream&
MushcoreLog::XMLInfoLog(void)
{
    MushcoreXMLOStream *retStream = &XMLStdStream();
    retStream->OStream() << MushcoreUtil::LogTimeString() << ": Info: ";
    return *retStream;
}
