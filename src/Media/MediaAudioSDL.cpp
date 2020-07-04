//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioSDL.cpp
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
//%Header } 855iXKDHzq/sqHagCGXUGw
/*
 * $Id: MediaAudioSDL.cpp,v 1.39 2007/06/25 20:37:11 southa Exp $
 * $Log: MediaAudioSDL.cpp,v $
 * Revision 1.39  2007/06/25 20:37:11  southa
 * X11 fixes
 *
 * Revision 1.38  2007/06/25 15:59:43  southa
 * X11 compatibility
 *
 * Revision 1.37  2007/06/24 21:09:39  southa
 * X11 support
 *
 * Revision 1.36  2007/06/14 01:03:52  southa
 * win32 build fixes
 *
 * Revision 1.35  2007/04/16 18:51:00  southa
 * Voice work
 *
 * Revision 1.34  2007/04/16 08:41:09  southa
 * Level and header mods
 *
 * Revision 1.33  2007/03/07 16:59:44  southa
 * Khazi spawning and level ends
 *
 * Revision 1.32  2006/12/16 10:57:22  southa
 * Encrypted files
 *
 * Revision 1.31  2006/12/14 00:33:48  southa
 * Control fix and audio pacing
 *
 * Revision 1.30  2006/12/11 18:54:18  southa
 * Positional audio
 *
 * Revision 1.29  2006/12/11 15:01:48  southa
 * Snapshot
 *
 * Revision 1.28  2006/12/11 13:28:23  southa
 * Snapshot
 *
 * Revision 1.27  2006/11/12 14:39:50  southa
 * Player weapons amd audio fix
 *
 * Revision 1.26  2006/11/10 20:17:11  southa
 * Audio work
 *
 * Revision 1.25  2006/11/06 12:56:31  southa
 * MushFile work
 *
 * Revision 1.24  2006/10/12 22:04:47  southa
 * Collision events
 *
 * Revision 1.23  2006/07/28 16:52:20  southa
 * Options work
 *
 * Revision 1.22  2006/07/26 16:37:22  southa
 * Options menu
 *
 * Revision 1.21  2006/06/01 15:39:13  southa
 * DrawArray verification and fixes
 *
 * Revision 1.20  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.19  2005/04/19 23:25:41  southa
 * Mode switching and recognition
 *
 * Revision 1.18  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.17  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.16  2003/08/21 23:09:01  southa
 * Fixed file headers
 *
 * Revision 1.15  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.13  2003/01/17 13:30:39  southa
 * Source conditioning and build fixes
 *
 * Revision 1.12  2003/01/13 14:32:01  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.11  2003/01/12 17:32:57  southa
 * Mushcore work
 *
 * Revision 1.10  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.9  2003/01/07 17:13:44  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.8  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.7  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/31 14:51:33  southa
 * Removed call to Mix_ChannelFinished
 *
 * Revision 1.4  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/26 15:19:02  southa
 * Fix for SDL_mixer fading state bug
 *
 * Revision 1.2  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
 * Revision 1.1  2002/08/24 13:12:31  southa
 * Null MediaAudio device
 *
 * Revision 1.11  2002/08/19 09:59:36  southa
 * Removed sound callbacks, used polling
 *
 * Revision 1.10  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
 * Revision 1.9  2002/08/16 19:46:07  southa
 * MediaSound work
 *
 * Revision 1.8  2002/08/13 17:50:21  southa
 * Added playsound command
 *
 * Revision 1.7  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.4  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.3  2002/06/20 11:06:14  southa
 * Updated for cygwin
 *
 * Revision 1.2  2002/06/13 15:15:56  southa
 * New directory structure, FPS printing, load command
 *
 * Revision 1.1  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 */

#include "MediaAudioSDL.h"
#include "MediaAudioSDLChannelDef.h"
#include "MediaRWops.h"
#include "MediaSDL.h"
#include "MediaSTL.h"
#include "MediaSound.h"
#include "MediaSoundStream.h"

#include "API/mushPlatform.h"

using namespace Mushware;
using namespace std;

MediaAudioSDL::MediaAudioSDL():
    m_music(NULL),
    m_errCtr(0),
    m_fpMix_LoadMUS_RW(NULL)
{
    MediaSDL::Sgl().InitAudio();

    int audioRate = MIX_DEFAULT_FREQUENCY; // 22050Hz
    unsigned short audioFormat = MIX_DEFAULT_FORMAT; // 16-bit stereo
    int audioHardChannels = 2; // Stereo
    U32 audioSoftChannels = 32;
    int audioBuffer = 1024;

    const MushcoreScalar *pScalar;
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "MUSHME_AUDIO_RATE"))
    {
        audioRate = pScalar->U32Get();
    }
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "MUSHME_AUDIO_FORMAT"))
    {
        audioFormat = pScalar->U32Get();
    }
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "MUSHME_AUDIO_HARD_CHANNELS"))
    {
        audioHardChannels = pScalar->U32Get();
    }
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "MUSHME_AUDIO_SOFT_CHANNELS"))
    {
        audioSoftChannels = pScalar->U32Get();
    }
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "MUSHME_AUDIO_BUFFER"))
    {
        audioBuffer = pScalar->U32Get();
    }
    
    if (Mix_OpenAudio(audioRate, audioFormat, audioHardChannels, audioBuffer))
    {
        throw(MushcoreDeviceFail("Unable to open SDL for audio: "+string(Mix_GetError())));
    }

    if (!Mix_QuerySpec(&audioRate, &audioFormat, &audioHardChannels))
    {
        Mix_CloseAudio();
        throw(MushcoreDeviceFail("Unable to open SDL for audio: "+string(Mix_GetError())));
    }
    m_softChannels = Mix_AllocateChannels(audioSoftChannels);
    ChannelDefsResize(m_softChannels, MediaAudioSDLChannelDef());
    
    m_lastTickerMsec = SDL_GetTicks();

    PlatformMiscUtils::FunctionPointerGetIfExists(m_fpMix_LoadMUS_RW, "Mix_LoadMUS_RW");

    const SDL_version *pVersion = Mix_Linked_Version();
    if (pVersion->major <= 1 && pVersion->minor <= 2 && pVersion->patch <= 6)
    {
        MushcoreLog::Sgl().WarningLog() << "SDL_mixer version is " << static_cast<U32>(pVersion->major) <<
            "." << static_cast<U32>(pVersion->minor)  << "." << static_cast<U32>(pVersion->patch) <<
            " but >= 1.2.7 would be better.  OGG music load from .mush file disabled" << endl;
       
    }
    else
    {
        PlatformMiscUtils::FunctionPointerGetIfExists(m_fpMix_LoadMUS_RW, "Mix_LoadMUS_RW");
    }
}

MediaAudioSDL::~MediaAudioSDL()
{
    // Delete the MediaSound database before removing the audio services
    // that they're using
    MushcoreData<MediaSound>::SingletonDestroy();

    Mix_CloseAudio();
}

void
MediaAudioSDL::PlayMusic(const string& inFilename)
{
    Mix_Music *music = Mix_LoadMUS(inFilename.c_str());
    if (music == NULL)
    {
        if (++m_errCtr < 100)
        {
            MushcoreLog::Sgl().WarningLog() << "Failed to play music '" << inFilename << "': " << string(Mix_GetError());
        }
    }
    Mix_PlayMusic(music, 10000);    
}

void
MediaAudioSDL::ChannelUpdate(Mushware::U32 inChannel)
{
    MediaAudioSDLChannelDef& channelDef( dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(inChannel)) );
    MUSHCOREASSERT(channelDef.Positional());
    
    tVal volume = channelDef.Volume() * ImpliedVolume(channelDef);
    tVal baseVolume = channelDef.Voice() ? m_voiceVolume : m_audioVolume;
    Mix_Volume(inChannel, static_cast<int>(volume * baseVolume));

    tVal impliedPanning = ImpliedPanning(channelDef);
    tVal panLeft = ( impliedPanning < 0.0 ) ? 1.0 : (1.0 - impliedPanning);
    tVal panRight = ( impliedPanning > 0.0 ) ? 1.0 : (1.0 + impliedPanning);
    
    Mix_SetPanning(inChannel, static_cast<U8>(255 * panLeft), static_cast<U8>(255 * panRight));
}

void
MediaAudioSDL::ChannelTrigger(Mushware::U32 inChannel)
{
    MediaAudioSDLChannelDef& channelDef( dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(inChannel)) );
    MUSHCOREASSERT(channelDef.ActiveSample() != NULL);
    
    if (!channelDef.ActiveSample()->IsNull())
    {
        tVal volume = channelDef.Volume();
        tVal baseVolume = channelDef.Voice() ? m_voiceVolume : m_audioVolume;
        
        if (channelDef.Positional())
        {
            volume *= ImpliedVolume(channelDef);
        }
        
        if (channelDef.ActiveSample()->MixChunkGet() == NULL)
        {
            channelDef.ActiveSample()->Load();
        }
        
        if (static_cast<S32>(inChannel) != Mix_PlayChannel(inChannel,
                                                           channelDef.ActiveSample()->MixChunkGet(),
                                                           channelDef.Loop() ? -1 : 0))
        {
            MushcoreLog::Sgl().ErrorLog() << "Failed to play sound" << endl;
        }
        else
        {
            if (channelDef.Positional())
            {
                ChannelUpdate(inChannel);
            }
            else
            {
                Mix_Volume(inChannel, static_cast<int>(volume * baseVolume));        
                Mix_SetPanning(inChannel,255,255);
            }
            
            channelDef.ActivitySet(MediaAudioChannelDef::kActivityPlaying);
        }
    }
}

void
MediaAudioSDL::Play(MediaSound& inSound, Mushware::tVal inVolume, Mushware::t4Val inPosition,
                    Mushware::U32 inFlags)
{
    if (SDL_GetTicks() - m_lastTickerMsec > 10000)
    {
        static bool errorReported = false;
        if (!errorReported)
        {
            MushcoreLog::Sgl().WarningLog() << "MediaAudioSDL ticker not being called" << endl;
            errorReported = true;
        }
    }
    U32 channel;
    if (ChannelSelect(channel))
    {
        MUSHCOREASSERT(channel < m_softChannels);
        
        MediaAudioSDLChannelDef& channelDef( dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(channel)) );
        channelDef.VolumeSet(inVolume);
        channelDef.PositionSet(inPosition);
        channelDef.PositionalSet(true);
        channelDef.LoopSet(false);
        channelDef.VoiceSet(false);
        channelDef.ActiveSampleSet(&inSound);
        ChannelTrigger(channel);
        if (inFlags & kFlagsTiedToListener)
        {
            // No position updates for this channel 
            channelDef.PositionalSet(false);
        }
    }
}

void
MediaAudioSDL::Play(MediaSound& inSound)
{
    U32 channel;
    if (ChannelSelect(channel))
    {
        MUSHCOREASSERT(channel < m_softChannels);
        
        MediaAudioSDLChannelDef& channelDef( dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(channel)) );
        channelDef.VolumeSet(1.0);
        channelDef.PositionalSet(false);
        channelDef.LoopSet(false);
        channelDef.VoiceSet(false);
        channelDef.ActiveSampleSet(&inSound);
        ChannelTrigger(channel);
    }
}

void
MediaAudioSDL::VoicePlay(MediaSound& inSound)
{
    U32 channel;
    if (ChannelSelect(channel))
    {
        MUSHCOREASSERT(channel < m_softChannels);
        
        MediaAudioSDLChannelDef& channelDef( dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(channel)) );
        channelDef.VolumeSet(1.0);
        channelDef.PositionalSet(false);
        channelDef.LoopSet(false);
        channelDef.VoiceSet(true);
        channelDef.ActiveSampleSet(&inSound);
        ChannelTrigger(channel);
    }
}

void
MediaAudioSDL::Load(MediaSoundStream& inSoundStream)
{
    /* Loading music from a .mush file keeps an image of the compressed file
     * in memory
     */
    if (m_music != NULL)
    {
        Mix_FreeMusic(m_music);
        m_music=NULL;
    }

    string filename(inSoundStream.FilenameGet());
    m_musicMushFile.OpenForRead(filename);
    
    if (m_musicMushFile.SourceIsNull())
    {
        MushcoreLog::Sgl().InfoLog() << "Music loaded form null source - not played" << endl;
        // Leave m_music as NULL
    }
    else if (m_fpMix_LoadMUS_RW == NULL)
    {
        try
        {
            m_music = Mix_LoadMUS(m_musicMushFile.PlainFilename().c_str());

            if (m_music == NULL)
            {
                if (++m_errCtr < 100)
                {
                     MushcoreLog::Sgl().WarningLog() << "Failed to play music '" << filename << "': " << string(Mix_GetError());
                }
            }
        }
        catch (MushcoreFileFail& e)
        {
            if (++m_errCtr < 100)
            {
                MushcoreLog::Sgl().WarningLog() << "Cannot load music file " << filename << ": SDL_LoadMUS_RW not supported (needs SDL_mixer >= 1.2.7)" << endl;
            }
        }
    }
    else
    {

        MediaRWops mediaRWops(m_musicMushFile);

        SDL_RWops *pSrc = NULL;
        
        try
        {
            pSrc = mediaRWops.RWops();
        }
        catch (MushcoreFileFail& e)
        {
            if (++m_errCtr < 100)
            {
                MushcoreLog::Sgl().WarningLog() << e.what() << endl;
            }
        }
        
        if (pSrc != NULL)
        {
            // If Mix_LoadMUS_RW is missing you need SDL_mixer 1.2.7 or later
            m_music = reinterpret_cast<Mix_Music * (*)(SDL_RWops *rw)>(m_fpMix_LoadMUS_RW)(pSrc);
            if (m_music == NULL)
            {
                if (++m_errCtr < 100)
                {
                    MushcoreLog::Sgl().WarningLog() << "Failed to play music '" << filename << "': " << string(Mix_GetError());
                }
            }
        }
    }
}

void
MediaAudioSDL::Play(MediaSoundStream& inSoundStream, U32 inLoop)
{
    Load(inSoundStream);
    if (m_music != NULL)
    {
        Mix_PlayMusic(m_music, inLoop);
    }
}

void
MediaAudioSDL::Ticker(void)
{
    for (U32 i=0; i<m_softChannels; ++i)
    {
        MediaAudioSDLChannelDef& channelDef(dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(i)));
        
        if (channelDef.Activity() != MediaAudioChannelDef::kActivityIdle)
        {
            
            if (Mix_Playing(i) == 0)
            {
                channelDef.ActivitySet(MediaAudioChannelDef::kActivityIdle);
            }
            else
            {
                if (channelDef.Positional())
                {
                    ChannelUpdate(i);
                }
            }
        }
    }
    m_lastTickerMsec = SDL_GetTicks();
}

void
MediaAudioSDL::SoundHalt(MediaSound& inSound)
{
    for (U32 i=0; i<m_softChannels; ++i)
    {
        MediaAudioSDLChannelDef& channelDef(dynamic_cast<MediaAudioSDLChannelDef&>(ChannelDefWRef(i)));
        
        if (channelDef.ActiveSample() == &inSound && Mix_Playing(i) != 0)
        {
            Mix_HaltChannel(i);
        }
    }
}

void
MediaAudioSDL::Load(MediaSound &inSound) const
{
    Free(inSound);
    string filename(inSound.FilenameGet());
    
    MushFileFile srcFile;
    srcFile.OpenForRead(filename);
    
    if (srcFile.SourceIsNull())
    {
        MushcoreLog::Sgl().InfoLog() << "Sound loaded from null source - not played" << endl;
        inSound.IsNullSet(true);
        // Leave MixChunk as NULL
    }
    else
    {
        MediaRWops mediaRWops(srcFile);
        
        SDL_RWops *pSrc = NULL;
        
        try
        {
            pSrc = mediaRWops.RWops();
        }
        catch (MushcoreFileFail& e)
        {
            if (++m_errCtr < 100)
            {
                MushcoreLog::Sgl().WarningLog() << e.what() << endl;
            }
        }
        
        if (pSrc != NULL)
        {
            Mix_Chunk *chunk = Mix_LoadWAV_RW(pSrc, false); // Don't free after play
            if (chunk == NULL)
            {
                if (++m_errCtr < 100)
                {
                    MushcoreLog::Sgl().WarningLog()  << "Failed to load sound '" << filename << "': " << string(Mix_GetError());
                }
            }
            inSound.MixChunkSet(chunk);
            inSound.IsNullSet(false);
        }
    }
}

void
MediaAudioSDL::Free(MediaSound &inSound) const
{
    Mix_Chunk *chunk = inSound.MixChunkGet();
    if (chunk != NULL)
    {
        Mix_FreeChunk(chunk);
    }
    inSound.MixChunkSet(NULL);
}

void
MediaAudioSDL::MusicFadeIn(Mushware::tVal inMsec)
{
    if (m_music != NULL)
    {
        Mix_FadeInMusic(m_music, 10000, static_cast<int>(inMsec));
    }
}

void
MediaAudioSDL::MusicFadeOut(Mushware::tVal inMsec)
{
    Mix_FadeOutMusic(static_cast<int>(inMsec));
}

void
MediaAudioSDL::MusicVolumeSet(Mushware::tVal inVolume)
{
    Mix_VolumeMusic(static_cast<int>(inVolume*128));
}

void
MediaAudioSDL::AudioVolumeSet(Mushware::tVal inVolume)
{
    m_audioVolume = static_cast<U32>(inVolume*128);
}

void
MediaAudioSDL::VoiceVolumeSet(Mushware::tVal inVolume)
{
    m_voiceVolume = static_cast<U32>(inVolume*128);
}

