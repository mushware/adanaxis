/*
 * $Id$
 * $Log$
 */

#include "MediaNetLog.h"

#include "MediaSDL.h"

auto_ptr<MediaNetLog> MediaNetLog::m_instance;

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

