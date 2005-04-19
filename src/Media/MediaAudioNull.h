//%includeGuardStart {
#ifndef MEDIAAUDIONULL_H
#define MEDIAAUDIONULL_H
//%includeGuardStart } GkZzyN3sTv2NQk1GSbcLsw
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioNull.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Lyih9KbNJKXiDaCn2V9pQg
/*
 * $Id: MediaAudioNull.h,v 1.9 2004/01/02 21:13:10 southa Exp $
 * $Log: MediaAudioNull.h,v $
 * Revision 1.9  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:01  southa
 * Fixed file headers
 *
 * Revision 1.6  2002/12/29 20:30:55  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.5  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:28  southa
 * Source conditioning
 *
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
    virtual void PlayMusic(const std::string& inName);
    virtual void Play(MediaSound& inSound);
    virtual void Play(MediaSoundStream& inSoundStream, Mushware::U32 inLoop=10000);
    virtual void SoundHalt(MediaSound& inSound);
    virtual void Load(MediaSound& inSound) const;
    virtual void Load(MediaSoundStream& inSoundStream) {}
    virtual void Free(MediaSound& inSound) const;
    virtual void Ticker(void);
    virtual void MusicFadeIn(Mushware::tVal inMsec) {};
    virtual void MusicFadeOut(Mushware::tVal inMsec) {};
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
