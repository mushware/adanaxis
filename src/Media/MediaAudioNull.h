/*
 * $Id: MediaAudioNull.h,v 1.1 2002/08/24 13:12:31 southa Exp $
 * $Log: MediaAudioNull.h,v $
 * Revision 1.1  2002/08/24 13:12:31  southa
 * Null MediaAudio device
 *
 */

#include "MediaAudio.h"

class MediaAudioNull : public MediaAudio
{
public:
    MediaAudioNull();
    virtual void PlayMusic(const string& inName);
    virtual void Play(MediaSound& inSound);
    virtual void Play(MediaSoundStream& inSoundStream, U32 inLoop=10000);
    virtual void SoundHalt(MediaSound& inSound);
    virtual void Load(MediaSound& inSound) const;
    virtual void Free(MediaSound& inSound) const;
    virtual void Ticker(void);
private:
};
