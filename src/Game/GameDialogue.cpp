//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameDialogue.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } TQoHFnQLMF2y8QhfOFHB/A
/*
 * $Id: GameDialogue.cpp,v 1.27 2005/03/25 19:13:48 southa Exp $
 * $Log: GameDialogue.cpp,v $
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
            gl.MoveTo(specRef.Posicity().Pos().X(), specRef.Posicity().Pos().Y());
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
                specRef.PosicityWRef().InPlaceVelocityAdd();
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
    
    m_expired=expired;
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

const char *GameDialogue::AutoNameGet(void) const
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
        ioIn >> *this;
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
//%outOfLineFunctions } y4OiVChZ45VHS4b05bz8dA
