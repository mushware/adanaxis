//%Header {
/*****************************************************************************
 *
 * File: src/Game/InfernalMotion.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } yQCVz33NM1yzcNsDyqJ4jw
/*
 * $Id: InfernalMotion.cpp,v 1.14 2003/09/17 19:40:32 southa Exp $
 * $Log: InfernalMotion.cpp,v $
 * Revision 1.14  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.13  2003/08/21 23:08:49  southa
 * Fixed file headers
 *
 * Revision 1.12  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.11  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
 * Revision 1.10  2003/01/07 17:13:43  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.9  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.8  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/11/24 23:18:23  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.6  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.5  2002/10/17 16:41:21  southa
 * Initialisation fix and player facet
 *
 * Revision 1.4  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/09 17:09:04  southa
 * GameDialogue added
 *
 * Revision 1.2  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/23 14:10:47  southa
 * Added InfernalMotion
 *
 */

#include "InfernalMotion.h"

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

void
InfernalMotion::HandleRectEnd(MushcoreXML& inXML)
{
    m_motionSpec.shape.Unpickle(inXML);
}

void
InfernalMotion::HandlePositionEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for position.  Should be <position>64,96,0.314</position>";
    char comma;
    if (!(data >> m_motionSpec.pos.x)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);
    if (!(data >> m_motionSpec.pos.y)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);
    if (!(data >> m_motionSpec.angle)) inXML.Throw(failMessage);
}

void
InfernalMotion::HandleDeltaEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for delta.  Should be <delta>1,-1,0.0314</delta>";
    char comma;
    if (!(data >> m_motionSpec.deltaPos.x)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);
    if (!(data >> m_motionSpec.deltaPos.y)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);
    if (!(data >> m_motionSpec.deltaAngle)) inXML.Throw(failMessage);
}

void
InfernalMotion::HandleMotionEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
InfernalMotion::NullHandler(MushcoreXML& inXML)
{
}

void
InfernalMotion::Pickle(ostream& inOut, const string& inPrefix) const
{
    m_motionSpec.shape.Pickle(inOut, inPrefix);
    inOut << inPrefix << "<position>" << m_motionSpec.pos.x << ",";
    inOut << m_motionSpec.pos.y << "," << m_motionSpec.angle << "</position>" << endl;
}

void
InfernalMotion::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["rect"] = &InfernalMotion::NullHandler;
    m_endTable[kPickleData]["rect"] = &InfernalMotion::HandleRectEnd;
    m_startTable[kPickleData]["position"] = &InfernalMotion::NullHandler;
    m_endTable[kPickleData]["position"] = &InfernalMotion::HandlePositionEnd;
    m_startTable[kPickleData]["delta"] = &InfernalMotion::NullHandler;
    m_endTable[kPickleData]["delta"] = &InfernalMotion::HandleDeltaEnd;
    m_endTable[kPickleData]["motion"] = &InfernalMotion::HandleMotionEnd;
    m_pickleState=kPickleData;

    m_motionSpec.ZeroSet();
}

void
InfernalMotion::Unpickle(MushcoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
InfernalMotion::UnpickleEpilogue(void)
{
    m_startTable.resize(0);
    m_endTable.resize(0);
}

void
InfernalMotion::XMLStartHandler(MushcoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << "> in Motion.  Potential matches are";
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
InfernalMotion::XMLEndHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << "> in Motion.  Potential matches are";
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
InfernalMotion::XMLDataHandler(MushcoreXML& inXML)
{
}


char *
InfernalMotion::TypeNameGet(void) const
{
    return "gamemotion";
}
