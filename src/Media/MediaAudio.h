#ifndef MEDIAAUDIO_H
#define MEDIAAUDIO_H
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
 * $Id$
 * $Log$
 */

#include "MediaStandard.h"

class MediaSound;
class MediaSoundStream;

class MediaAudio
{
public:
    virtual ~MediaAudio();
    virtual void PlayMusic(const string& inName) = 0;
    virtual void Play(MediaSound& inSound) = 0;
    virtual void Play(MediaSoundStream& inSoundStream) = 0;
    virtual void SoundHalt(MediaSound& inSound) = 0;
    virtual void Load(MediaSound& inSound) const = 0;
    virtual void Free(MediaSound& inSound) const = 0;
    virtual void Ticker(void) = 0;

    static void InstanceCreate(void);
    static MediaAudio& Instance(void);

private:
    static auto_ptr<MediaAudio> m_instance;
};

#endif
