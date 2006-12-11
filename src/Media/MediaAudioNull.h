//%includeGuardStart {
#ifndef MEDIAAUDIONULL_H
#define MEDIAAUDIONULL_H
//%includeGuardStart } GkZzyN3sTv2NQk1GSbcLsw
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioNull.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } +TqwNDFCDF610zYAXeniiA
/*
 * $Id: MediaAudioNull.h,v 1.14 2006/12/11 13:28:23 southa Exp $
 * $Log: MediaAudioNull.h,v $
 * Revision 1.14  2006/12/11 13:28:23  southa
 * Snapshot
 *
 * Revision 1.13  2006/07/26 16:37:22  southa
 * Options menu
 *
 * Revision 1.12  2006/06/01 15:39:13  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.10  2005/04/19 23:25:40  southa
 * Mode switching and recognition
 *
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
    virtual void Play(MediaSound& inSound, Mushware::tVal inVolume, Mushware::t4Val inPosition,
                      Mushware::U32 inFlags);
    virtual void Play(MediaSoundStream& inSoundStream, Mushware::U32 inLoop=10000);
    virtual void SoundHalt(MediaSound& inSound);
    virtual void Load(MediaSound& inSound) const;
    virtual void Load(MediaSoundStream& inSoundStream) {}
    virtual void Free(MediaSound& inSound) const;
    virtual void Ticker(void);
    virtual void MusicFadeIn(Mushware::tVal inMsec) {}
    virtual void MusicFadeOut(Mushware::tVal inMsec) {}
    virtual void MusicVolumeSet(Mushware::tVal inVolume) {}
    virtual void AudioVolumeSet(Mushware::tVal inVolume) {}

private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
