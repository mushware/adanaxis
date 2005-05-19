//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaSoundStream.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } xlCRhuAoTMrT0DwUtH9KGQ
/*
 * $Id: MediaSoundStream.cpp,v 1.19 2005/04/19 23:25:41 southa Exp $
 * $Log: MediaSoundStream.cpp,v $
 * Revision 1.19  2005/04/19 23:25:41  southa
 * Mode switching and recognition
 *
 * Revision 1.18  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.17  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.16  2003/08/21 23:09:02  southa
 * Fixed file headers
 *
 * Revision 1.15  2003/01/20 12:23:22  southa
 * Code and interface tidying
 *
 * Revision 1.14  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.13  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.12  2003/01/17 13:30:39  southa
 * Source conditioning and build fixes
 *
 * Revision 1.11  2003/01/13 14:32:02  southa
 * Build frameworks for Mac OS X
 *
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

MUSHCORE_DATA_INSTANCE(MediaSoundStream);

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
    MushcoreData<MediaSoundStream>::Sgl().Give(name, new MediaSoundStream(filename));
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
    MediaSoundStream *soundStream=MushcoreData<MediaSoundStream>::Sgl().Get(name);
    MediaAudio::Sgl().Play(*soundStream) ;
    return MushcoreScalar(0);
}

MushcoreScalar
MediaSoundStream::LoadSoundStream(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(MushcoreCommandFail("Usage: loadsoundstreamm('name')"));
    }
    string name;
    ioCommand.PopParam(name);
    MediaSoundStream *soundStream=MushcoreData<MediaSoundStream>::Sgl().Get(name);
    MediaAudio::Sgl().Load(*soundStream) ;
    return MushcoreScalar(0);
}

void
MediaSoundStream::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("soundstream", SoundStream);
    MushcoreInterpreter::Sgl().HandlerAdd("playsoundstream", PlaySoundStream);
    MushcoreInterpreter::Sgl().HandlerAdd("loadsoundstream", LoadSoundStream);
}
