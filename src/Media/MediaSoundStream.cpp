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
 * $Id: MediaSoundStream.cpp,v 1.10 2003/01/12 17:32:58 southa Exp $
 * $Log: MediaSoundStream.cpp,v $
 * Revision 1.10  2003/01/12 17:32:58  southa
 * Mushcore work
 *
 * Revision 1.9  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.8  2003/01/09 14:57:05  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/29 20:59:58  southa
 * More build fixes
 *
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
#include "MediaSTL.h"

using namespace Mushware;
using namespace std;

auto_ptr< MushcoreData<MediaSoundStream> > MushcoreData<MediaSoundStream>::m_instance;

MushcoreInstaller MediaSoundStreamInstaller(MediaSoundStream::Install);

MediaSoundStream::MediaSoundStream(const string& inName):
m_filename(inName)
{
}

MushcoreScalar
MediaSoundStream::SoundStream(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: soundstream('name','filename')"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    MushcoreData<MediaSoundStream>::Instance().Give(name, new MediaSoundStream(filename));
    return MushcoreScalar(0);
}

MushcoreScalar
MediaSoundStream::PlaySoundStream(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(MushcoreCommandFail("Usage: playsoundstreamm('name')"));
    }
    string name;
    ioCommand.PopParam(name);
    MediaSoundStream *soundStream=MushcoreData<MediaSoundStream>::Instance().Get(name);
    MediaAudio::Instance().Play(*soundStream) ;
    return MushcoreScalar(0);
}

void
MediaSoundStream::Install(void)
{
    MushcoreInterpreter::Instance().AddHandler("soundstream", SoundStream);
    MushcoreInterpreter::Instance().AddHandler("playsoundstream", PlaySoundStream);
}
