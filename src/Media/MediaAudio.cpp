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
 * $Id: MediaAudio.cpp,v 1.4 2002/06/20 15:50:30 southa Exp $
 * $Log: MediaAudio.cpp,v $
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

#include "MediaAudio.h"
#include "MediaSDL.h"

MediaAudio *MediaAudio::m_instance=NULL;

MediaAudio::~MediaAudio()
{
    Mix_CloseAudio();
}
        
MediaAudio::MediaAudio()
{
    MediaSDL::Instance().InitAudio();
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
}

void
MediaAudio::PlayMusic(const string& inFilename)
{
    Mix_Music *music = Mix_LoadMUS(inFilename.c_str());
    if (music == NULL)
    {
        throw(FileFail(inFilename, "Failed to load music: "+string(Mix_GetError())));
    }
    Mix_PlayMusic(music, 10000);    
}
