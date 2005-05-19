//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaSound.cpp
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
//%Header } eyFyRRwAJGHklPvS1D6HFQ
/*
 * $Id: MediaSound.cpp,v 1.21 2004/01/02 21:13:10 southa Exp $
 * $Log: MediaSound.cpp,v $
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
        throw(MushcoreCommandFail("Usage: transientsound <name> <filename>"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    MediaSound *sound=MushcoreData<MediaSound>::Sgl().Give(name, new MediaSound(filename));
    sound->ResidenceSet(false);
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
