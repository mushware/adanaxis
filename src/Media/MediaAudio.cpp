/*
 * $Id$
 * $Log$
 */

#include "MediaAudio.h"
#include "MediaAudioSDL.h"
#include "MediaAudioNull.h"

auto_ptr<MediaAudio> MediaAudio::m_instance;

MediaAudio::~MediaAudio()
{
}

MediaAudio&
MediaAudio::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    InstanceCreate();
    return *m_instance;
}

void
MediaAudio::InstanceCreate()
{
    try
    {
        m_instance.reset(new MediaAudioSDL);
    }
    catch (exception& e)
    {
        cerr << "Exception creating MediaAudioSDL: " << e.what() << endl;
    }
    if (m_instance.get() == NULL)
    {
        m_instance.reset(new MediaAudioNull);
    }
}
