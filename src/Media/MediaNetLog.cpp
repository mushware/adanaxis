/*
 * $Id: MediaNetLog.cpp,v 1.1 2002/11/04 15:50:31 southa Exp $
 * $Log: MediaNetLog.cpp,v $
 * Revision 1.1  2002/11/04 15:50:31  southa
 * Network log
 *
 */

#include "MediaNetLog.h"

#include "MediaSDL.h"

MediaNetLog *MediaNetLog::m_instance=NULL;

MediaNetLog::MediaNetLog() :
    m_outStream(NULL)
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

