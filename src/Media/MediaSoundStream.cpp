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
 * $Id: MediaSoundStream.cpp,v 1.6 2002/12/20 13:17:45 southa Exp $
 * $Log: MediaSoundStream.cpp,v $
 * Revision 1.6  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/12/05 13:20:13  southa
 * Client link handling
 *
 * Revision 1.4  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:29  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/17 10:41:51  southa
 * Designer fixes
 *
 * Revision 1.1  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
 */

#include "MediaSoundStream.h"

#include "MediaAudio.h"

using namespace Mushware;
using namespace std;

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
    CoreData<MediaSoundStream>::Instance().Give(name, new MediaSoundStream(filename));
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
    MediaSoundStream *soundStream=CoreData<MediaSoundStream>::Instance().Get(name);
    MediaAudio::Instance().Play(*soundStream) ;
    return CoreScalar(0);
}

void
MediaSoundStream::Install(void)
{
    CoreApp::Instance().AddHandler("soundstream", SoundStream);
    CoreApp::Instance().AddHandler("playsoundstream", PlaySoundStream);
}
