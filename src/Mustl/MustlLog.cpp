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
 * $Id: MustlLog.cpp,v 1.5 2002/12/20 13:17:46 southa Exp $
 * $Log: MustlLog.cpp,v $
 * Revision 1.5  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/12/17 12:53:34  southa
 * Mustl library
 *
 * Revision 1.3  2002/12/14 15:04:34  southa
 * Mustl fixes
 *
 * Revision 1.2  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:26  southa
 * Created Mustl
 *
 * Revision 1.5  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.4  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.3  2002/11/08 11:54:40  southa
 * Web fixes
 *
 * Revision 1.2  2002/11/07 00:53:37  southa
 * localweb work
 *
 * Revision 1.1  2002/11/04 15:50:31  southa
 * Network log
 *
 */

#include "MustlLog.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

using namespace Mustl;
using namespace std;

MustlLog MustlLog::m_gMustlLogInstance;

MustlLog::MustlLog() :
    m_outStream(NULL),
    m_netLog(true),
    m_webLog(true),
    m_verboseLog(false),
    m_trafficLog(false),
    m_logFullIP(false)
{
    m_nullStream = new ostringstream;
}

MustlLog::~MustlLog()
{
    if (m_outStream != NULL) delete m_outStream;
    delete m_nullStream;
}

ostream&
MustlLog::Log(void)
{
    ostream *retStream;
    if (m_outStream == NULL)
    {
        retStream = &cout;
    }
    else
    {
        retStream = m_outStream;
    }
    *retStream << MustlTimer::Instance().CurrentMsecGet() << ": ";
    return *retStream;
}

ostream&
MustlLog::NetLog(void)
{
    if (m_netLog)
    {
        return Log();
    }
    else
    {
        m_nullStream->clear();
        return *m_nullStream;
    }
}

ostream&
MustlLog::WebLog(void)
{
    if (m_webLog)
    {
        return Log();
    }
    else
    {
        m_nullStream->clear();
        return *m_nullStream;
    }
}

ostream&
MustlLog::VerboseLog(void)
{
    if (m_verboseLog)
    {
        return Log();
    }
    else
    {
        m_nullStream->clear();
        return *m_nullStream;
    }
}

ostream&
MustlLog::TrafficLog(void)
{
    if (m_trafficLog)
    {
        return Log();
    }
    else
    {
        m_nullStream->clear();
        return *m_nullStream;
    }
}

void
MustlLog::OpenFile(const string& inName)
{
    MUSTLASSERT(false);
}

void
MustlLog::CloseFile(void)
{
    if (m_outStream != NULL) delete m_outStream;
    m_outStream=NULL;
}

