/*
 * $Id: MediaAudio.cpp,v 1.2 2002/06/13 15:15:56 southa Exp $
 * $Log: MediaAudio.cpp,v $
 * Revision 1.2  2002/06/13 15:15:56  southa
 * New directory structure, FPS printing, load command
 *
 * Revision 1.1  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 */

#include "MediaAudio.h"
#include "MediaSDL.h"

bool MediaAudio::m_audioGood=false;

void
MediaAudio::Init(void)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        throw(DeviceFail("Unable to init SDL: "+string(SDL_GetError())));
    }
    atexit(SDL_Quit);

    int audioRate = 44100;
    unsigned short audioFormat = MIX_DEFAULT_FORMAT; /* 16-bit stereo */
    int audioChannels = 2;
    int audioBuffers = 4096;
    
    if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers))
    {
        throw(DeviceFail("Unable to open SDL for audio: "+string(Mix_GetError())));
    }

    if (!Mix_QuerySpec(&audioRate, &audioFormat, &audioChannels))
    {
        throw(DeviceFail("Unable to open SDL for audio: "+string(Mix_GetError())));
    }
    cerr << "Got audioRate=" << audioRate << ", audioFormat=" << audioFormat << ", audioChannels=" << audioChannels << endl;   
    m_audioGood=true;
}

void
MediaAudio::PlayMusic(const string& inFilename)
{
    if (m_audioGood)
    {
        Mix_Music *music = Mix_LoadMUS(inFilename.c_str());
        if (music == NULL)
        {
            throw(FileFail(inFilename, "Failed to load music: "+string(Mix_GetError())));
        }
        Mix_PlayMusic(music, 10000);    
    }
}
