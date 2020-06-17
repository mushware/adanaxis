//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaSound.cpp
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
//%Header } EDjBJV0XxdAWilFXyLgung
/*
 * $Id: MediaSound.cpp,v 1.25 2007/04/18 09:22:27 southa Exp $
 * $Log: MediaSound.cpp,v $
 * Revision 1.25  2007/04/18 09:22:27  southa
 * Header and level fixes
 *
 * Revision 1.24  2006/11/12 14:39:50  southa
 * Player weapons amd audio fix
 *
 * Revision 1.23  2006/06/01 15:39:14  southa
 * DrawArray verification and fixes
 *
 * Revision 1.22  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.21  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.20  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.19  2003/08/21 23:09:02  southa
 * Fixed file headers
 *
 * Revision 1.18  2003/01/20 12:23:22  southa
 * Code and interface tidying
 *
 * Revision 1.17  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.16  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.15  2003/01/17 13:30:39  southa
 * Source conditioning and build fixes
 *
 * Revision 1.14  2003/01/13 14:32:01  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.13  2003/01/12 17:32:58  southa
 * Mushcore work
 *
 * Revision 1.12  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.11  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
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
#include "MediaSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MediaSound);

MushcoreInstaller MediaSoundInstaller(MediaSound::Install);

MediaSound::MediaSound(const string& inName):
    m_filename(inName),
    m_chunk(NULL),
    m_resident(false),
    m_isNull(false)
{
}

MediaSound::~MediaSound()
{
    Free();
}

void
MediaSound::Load(void)
{
    MediaAudio::Sgl().Load(*this);
}

void
MediaSound::Free(void)
{
    if (m_chunk != NULL)
    {
        // cerr << "Freeing sound '" << m_filename << "'" << endl;
        MediaAudio::Sgl().SoundHalt(*this);
        MediaAudio::Sgl().Free(*this);
        // cerr << "Freed sound '" << m_filename << "'" << endl;
        m_chunk=NULL;
    }
}    

void
MediaSound::EndHandler(void)
{
}

MushcoreScalar
MediaSound::TransientSound(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: transientsound <name> <filename>"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    MediaSound *sound=MushcoreData<MediaSound>::Sgl().Give(name, new MediaSound(filename));
    sound->ResidenceSet(true); // Transient sounds now resident (caused crashes)
    return MushcoreScalar(0);
}

MushcoreScalar
MediaSound::ResidentSound(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: residentsound('name','filename')"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    MediaSound *sound=MushcoreData<MediaSound>::Sgl().Give(name, new MediaSound(filename));
    sound->ResidenceSet(true);
    sound->Load();
    return MushcoreScalar(0);
}

MushcoreScalar
MediaSound::PlaySound(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(MushcoreCommandFail("Usage: playsound('name')"));
    }
    string name;
    ioCommand.PopParam(name);
    MediaSound *sound=MushcoreData<MediaSound>::Sgl().Get(name);
    MediaAudio::Sgl().Play(*sound);
    return MushcoreScalar(0);
}

void
MediaSound::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("residentsound", ResidentSound);
    MushcoreInterpreter::Sgl().HandlerAdd("transientsound", TransientSound);
    MushcoreInterpreter::Sgl().HandlerAdd("playsound", PlaySound);
}
