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
 * $Id: MediaSoundStream.cpp,v 1.2 2002/08/17 10:41:51 southa Exp $
 * $Log: MediaSoundStream.cpp,v $
 * Revision 1.2  2002/08/17 10:41:51  southa
 * Designer fixes
 *
 * Revision 1.1  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
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
        throw(CommandFail("Usage: playsoundstreamm('name')"));
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
