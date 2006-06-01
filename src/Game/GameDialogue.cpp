//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameDialogue.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } 4xqdhFCU1OwTEJubgm2zbA
/*
 * $Id: GameDialogue.cpp,v 1.34 2005/07/04 15:59:00 southa Exp $
 * $Log: GameDialogue.cpp,v $
 * Revision 1.34  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.33  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.32  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
 * Revision 1.31  2005/06/16 17:25:38  southa
 * Client/server work
 *
 * Revision 1.30  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.29  2005/03/28 18:59:32  southa
 * Dialogues for Tesseract Trainer
 *
 * Revision 1.28  2005/03/25 22:04:48  southa
 * Dialogue and MushcoreIO fixes
 *
 * Revision 1.27  2005/03/25 19:13:48  southa
 * GameDialogue work
 *
 */

#include "GameDialogue.h"

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller GameDialogueInstaller(GameDialogue::Install);

MUSHCORE_DATA_INSTANCE(GameDialogue);

GameDialogue::GameDialogue() :
    m_age(0),
    m_expired(false)
{
}

void
GameDialogue::Render(void) const
{
    for (U32 i=0; i < m_strings.size(); ++i)
    {
        const GameStringSpec& specRef = m_strings[i];
        if (m_age >= specRef.StartTime() && m_age < specRef.EndTime())
        {
            tVal startMult(0),midMult(0),endMult(0);
            if (m_age < specRef.StartTime())
            {
                startMult=1;
            }
            else if (m_age < specRef.EndTime())
            {
                startMult = 1 - (m_age - specRef.StartTime()) / specRef.FadeTime();
                if (startMult < 0) startMult=0;
                endMult = 1 - (specRef.EndTime() - m_age) / specRef.FadeTime();
                if (endMult < 0) endMult=0;
                midMult=1-startMult-endMult;
            }
            else
            {
                endMult=1;
            }
            
            GLUtils::PushMatrix();
            GLUtils gl;
            gl.MoveTo(specRef.Posticity().Pos().X(), specRef.Posticity().Pos().Y());
            // FIXME GLUtils::RotateAboutZ(m_angle);
            GLColour colour=
                startMult*specRef.StartColour() +
                midMult*specRef.MidColour() +
                endMult*specRef.EndColour();
            colour.Apply();
            
            tVal scale=
                startMult*specRef.StartSize() +
                midMult*specRef.MidSize() +
                endMult*specRef.EndSize();
            GLUtils::Scale(scale, scale, 1);
            specRef.String().Render();
            GLUtils::PopMatrix();
        }
    }
}

void
GameDialogue::Move(void)
{
    bool expired=true;
    
    for (U32 i=0; i<m_strings.size(); ++i)
    {
        GameStringSpec& specRef = m_strings[i];
        
        if (m_age < specRef.EndTime())
        {
            expired=false;
            if (m_age >= specRef.StartTime())
            {
                specRef.PosticityWRef().InPlaceVelocityAdd();
            }
        }
    }
    
    for (U32 i=0; i<m_sounds.size(); ++i)
    {
        GameSoundSpec& specRef = m_sounds[i];
        if (m_age < specRef.StartTime())
        {
            expired = false;
        }
        if (m_age == specRef.StartTime())
        {
            MediaAudio::Sgl().Play(*specRef.SoundRef().Get());
        }
    }
    
    for (U32 i=0; i<m_soundStreams.size(); ++i)
    {
        GameSoundStreamSpec& specRef = m_soundStreams[i];
        if (m_age < specRef.StartTime())
        {
            expired = false;
        }
        if (m_age == specRef.StartTime())
        {
            MediaAudio::Sgl().Play(*specRef.SoundStreamRef().Get(), specRef.Loop());
        }
    }
    
    if (expired)
    {
        m_expired = true;
    }
    m_age++;
}

void
GameDialogue::TextSet(U32 inWhich, const string& inStr)
{
    if (inWhich >= m_strings.size())
    {
        throw(MushcoreReferenceFail("TextSet index too high for this Dialogue"));
    }
    m_strings[inWhich].StringWRef().TextSet(inStr);
}

void
GameDialogue::ExpireNow(void)
{
    // Need to leave the last sound stream playing, if we haven't started it yet
    tVal latestTime=m_age;
    bool latestFound=false;
    U32 latestIndex=0;

    for (U32 i=0; i<m_soundStreams.size(); ++i)
    {
        GameSoundStreamSpec& specRef = m_soundStreams[i];
        if (latestTime <= specRef.StartTime())
        {
            latestTime=specRef.StartTime();
            latestFound=true;
            latestIndex=i;
        }
    }
    
    if (m_killSound != "")
    {    
        MediaAudio::Sgl().Play(*MushcoreDataRef<MediaSound>(m_killSound).Get());
    }
    
    if (latestFound)
    {
        MUSHCOREASSERT(latestIndex < m_soundStreams.size());
        GameSoundStreamSpec& specRef = m_soundStreams[latestIndex];
        MediaAudio::Sgl().Play(*specRef.SoundStreamRef().Get());
    }
    
    m_expired = true;
}

MushcoreScalar
GameDialogue::GameDialogueLoad(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(MushcoreCommandFail("Usage: GameDialogueLoad <filename>"));
    }
    string filename;
    ioCommand.PopParam(filename);
    ifstream fileStream(filename.c_str());
    if (!fileStream) throw(MushcoreFileFail(filename, "Could not open file"));
    
    MushcoreXMLIStream xmlIStream(fileStream);
    
    xmlIStream >> MushcoreData<GameDialogue>::Sgl();
    
    return MushcoreScalar(0);
}

void
GameDialogue::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("GameDialogueLoad", GameDialogueLoad);
}

//%outOfLineFunctions {

const char *GameDialogue::AutoName(void) const
{
    return "GameDialogue";
}

MushcoreVirtualObject *GameDialogue::AutoClone(void) const
{
    return new GameDialogue(*this);
}

MushcoreVirtualObject *GameDialogue::AutoCreate(void) const
{
    return new GameDialogue;
}

MushcoreVirtualObject *GameDialogue::AutoVirtualFactory(void)
{
    return new GameDialogue;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GameDialogue", GameDialogue::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
GameDialogue::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "strings=" << m_strings << ", ";
    ioOut << "sounds=" << m_sounds << ", ";
    ioOut << "soundStreams=" << m_soundStreams << ", ";
    ioOut << "killSound=" << m_killSound << ", ";
    ioOut << "age=" << m_age << ", ";
    ioOut << "expired=" << m_expired;
    ioOut << "]";
}
bool
GameDialogue::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "strings")
    {
        ioIn >> m_strings;
    }
    else if (inTagStr == "sounds")
    {
        ioIn >> m_sounds;
    }
    else if (inTagStr == "soundStreams")
    {
        ioIn >> m_soundStreams;
    }
    else if (inTagStr == "killSound")
    {
        ioIn >> m_killSound;
    }
    else if (inTagStr == "age")
    {
        ioIn >> m_age;
    }
    else if (inTagStr == "expired")
    {
        ioIn >> m_expired;
    }
    else 
    {
        return false;
    }
    return true;
}
void
GameDialogue::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("strings");
    ioOut << m_strings;
    ioOut.TagSet("sounds");
    ioOut << m_sounds;
    ioOut.TagSet("soundStreams");
    ioOut << m_soundStreams;
    ioOut.TagSet("killSound");
    ioOut << m_killSound;
    ioOut.TagSet("age");
    ioOut << m_age;
    ioOut.TagSet("expired");
    ioOut << m_expired;
}
//%outOfLineFunctions } pMZF79hRXwW8iK1Da/c4IQ
