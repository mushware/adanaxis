/*
 * $Id: GameDialogue.cpp,v 1.6 2002/08/19 22:18:36 southa Exp $
 * $Log: GameDialogue.cpp,v $
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

#include "GameMotion.h"
#include "GameData.h"
#include "GameTimer.h"

void
GameDialogue::Render(void) const
{
    GameTimer& timer(GameData::Instance().TimerGet());
   
    U32 size=m_strings.size();
    
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());
    tVal windbackValue=timer.WindbackValueGet(glAppHandler.MillisecondsGet());

    
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
            MediaAudio::Instance().Play(*spec.soundRef.DataGet());
        }
    }


    for (U32 i=0; i<size; ++i)
    {
        SoundStreamSpec& spec=m_soundStreams[i];
        if (m_age < spec.startTime)
        {
            expired = false;
        }
        if (m_age == spec.startTime)
        {
            MediaAudio::Instance().Play(*spec.soundStreamRef.DataGet());
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
        throw(ReferenceFail("TextSet index too high for this Dialogue"));
    }
    m_strings[inWhich].string.TextSet(inStr);
}

void GameDialogue::ExpireNow(void)
{
    // Need to leave the last sound stream playing, if we haven't started it yet
    tVal latestTime=m_age;
    bool latestFound=false;
    U32 latestIndex;
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

    if (latestFound)
    {
        COREASSERT(latestIndex < m_soundStreams.size());
        SoundStreamSpec& spec=m_soundStreams[latestIndex];
        MediaAudio::Instance().Play(*spec.soundStreamRef.DataGet());
    }
}
    

void
GameDialogue::HandleTextEnd(CoreXML& inXML)
{
    CoreScalar alignment(CoreScalar(0));

    GameMotionSpec motionSpec=m_motion.MotionSpecGet();

    inXML.GetAttrib(alignment, "align");
    m_currentSpec.string=GLString(inXML.TopData(), m_fontRef, alignment.ValGet());
    m_currentSpec.motionSpec=motionSpec;
    m_strings.push_back(m_currentSpec);
    
    motionSpec.pos.y -= m_fontRef.SizeGet()*m_currentSpec.midSize;
    m_motion.MotionSpecSet(motionSpec);
}

void
GameDialogue::HandleFontEnd(CoreXML& inXML)
{
    tVal size=inXML.GetAttribOrThrow("size").ValGet();
    m_fontRef=GLFontRef(inXML.TopData(), size);
}

void
GameDialogue::HandleStartTimeEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for starttime.  Should be <starttime>100.0</starttime>";
    if (!(data >> m_currentSpec.startTime)) inXML.Throw(failMessage);
}

void
GameDialogue::HandleEndTimeEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for endtime.  Should be <endtime>100.0</endtime>";
    if (!(data >> m_currentSpec.endTime)) inXML.Throw(failMessage);
}

void
GameDialogue::HandleFadeTimeEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for fadetime.  Should be <fadetime>100.0</fadetime>";
    if (!(data >> m_currentSpec.fadeTime)) inXML.Throw(failMessage);
    if (fabs(m_currentSpec.fadeTime) < 1) m_currentSpec.fadeTime=1;
}

void
GameDialogue::HandleSizesEnd(CoreXML& inXML)
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
GameDialogue::HandleStartColourEnd(CoreXML& inXML)
{
    m_currentSpec.startColour.Unpickle(inXML);
}

void
GameDialogue::HandleMidColourEnd(CoreXML& inXML)
{
    m_currentSpec.midColour.Unpickle(inXML);
}

void
GameDialogue::HandleEndColourEnd(CoreXML& inXML)
{
    m_currentSpec.endColour.Unpickle(inXML);
}

void
GameDialogue::HandleMotionStart(CoreXML& inXML)
{
    m_motion.Unpickle(inXML);
}

void
GameDialogue::HandleSoundEnd(CoreXML& inXML)
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
GameDialogue::HandleSoundStreamEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for soundstream.  Should be <sound>rate-music<sound>";
    string name;
    SoundStreamSpec streamSpec;
    if (!(data >> name)) inXML.Throw(failMessage);
    streamSpec.soundStreamRef.NameSet(name);
    streamSpec.startTime = m_currentSpec.startTime;
    m_soundStreams.push_back(streamSpec);
}

void
GameDialogue::HandleDialogueEnd(CoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameDialogue::NullHandler(CoreXML& inXML)
{
}

void
GameDialogue::Pickle(ostream& inOut, const string& inPrefix="") const
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
GameDialogue::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameDialogue::XMLStartHandler(CoreXML& inXML)
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
GameDialogue::XMLEndHandler(CoreXML& inXML)
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
GameDialogue::XMLDataHandler(CoreXML& inXML)
{
}


