/*
 * $Id: MediaAudioNull.cpp,v 1.1 2002/08/24 13:12:31 southa Exp $
 * $Log: MediaAudioNull.cpp,v $
 * Revision 1.1  2002/08/24 13:12:31  southa
 * Null MediaAudio device
 *
 */

#include "MediaAudioNull.h"

MediaAudioNull::MediaAudioNull()
{
    cerr << "Created NULL audio device" << endl;
}

void
MediaAudioNull::PlayMusic(const string& inName)
{
}

void
MediaAudioNull::Play(MediaSound& inSound)
{
}

void
MediaAudioNull::Play(MediaSoundStream& inSoundStream, U32 inLoop=10000)
{
}

void
MediaAudioNull::SoundHalt(MediaSound& inSound)
{
}

void
MediaAudioNull::Load(MediaSound& inSound) const
{
}

void
MediaAudioNull::Free(MediaSound& inSound) const
{
}

void
MediaAudioNull::Ticker(void)
{
}
