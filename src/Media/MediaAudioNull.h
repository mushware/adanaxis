/*
 * $Id$
 * $Log$
 */

#include "MediaAudio.h"

class MediaAudioNull : public MediaAudio
{
public:
    MediaAudioNull();
    virtual void PlayMusic(const string& inName);
    virtual void Play(MediaSound& inSound);
    virtual void Play(MediaSoundStream& inSoundStream);
    virtual void SoundHalt(MediaSound& inSound);
    virtual void Load(MediaSound& inSound) const;
    virtual void Free(MediaSound& inSound) const;
    virtual void Ticker(void);
private:
};
