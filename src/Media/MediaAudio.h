#ifndef MEDIAAUDIO_H
#define MEDIAAUDIO_H
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
 * $Id: MediaAudio.h,v 1.14 2002/10/22 20:42:07 southa Exp $
 * $Log: MediaAudio.h,v $
 * Revision 1.14  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.13  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
 * Revision 1.11  2002/08/24 13:12:31  southa
 * Null MediaAudio device
 *
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
    virtual void Play(MediaSoundStream& inSoundStream, Mushware::U32 inLoop=10000) = 0;
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
