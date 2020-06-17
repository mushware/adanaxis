//%includeGuardStart {
#ifndef MEDIAAUDIONULL_H
#define MEDIAAUDIONULL_H
//%includeGuardStart } GkZzyN3sTv2NQk1GSbcLsw
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioNull.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } zUh+/k5qAe4upmUV9E3lew
/*
 * $Id: MediaAudioNull.h,v 1.15 2006/12/11 18:54:18 southa Exp $
 * $Log: MediaAudioNull.h,v $
 * Revision 1.15  2006/12/11 18:54:18  southa
 * Positional audio
 *
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
    virtual void VoicePlay(MediaSound& inSound);
    virtual void SoundHalt(MediaSound& inSound);
    virtual void Load(MediaSound& inSound) const;
    virtual void Load(MediaSoundStream& inSoundStream) {}
    virtual void Free(MediaSound& inSound) const;
    virtual void Ticker(void);
    virtual void MusicFadeIn(Mushware::tVal inMsec) {}
    virtual void MusicFadeOut(Mushware::tVal inMsec) {}
    virtual void MusicVolumeSet(Mushware::tVal inVolume) {}
    virtual void AudioVolumeSet(Mushware::tVal inVolume) {}
    virtual void VoiceVolumeSet(Mushware::tVal inVolume) {}

private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
