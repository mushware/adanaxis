/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: MediaAudioNull.cpp,v 1.2 2002/08/26 12:44:37 southa Exp $
 * $Log: MediaAudioNull.cpp,v $
 * Revision 1.2  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
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
