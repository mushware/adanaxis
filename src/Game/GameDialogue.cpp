/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameDialogue.cpp,v 1.22 2003/01/20 10:45:26 southa Exp $
 * $Log: GameDialogue.cpp,v $
 * Revision 1.22  2003/01/20 10:45:26  southa
 * Singleton tidying
 *
 * Revision 1.21  2003/01/13 14:31:58  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.20  2003/01/12 17:32:53  southa
 * Mushcore work
 *
 * Revision 1.19  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.18  2003/01/07 17:13:42  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.17  2002/12/29 20:59:55  southa
 * More build fixes
 *
 * Revision 1.16  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.15  2002/12/10 19:00:17  southa
 * Split timer into client and server
 *
 * Revision 1.14  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.13  2002/11/24 23:18:16  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.12  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.11  2002/10/10 13:51:16  southa
 * Speed fixes and various others
 *
 * Revision 1.10  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
 * Revision 1.8  2002/08/23 16:41:29  southa
 * Replaced deleted section
 *
 * Revision 1.7  2002/08/22 10:11:11  southa
 * Save records, spacebar dialogues
 *
 * Revision 1.6  2002/08/19 22:18:36  southa
 * Display of time differences
 *
 * Revision 1.5  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
 * Revision 1.4  2002/08/13 18:29:04  southa
 * Tidied GameDialogue code
 *
 * Revision 1.3  2002/08/13 17:50:21  southa
 * Added playsound command
 *
 * Revision 1.2  2002/08/10 12:34:48  southa
 * Added current dialogues
 *
 * Revision 1.1  2002/08/09 17:09:04  southa
 * GameDialogue added
 *
 */

#include "GameDialogue.h"

#include "GameData.h"
#include "GameDataUtils.h"
#include "GameMotion.h"
#include "GameSTL.h"
#include "GameTimer.h"

using namespace Mushware;
using namespace std;

void
GameDialogue::Render(void) const
{
    GameTimer& timer(GameData::Sgl().TimerGet());
   
    U32 size=m_strings.size();
    
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());
    timer.CurrentMsecSet(glAppHandler.MillisecondsGet());
    tVal windbackValue=timer.ClientGet().WindbackValueGet();

    
    for (U32 i=0; i<size; ++i)
    {
        const StringSpec& spec=m_strings[i];
        if (m_age >= spec.startTime && m_age < spec.endTime)
        {
            tVal startMult(0),midMult(0),endMult(0);
            if (m_age < spec.startTime)
            {
                startMult=1;
            }
            else if (m_age < spec.endTime)
            {
                startMult = 1 - (m_age - spec.startTime) / spec.fadeTime;
                if (startMult < 0) startMult=0;
                endMult = 1 - (spec.endTime - m_age) / spec.fadeTime;
                if (endMult < 0) endMult=0;
                midMult=1-startMult-endMult;
            }
            else
            {
                endMult=1;
            }
            
            GameMotionSpec motionSpec(spec.motionSpec);
            motionSpec.Windback(windbackValue);
            GLUtils::PushMatrix();
            GLUtils gl;
            gl.MoveTo(motionSpec.pos);
            GLUtils::RotateAboutZ(motionSpec.angle);
            GLColour colour=
                startMult*spec.startColour +
                midMult*spec.midColour +
                endMult*spec.endColour;
            colour.Apply();
            
            tVal scale=
                startMult*spec.startSize +
                midMult*spec.midSize +
                endMult*spec.endSize;
            GLUtils::Scale(scale, scale, 1);
            spec.string.Render();
            GLUtils::PopMatrix();
        }
    }
}

void
GameDialogue::Move(void)
{
    U32 size=m_strings.size();
    bool expired=true;
    for (U32 i=0; i<size; ++i)
    {
        StringSpec& spec=m_strings[i];

        if (m_age < spec.endTime)
        {
            expired=false;
            if (m_age >= spec.startTime)
            {
                spec.motionSpec.ApplyDelta();
            }
        }
    }
    
    size=m_sounds.size();
    
    for (U32 i=0; i<size; ++i)
    {
        SoundSpec& spec=m_sounds[i];
        if (m_age < spec.startTime)
        {
            expired = false;
        }
        if (m_age == spec.startTime)
        {
            MediaAudio::Sgl().Play(*spec.soundRef.Get());
        }
    }

    size=m_soundStreams.size();
    
    for (U32 i=0; i<size; ++i)
    {
        SoundStreamSpec& spec=m_soundStreams[i];
        if (m_age < spec.startTime)
        {
            expired = false;
        }
        if (m_age == spec.startTime)
        {
            MediaAudio::Sgl().Play(*spec.soundStreamRef.Get(), spec.loop);
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
    m_strings[inWhich].string.TextSet(inStr);
}

void GameDialogue::ExpireNow(void)
{
    // Need to leave the last sound stream playing, if we haven't started it yet
    tVal latestTime=m_age;
    bool latestFound=false;
    U32 latestIndex=0;
    U32 size=m_soundStreams.size();
    for (U32 i=0; i<size; ++i)
    {
        SoundStreamSpec& spec=m_soundStreams[i];
        if (latestTime <= spec.startTime)
        {
            latestTime=spec.startTime;
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
        SoundStreamSpec& spec=m_soundStreams[latestIndex];
        MediaAudio::Sgl().Play(*spec.soundStreamRef.Get());
    }
}
    

void
GameDialogue::HandleTextEnd(MushcoreXML& inXML)
{
    MushcoreScalar alignment(MushcoreScalar(0));

    GameMotionSpec motionSpec=m_motion.MotionSpecGet();

    inXML.GetAttrib(alignment, "align");
    m_currentSpec.string=GLString(inXML.TopData(), m_fontRef, alignment.ValGet());
    m_currentSpec.motionSpec=motionSpec;
    m_strings.push_back(m_currentSpec);
    
    motionSpec.pos.y -= m_fontRef.SizeGet()*m_currentSpec.midSize;
    m_motion.MotionSpecSet(motionSpec);
}

void
GameDialogue::HandleFontEnd(MushcoreXML& inXML)
{
    tVal size=inXML.GetAttribOrThrow("size").ValGet();
    m_fontRef=GLFontRef(inXML.TopData(), size);
}

void
GameDialogue::HandleStartTimeEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for starttime.  Should be <starttime>100.0</starttime>";
    if (!(data >> m_currentSpec.startTime)) inXML.Throw(failMessage);
}

void
GameDialogue::HandleEndTimeEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for endtime.  Should be <endtime>100.0</endtime>";
    if (!(data >> m_currentSpec.endTime)) inXML.Throw(failMessage);
}

void
GameDialogue::HandleFadeTimeEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for fadetime.  Should be <fadetime>100.0</fadetime>";
    if (!(data >> m_currentSpec.fadeTime)) inXML.Throw(failMessage);
    if (fabs(m_currentSpec.fadeTime) < 1) m_currentSpec.fadeTime=1;
}

void
GameDialogue::HandleSizesEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for sizes.  Should be <sizes>0.0,1.0,0.0</sizes>";
    char comma;
    if (!(data >> m_currentSpec.startSize)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);

    if (!(data >> m_currentSpec.midSize)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);

    if (!(data >> m_currentSpec.endSize)) inXML.Throw(failMessage);
}

void
GameDialogue::HandleStartColourEnd(MushcoreXML& inXML)
{
    m_currentSpec.startColour.Unpickle(inXML);
}

void
GameDialogue::HandleMidColourEnd(MushcoreXML& inXML)
{
    m_currentSpec.midColour.Unpickle(inXML);
}

void
GameDialogue::HandleEndColourEnd(MushcoreXML& inXML)
{
    m_currentSpec.endColour.Unpickle(inXML);
}

void
GameDialogue::HandleMotionStart(MushcoreXML& inXML)
{
    m_motion.Unpickle(inXML);
}

void
GameDialogue::HandleSoundEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for sound.  Should be <sound>impressive<sound>";
    string name;
    SoundSpec soundSpec;
    if (!(data >> name)) inXML.Throw(failMessage);
    soundSpec.soundRef.NameSet(name);
    soundSpec.startTime = m_currentSpec.startTime;
    m_sounds.push_back(soundSpec);
}

void
GameDialogue::HandleSoundStreamEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for soundstream.  Should be <sound>rate-music<sound>";
    string name;
    SoundStreamSpec streamSpec;
    if (!(data >> name)) inXML.Throw(failMessage);
    streamSpec.soundStreamRef.NameSet(name);
    streamSpec.startTime = m_currentSpec.startTime;

    MushcoreScalar temp;
    temp=MushcoreScalar(10000.0);
    inXML.GetAttrib(temp, "loop");
    streamSpec.loop=temp.U32Get();
    
    m_soundStreams.push_back(streamSpec);
}

void
GameDialogue::HandleKillSoundEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for killsound.  Should be <killsound>phone-beep</killsound>";
    if (!(data >> m_killSound)) inXML.Throw(failMessage);
}

void
GameDialogue::HandleDialogueEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameDialogue::NullHandler(MushcoreXML& inXML)
{
}

void
GameDialogue::Pickle(ostream& inOut, const string& inPrefix) const
{
    if (m_strings.size() != 0)
    {
// Fill me in
    }
}

void
GameDialogue::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["text"] = &GameDialogue::NullHandler;
    m_endTable[kPickleData]["text"] = &GameDialogue::HandleTextEnd;
    m_startTable[kPickleData]["font"] = &GameDialogue::NullHandler;
    m_endTable[kPickleData]["font"] = &GameDialogue::HandleFontEnd;
    m_startTable[kPickleData]["startcolour"] = &GameDialogue::NullHandler;
    m_endTable[kPickleData]["startcolour"] = &GameDialogue::HandleStartColourEnd;
    m_startTable[kPickleData]["midcolour"] = &GameDialogue::NullHandler;
    m_endTable[kPickleData]["midcolour"] = &GameDialogue::HandleMidColourEnd;
    m_startTable[kPickleData]["endcolour"] = &GameDialogue::NullHandler;
    m_endTable[kPickleData]["endcolour"] = &GameDialogue::HandleEndColourEnd;
    m_startTable[kPickleData]["starttime"] = &GameDialogue::NullHandler;
    m_endTable[kPickleData]["starttime"] = &GameDialogue::HandleStartTimeEnd;
    m_startTable[kPickleData]["endtime"] = &GameDialogue::NullHandler;
    m_endTable[kPickleData]["endtime"] = &GameDialogue::HandleEndTimeEnd;
    m_startTable[kPickleData]["fadetime"] = &GameDialogue::NullHandler;
    m_endTable[kPickleData]["fadetime"] = &GameDialogue::HandleFadeTimeEnd;
    m_startTable[kPickleData]["sizes"] = &GameDialogue::NullHandler;
    m_endTable[kPickleData]["sizes"] = &GameDialogue::HandleSizesEnd;
    m_startTable[kPickleData]["motion"] = &GameDialogue::HandleMotionStart;
    m_startTable[kPickleData]["sound"] = &GameDialogue::NullHandler;
    m_endTable[kPickleData]["sound"] = &GameDialogue::HandleSoundEnd;
    m_startTable[kPickleData]["soundstream"] = &GameDialogue::NullHandler;
    m_endTable[kPickleData]["soundstream"] = &GameDialogue::HandleSoundStreamEnd;
    m_startTable[kPickleData]["killsound"] = &GameDialogue::NullHandler;
    m_endTable[kPickleData]["killsound"] = &GameDialogue::HandleKillSoundEnd;
    m_endTable[kPickleData]["dialogue"] = &GameDialogue::HandleDialogueEnd;
    m_pickleState=kPickleData;
    m_motion.MotionSpecSet(GameMotionSpec(GLPoint(0,0), 0));
    m_currentSpec.startColour=GLColour(0,0,0,0);
    m_currentSpec.midColour=GLColour(0,0,0,0);
    m_currentSpec.endColour=GLColour(0,0,0,0);
    m_currentSpec.startSize=1;
    m_currentSpec.midSize=1;
    m_currentSpec.endSize=1;
    m_fontRef=GLFontRef("font not set");
    m_currentSpec.startTime=0;
    m_currentSpec.endTime=100;
    m_currentSpec.fadeTime=1;
    m_age=0;
    m_expired=false;
}

void
GameDialogue::UnpickleEpilogue(void)
{
    m_startTable.clear();
    m_endTable.clear();
}

void
GameDialogue::Unpickle(MushcoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameDialogue::XMLStartHandler(MushcoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << "> in Dialogue.  Potential matches are";
        ElementFunctionMap::iterator p = m_startTable[m_pickleState].begin();
        while (p != m_startTable[m_pickleState].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
GameDialogue::XMLEndHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << "> in Dialogue.  Potential matches are";
        ElementFunctionMap::iterator p = m_endTable[m_pickleState].begin();
        while (p != m_endTable[m_pickleState].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
GameDialogue::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
GameDialogue::TypeNameGet(void) const
{
    return "gamedialogue";
}
