/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MediaSound.cpp,v 1.10 2002/12/29 20:59:58 southa Exp $
 * $Log: MediaSound.cpp,v $
 * Revision 1.10  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.9  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/12/05 13:20:13  southa
 * Client link handling
 *
 * Revision 1.7  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:28  southa
 * Source conditioning
 *
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
 * MushcoreData and MushcoreDatRef
 *
 */

#include "MediaSound.h"

#include "MediaAudio.h"

using namespace Mushware;
using namespace std;

auto_ptr< MushcoreData<MediaSound> > MushcoreData<MediaSound>::m_instance;

MushcoreInstaller MediaSoundInstaller(MediaSound::Install);

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

MushcoreScalar
MediaSound::TransientSound(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: transientsound <name> <filename>"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    MediaSound *sound=MushcoreData<MediaSound>::Instance().Give(name, new MediaSound(filename));
    sound->ResidenceSet(false);
    return MushcoreScalar(0);
}

MushcoreScalar
MediaSound::ResidentSound(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: residentsound('name','filename')"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    MediaSound *sound=MushcoreData<MediaSound>::Instance().Give(name, new MediaSound(filename));
    sound->ResidenceSet(true);
    sound->Load();
    return MushcoreScalar(0);
}

MushcoreScalar
MediaSound::PlaySound(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(CommandFail("Usage: playsound('name')"));
    }
    string name;
    ioCommand.PopParam(name);
    MediaSound *sound=MushcoreData<MediaSound>::Instance().Get(name);
    MediaAudio::Instance().Play(*sound);
    return MushcoreScalar(0);
}

void
MediaSound::Install(void)
{
    MushcoreApp::Instance().AddHandler("residentsound", ResidentSound);
    MushcoreApp::Instance().AddHandler("transientsound", TransientSound);
    MushcoreApp::Instance().AddHandler("playsound", PlaySound);
}
