/*
 * $Id: MediaSound.cpp,v 1.2 2002/08/16 19:46:07 southa Exp $
 * $Log: MediaSound.cpp,v $
 * Revision 1.2  2002/08/16 19:46:07  southa
 * MediaSound work
 *
 * Revision 1.1  2002/08/15 13:39:31  southa
 * CoreData and CoreDatRef
 *
 */

#include "MediaSound.h"

#include "MediaAudio.h"

auto_ptr< CoreData<MediaSound> > CoreData<MediaSound>::m_instance;

CoreInstaller MediaSoundInstaller(MediaSound::Install);

MediaSound::MediaSound(const string& inName):
    m_filename(inName),
    m_chunk(NULL)
{
}

MediaSound::~MediaSound()
{
    Free();
}

void
MediaSound::Load(void)
{
    MediaAudio::Instance(); // Construct the audio
    SDL_RWops *src=SDL_RWFromFile(m_filename.c_str(), "rb");
    if (src == NULL)
    {
        throw(FileFail(m_filename, "Failed to open sound file: "+string(SDL_GetError())));
    }
    m_chunk = Mix_LoadWAV_RW(src, false); // Don't free after play
    if (m_chunk == NULL)
    {
        throw(FileFail(m_filename, "Failed to load sound: "+string(Mix_GetError())));
    }
}

void
MediaSound::Free(void)
{
    if (m_chunk != NULL)
    {
        // cerr << "Freeing sound '" << m_filename << "'" << endl;
        MediaAudio::Instance().SoundHalt(*this);
        Mix_FreeChunk(m_chunk);
        // cerr << "Freed sound '" << m_filename << "'" << endl;
        m_chunk=NULL;
    }
}    

void
MediaSound::EndHandler(void)
{
    if (!m_resident)
    {
        Free();
    }
}

Mix_Chunk *
MediaSound::MixChunkGet(void)
{
    if (m_chunk == NULL)
    {
        Load();
    }
    return m_chunk;
}

CoreScalar
MediaSound::TransientSound(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: transientsound <name> <filename>"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    MediaSound *sound=CoreData<MediaSound>::Instance().DataGive(name, new MediaSound(filename));
    sound->ResidenceSet(false);
    return CoreScalar(0);
}

CoreScalar
MediaSound::ResidentSound(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: residentsound('name','filename')"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    MediaSound *sound=CoreData<MediaSound>::Instance().DataGive(name, new MediaSound(filename));
    sound->ResidenceSet(true);
    sound->Load();
    return CoreScalar(0);
}

CoreScalar
MediaSound::PlaySound(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(CommandFail("Usage: playsound('name')"));
    }
    string name;
    ioCommand.PopParam(name);
    MediaSound *sound=CoreData<MediaSound>::Instance().DataGet(name);
    MediaAudio::Instance().Play(*sound);
    return CoreScalar(0);
}

void
MediaSound::Install(void)
{
    CoreApp::Instance().AddHandler("residentsound", ResidentSound);
    CoreApp::Instance().AddHandler("transientsound", TransientSound);
    CoreApp::Instance().AddHandler("playsound", PlaySound);
}
