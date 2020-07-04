//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaSoundStream.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } js55IAKMGRDXssAyR3KZ7A
/*
 * $Id: MediaSoundStream.cpp,v 1.22 2006/07/31 11:01:37 southa Exp $
 * $Log: MediaSoundStream.cpp,v $
 * Revision 1.22  2006/07/31 11:01:37  southa
 * Music and dialogues
 *
 * Revision 1.21  2006/06/01 15:39:14  southa
 * DrawArray verification and fixes
 *
 * Revision 1.20  2005/05/19 13:02:08  southa
 * Mac release work
 *
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
        throw(MushcoreCommandFail("Usage: playsoundstream('name')"));
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
        throw(MushcoreCommandFail("Usage: loadsoundstream('name')"));
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
