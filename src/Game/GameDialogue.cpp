/*
 * $Id$
 * $Log$
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
    COREASSERT(size==m_motionSpecs.size());
    COREASSERT(size==m_startColours.size());
    COREASSERT(size==m_midColours.size());
    COREASSERT(size==m_endColours.size());
    COREASSERT(size==m_startTimes.size());
    COREASSERT(size==m_endTimes.size());
    COREASSERT(size==m_fadeTimes.size());
    
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());
    tVal windbackValue=timer.WindbackValueGet(glAppHandler.MillisecondsGet());
    
    for (U32 i=0; i<size; ++i)
    {
        tVal startMult(0),midMult(0),endMult(0);
        if (m_age < m_startTimes[i])
        {
            startMult=1;
        }
        else if (m_age < m_endTimes[i])
        {
            startMult = 1 - (m_age - m_startTimes[i]) / m_fadeTimes[i];
            if (startMult < 0) startMult=0;
            endMult = 1 - (m_endTimes[i] - m_age) / m_fadeTimes[i];
            if (endMult < 0) endMult=0;
            midMult=1-startMult-endMult;
        }
        else
        {
            endMult=1;
        }
        if (1)
        {
            GameMotionSpec motionSpec(m_motionSpecs[i]);
            motionSpec.Windback(windbackValue);
            GLUtils::PushMatrix();
            GLUtils gl;
            gl.MoveTo(motionSpec.pos);
            GLUtils::RotateAboutZ(motionSpec.angle);
            GLColour colour=
                startMult*m_startColours[i] +
                midMult*m_midColours[i] +
                endMult*m_endColours[i];
            colour.Apply();
            
            tVal scale=
                startMult*m_startSizes[i] +
                midMult*m_midSizes[i] +
                endMult*m_endSizes[i];
            GLUtils::Scale(scale, scale, 1);
            m_strings[i].Render();
            GLUtils::PopMatrix();
        }
    }
}

void
GameDialogue::Move(void)
{
    U32 size=m_motionSpecs.size();

    for (U32 i=0; i<size; ++i)
    {
        m_motionSpecs[i].ApplyDelta();
    }
    m_age++;
}

void
GameDialogue::HandleTextEnd(CoreXML& inXML)
{
    CoreScalar alignment(CoreScalar(0));
    inXML.GetAttrib(alignment, "align");
    m_strings.push_back(GLString(inXML.TopData(), m_currentFontRef, alignment.ValGet()));
    m_motionSpecs.push_back(m_currentMotion.MotionSpecGet());
    m_startColours.push_back(m_currentStartColour);
    m_midColours.push_back(m_currentMidColour);
    m_endColours.push_back(m_currentEndColour);
    m_startSizes.push_back(m_currentStartSize);
    m_midSizes.push_back(m_currentMidSize);
    m_endSizes.push_back(m_currentEndSize);
    m_startTimes.push_back(m_currentStartTime);
    m_endTimes.push_back(m_currentEndTime);
    m_fadeTimes.push_back(m_currentFadeTime);

    GameMotionSpec motionSpec=m_currentMotion.MotionSpecGet();
    motionSpec.pos.y -= m_currentFontRef.SizeGet();
    m_currentMotion.MotionSpecSet(motionSpec);
}

void
GameDialogue::HandleFontEnd(CoreXML& inXML)
{
    tVal size=inXML.GetAttribOrThrow("size").ValGet();
    m_currentFontRef=GLFontRef(inXML.TopData(), size);
}

void
GameDialogue::HandleStartTimeEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for starttime.  Should be <starttime>100.0</starttime>";
    if (!(data >> m_currentStartTime)) inXML.Throw(failMessage);
}

void
GameDialogue::HandleEndTimeEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for endtime.  Should be <endtime>100.0</endtime>";
    if (!(data >> m_currentEndTime)) inXML.Throw(failMessage);
}

void
GameDialogue::HandleFadeTimeEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for fadetime.  Should be <fadetime>100.0</fadetime>";
    if (!(data >> m_currentFadeTime)) inXML.Throw(failMessage);
    if (fabs(m_currentFadeTime) < 1) m_currentFadeTime=1;
}

void
GameDialogue::HandleSizesEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for sizes.  Should be <sizes>0.0,1.0,0.0</sizes>";
    char comma;
    if (!(data >> m_currentStartSize)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);

    if (!(data >> m_currentMidSize)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);

    if (!(data >> m_currentEndSize)) inXML.Throw(failMessage);
}

void
GameDialogue::HandleStartColourEnd(CoreXML& inXML)
{
    m_currentStartColour.Unpickle(inXML);
}

void
GameDialogue::HandleMidColourEnd(CoreXML& inXML)
{
    m_currentMidColour.Unpickle(inXML);
}

void
GameDialogue::HandleEndColourEnd(CoreXML& inXML)
{
    m_currentEndColour.Unpickle(inXML);
}

void
GameDialogue::HandleMotionStart(CoreXML& inXML)
{
    m_currentMotion.Unpickle(inXML);
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
    m_endTable[kPickleData]["dialogue"] = &GameDialogue::HandleDialogueEnd;
    m_pickleState=kPickleData;
    m_currentMotion.MotionSpecSet(GameMotionSpec(GLPoint(0,0), 0));
    m_currentStartColour=GLColour(0,0,0,0);
    m_currentMidColour=GLColour(0,0,0,0);
    m_currentEndColour=GLColour(0,0,0,0);
    m_currentStartSize=1;
    m_currentMidSize=1;
    m_currentEndSize=1;
    m_currentFontRef=GLFontRef("font not set");
    m_currentStartTime=0;
    m_currentEndTime=100;
    m_currentFadeTime=1;
    m_age=0;
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


