#ifndef MEDIAAUDIONULL_H
#define MEDIAAUDIONULL_H
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
 * $Id: MediaAudioNull.h,v 1.2 2002/08/26 12:44:37 southa Exp $
 * $Log: MediaAudioNull.h,v $
 * Revision 1.2  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
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
#endif
