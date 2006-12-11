//%includeGuardStart {
#ifndef MEDIAAUDIO_H
#define MEDIAAUDIO_H
//%includeGuardStart } 5PPiYxjjZkwpM5mcMQmsaw
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudio.h
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
//%Header } NkO0g6TshWQZ+4+THDCdtQ
/*
 * $Id: MediaAudio.h,v 1.27 2006/07/26 16:37:22 southa Exp $
 * $Log: MediaAudio.h,v $
 * Revision 1.27  2006/07/26 16:37:22  southa
 * Options menu
 *
 * Revision 1.26  2006/06/01 15:39:13  southa
 * DrawArray verification and fixes
 *
 * Revision 1.25  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.24  2005/04/19 23:25:40  southa
 * Mode switching and recognition
 *
 * Revision 1.23  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.22  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.21  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.20  2003/08/21 23:09:00  southa
 * Fixed file headers
 *
 * Revision 1.19  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.18  2003/01/18 17:05:46  southa
 * Singleton work
 *
 * Revision 1.17  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.16  2002/12/29 20:30:55  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.15  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
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

#include "mushMushcore.h"
#include "MediaAudioChannelDef.h"

class MediaSound;
class MediaSoundStream;

class MediaAudio : public MushcoreAbstractSingleton<MediaAudio>
{
public:
    virtual ~MediaAudio();
    virtual void PlayMusic(const std::string& inName) = 0;
    virtual void Play(MediaSound& inSound) = 0;
    virtual void Play(MediaSound& inSound, Mushware::tVal inVolume, Mushware::t4Val inPosition) = 0;
    virtual void Play(MediaSoundStream& inSoundStream, Mushware::U32 inLoop=10000) = 0;
    virtual void SoundHalt(MediaSound& inSound) = 0;
    virtual void Load(MediaSound& inSound) const = 0;
    virtual void Load(MediaSoundStream& inSoundStream) = 0;
    virtual void Free(MediaSound& inSound) const = 0;
    virtual void Ticker(void) = 0;
    virtual void MusicFadeIn(Mushware::tVal inMsec) = 0;
    virtual void MusicFadeOut(Mushware::tVal inMsec) = 0;
    virtual void MusicVolumeSet(Mushware::tVal inVolume) = 0;
    virtual void AudioVolumeSet(Mushware::tVal inVolume) = 0;
    
    const MediaAudioChannelDef& ChannelDef(Mushware::U32 inIndex);
    MediaAudioChannelDef& ChannelDefWRef(Mushware::U32 inIndex);
    void ChannelDefsResize(Mushware::U32 inSize, const MediaAudioChannelDef& inDef);
                           
    static MediaAudio *SingletonFactory(void);
    
private:
    std::vector<MediaAudioChannelDef *> m_channelDefs;    
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
