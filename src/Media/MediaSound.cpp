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
 * $Id: MediaSound.cpp,v 1.5 2002/08/24 13:12:31 southa Exp $
 * $Log: MediaSound.cpp,v $
 * Revision 1.5  2002/08/24 13:12:31  southa
 * Null MediaAudio device
 *
 * Revision 1.4  2002/08/19 09:59:36  southa
 * Removed sound callbacks, used polling
 *
 * Revision 1.3  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
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
    MediaAudio::Instance().Load(*this);
}

void
MediaSound::Free(void)
{
    if (m_chunk != NULL)
    {
        // cerr << "Freeing sound '" << m_filename << "'" << endl;
        MediaAudio::Instance().SoundHalt(*this);
        MediaAudio::Instance().Free(*this);
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
