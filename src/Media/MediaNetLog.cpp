/*
 * $Id: MediaNetLog.cpp,v 1.4 2002/11/22 11:42:06 southa Exp $
 * $Log: MediaNetLog.cpp,v $
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

#include "MediaNetLog.h"

#include "MediaSDL.h"

MediaNetLog MediaNetLog::m_gMediaNetLogInstance;

MediaNetLog::MediaNetLog() :
    m_outStream(NULL),
    m_netLog(true),
    m_webLog(true),
    m_verboseLog(true),
    m_logFullIP(false)
{
}

MediaNetLog::~MediaNetLog()
{
    if (m_outStream != NULL) delete m_outStream;
}

ostream&
MediaNetLog::Log(void)
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
    *retStream << SDL_GetTicks() << ": ";
    return *retStream;
}

ostream&
MediaNetLog::NetLog(void)
{
    if (m_netLog)
    {
        return Log();
    }
    else
    {
        m_nullStream.clear();
        return m_nullStream;
    }
}

ostream&
MediaNetLog::WebLog(void)
{
    if (m_webLog)
    {
        return Log();
    }
    else
    {
        m_nullStream.clear();
        return m_nullStream;
    }
}

ostream&
MediaNetLog::VerboseLog(void)
{
    if (m_verboseLog)
    {
        return Log();
    }
    else
    {
        m_nullStream.clear();
        return m_nullStream;
    }
}

void
MediaNetLog::OpenFile(const string& inName)
{
    COREASSERT(false);
}

void
MediaNetLog::CloseFile(void)
{
    if (m_outStream != NULL) delete m_outStream;
    m_outStream=NULL;
}

