//%includeGuardStart {
#ifndef MEDIAAUDIO_H
#define MEDIAAUDIO_H
//%includeGuardStart } 5PPiYxjjZkwpM5mcMQmsaw
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudio.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } tyJt/xZmlTC6wUUlDIYd3g
/*
 * $Id: MediaAudio.h,v 1.22 2004/01/02 21:13:10 southa Exp $
 * $Log: MediaAudio.h,v $
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

class MediaSound;
class MediaSoundStream;

class MediaAudio : public MushcoreAbstractSingleton<MediaAudio>
{
public:
    virtual ~MediaAudio();
    virtual void PlayMusic(const std::string& inName) = 0;
    virtual void Play(MediaSound& inSound) = 0;
    virtual void Play(MediaSoundStream& inSoundStream, Mushware::U32 inLoop=10000) = 0;
    virtual void SoundHalt(MediaSound& inSound) = 0;
    virtual void Load(MediaSound& inSound) const = 0;
    virtual void Free(MediaSound& inSound) const = 0;
    virtual void Ticker(void) = 0;

    static MediaAudio *SingletonFactory(void);
    
protected:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
