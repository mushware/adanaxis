/*
 * $Id$
 * $Log$
 */

#include "MediaSoundStream.h"

#include "MediaAudio.h"

auto_ptr< CoreData<MediaSoundStream> > CoreData<MediaSoundStream>::m_instance;

CoreInstaller MediaSoundStreamInstaller(MediaSoundStream::Install);

MediaSoundStream::MediaSoundStream(const string& inName):
m_filename(inName)
{
}

CoreScalar
MediaSoundStream::SoundStream(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: soundstream('name','filename')"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    CoreData<MediaSoundStream>::Instance().DataGive(name, new MediaSoundStream(filename));
    return CoreScalar(0);
}

CoreScalar
MediaSoundStream::PlaySoundStream(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(CommandFail("Usage: playsoundstream soundstream('name')"));
    }
    string name;
    ioCommand.PopParam(name);
    MediaSoundStream *soundStream=CoreData<MediaSoundStream>::Instance().DataGet(name);
    MediaAudio::Instance().Play(*soundStream) ;
    return CoreScalar(0);
}

void
MediaSoundStream::Install(void)
{
    CoreApp::Instance().AddHandler("soundstream", SoundStream);
    CoreApp::Instance().AddHandler("playsoundstream", PlaySoundStream);
}
