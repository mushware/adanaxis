/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLLightDef.cpp,v 1.4 2002/11/24 23:18:03 southa Exp $
 * $Log: GLLightDef.cpp,v $
 * Revision 1.4  2002/11/24 23:18:03  southa
 * Added type name accessor to CorePickle
 *
 * Revision 1.3  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.2  2002/10/10 22:47:57  southa
 * Full light definitions
 *
 * Revision 1.1  2002/10/10 18:25:13  southa
 * Light links and test lights
 *
 */

#include "GLLightDef.h"

using namespace Mushware;

void
GLLightDef::BasePositionSet(const GLVector& inVec)
{
    m_basePosition=inVec;
    m_position=m_offset+m_basePosition;
}

void
GLLightDef::HandleOffsetEnd(CoreXML& inXML)
{
    m_offset.Unpickle(inXML);
    m_position=m_offset+m_basePosition;
}

void
GLLightDef::HandlePowerEnd(CoreXML& inXML)
{
    tVal power;
    istringstream data(inXML.TopData());
    if (!(data >> power)) inXML.Throw("Bad format for power");
    if (power < 0.001) inXML.Throw("Bad value for power");
    m_constant = 0.001;
    m_linear = 0;
    m_quadratic = 1/power;
}

void
GLLightDef::HandleColourEnd(CoreXML& inXML)
{
    m_specular.Unpickle(inXML);
    m_diffuse = m_specular;
}

void
GLLightDef::HandleAmbientEnd(CoreXML& inXML)
{
    m_ambient.Unpickle(inXML);
}

void
GLLightDef::HandleDiffuseEnd(CoreXML& inXML)
{
    m_diffuse.Unpickle(inXML);
}

void
GLLightDef::HandleSpecularEnd(CoreXML& inXML)
{
    m_specular.Unpickle(inXML);
}

void
GLLightDef::HandleCutoffEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_cutoff)) inXML.Throw("Bad format for cutoff");
    if (m_cutoff < 0 || m_cutoff > 180) inXML.Throw("Bad value for cutoff");
}

void
GLLightDef::HandleDirectionEnd(CoreXML& inXML)
{
    m_direction.Unpickle(inXML);
}

void
GLLightDef::HandleExponentEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_exponent)) inXML.Throw("Bad format for exponent");
    if (m_exponent < 0 || m_exponent > 128) inXML.Throw("Bad value for exponent");
}

void
GLLightDef::HandleConstantEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_constant)) inXML.Throw("Bad format for constant");
}

void
GLLightDef::HandleLinearEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_linear)) inXML.Throw("Bad format for linear");
}
void
GLLightDef::HandleQuadraticEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_quadratic)) inXML.Throw("Bad format for quadratic");
}

void
GLLightDef::HandleLightEnd(CoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GLLightDef::NullHandler(CoreXML& inXML)
{
}

void
GLLightDef::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<!-- Incomplete -->" << endl;
}

void
GLLightDef::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["offset"] = &GLLightDef::NullHandler;
    m_endTable[kPickleData]["offset"] = &GLLightDef::HandleOffsetEnd;
    m_startTable[kPickleData]["power"] = &GLLightDef::NullHandler;
    m_endTable[kPickleData]["power"] = &GLLightDef::HandlePowerEnd;
    m_startTable[kPickleData]["colour"] = &GLLightDef::NullHandler;
    m_endTable[kPickleData]["colour"] = &GLLightDef::HandleColourEnd;
    m_startTable[kPickleData]["ambient"] = &GLLightDef::NullHandler;
    m_endTable[kPickleData]["ambient"] = &GLLightDef::HandleAmbientEnd;
    m_startTable[kPickleData]["diffuse"] = &GLLightDef::NullHandler;
    m_endTable[kPickleData]["diffuse"] = &GLLightDef::HandleDiffuseEnd;
    m_startTable[kPickleData]["specular"] = &GLLightDef::NullHandler;
    m_endTable[kPickleData]["specular"] = &GLLightDef::HandleSpecularEnd;
    m_startTable[kPickleData]["cutoff"] = &GLLightDef::NullHandler;
    m_endTable[kPickleData]["cutoff"] = &GLLightDef::HandleCutoffEnd;
    m_startTable[kPickleData]["direction"] = &GLLightDef::NullHandler;
    m_endTable[kPickleData]["direction"] = &GLLightDef::HandleDirectionEnd;
    m_startTable[kPickleData]["exponent"] = &GLLightDef::NullHandler;
    m_endTable[kPickleData]["exponent"] = &GLLightDef::HandleExponentEnd;
    m_startTable[kPickleData]["constant"] = &GLLightDef::NullHandler;
    m_endTable[kPickleData]["constant"] = &GLLightDef::HandleConstantEnd;
    m_startTable[kPickleData]["linear"] = &GLLightDef::NullHandler;
    m_endTable[kPickleData]["linear"] = &GLLightDef::HandleLinearEnd;
    m_startTable[kPickleData]["quadratic"] = &GLLightDef::NullHandler;
    m_endTable[kPickleData]["quadratic"] = &GLLightDef::HandleQuadraticEnd;
    m_endTable[kPickleData]["light"] = &GLLightDef::HandleLightEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;

    m_offset=GLVector(0,0,0);
    m_basePosition=GLVector(0,0,0);
    m_position=GLVector(0,0,0);
    m_ambient=GLColour(0,0,0,0);
    m_diffuse=GLColour(1,1,1,1);
    m_specular=GLColour(1,1,1,1);
    m_cutoff=180;
    m_direction=GLVector(0,0,1);
    m_exponent=0;
    m_constant=0.0001;
    m_linear=0;
    m_quadratic=1;
}

void
GLLightDef::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GLLightDef::UnpickleEpilogue(void)
{
    m_startTable.resize(0);
    m_endTable.resize(0);
}

void
GLLightDef::XMLStartHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        //        if (m_pickleState == kPickleData)
        //        {
        //            GameGraphic::XMLStartHandler(inXML);
        //            m_pickleState=kPickleWithinBase;
        //            ++m_baseThreaded;
        //        }
        //        else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << "> in GLLightDef.  Potential matches are";
ElementFunctionMap::iterator p = m_startTable[m_pickleState].begin();
        while (p != m_startTable[m_pickleState].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
    }
}

void
GLLightDef::XMLEndHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        //        if (m_pickleState == kPickleWithinBase)
        //        {
        //          GameGraphic::XMLEndHandler(inXML);
        //            --m_baseThreaded;
        //            if (m_baseThreaded == 0)
        //            {
        //                m_pickleState=kPickleData;
        //            }
        //        }
        //        else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << "> in GLLightDef.  Potential matches are";
ElementFunctionMap::iterator p = m_endTable[m_pickleState].begin();
        while (p != m_endTable[m_pickleState].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
    }
}

void
GLLightDef::XMLDataHandler(CoreXML& inXML)
{
}

char *
GLLightDef::TypeNameGet(void) const
{
    return "gllightdef";
}

