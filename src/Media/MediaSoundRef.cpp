/*
 * $Id$
 * $Log$
 */

#include "MediaSoundRef.h"
#include "MediaData.h"

MediaSound *
MediaSoundRef::SoundGet(void) const
{
    if (m_soundPtr == NULL)
    {
        GetReference();
    }
    return m_soundPtr;
}

void
MediaSoundRef::GetReference(void) const
{
    m_soundPtr=MediaData::Instance().SoundGet(m_name);
    if (m_soundPtr == NULL)
    {
        throw(ReferenceFail("Attempt to access non-existent sound '"+m_name+"'"));
    }
}

bool
MediaSoundRef::Exists(void) const
{
    if (m_soundPtr != NULL) return true;
    m_soundPtr=MediaData::Instance().SoundGet(m_name);
    return (m_soundPtr != NULL);    
}
