/*
 * $Id$
 * $Log$
 */

#include "MediaAudio.h"
#include "MediaSDL.h"

void
MediaAudio::Init(void)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        throw(FatalFail("Unable to init SDL: "+string(SDL_GetError())));
    }
    atexit(SDL_Quit);

    int audioRate = 44100;
    unsigned short audioFormat = MIX_DEFAULT_FORMAT; /* 16-bit stereo */
    int audioChannels = 2;
    int audioBuffers = 4096;
    
    if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers))
    {
        throw(FatalFail("Unable to open SDL for audio: "+string(Mix_GetError())));
    }

    if (!Mix_QuerySpec(&audioRate, &audioFormat, &audioChannels))
    {
        throw(FatalFail("Unable to open SDL for audio: "+string(Mix_GetError())));
    }
    cerr << "Got audioRate=" << audioRate << ", audioFormat=" << audioFormat << ", audioChannels=" << audioChannels << endl;   
}

void
MediaAudio::PlayMusic(const string& inFilename)
{
    Mix_Music *music = Mix_LoadMUS(inFilename.c_str());
    if (music == NULL)
    {
        throw(FileFail(inFilename, "Failed to load music: "+string(Mix_GetError())));
    }
    Mix_PlayMusic(music, 0);    
}
