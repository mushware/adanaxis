/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/




/*
 * $Id: GameTraits.cpp,v 1.8 2002/08/27 08:56:27 southa Exp $
 * $Log: GameTraits.cpp,v $
 * Revision 1.8  2002/08/27 08:56:27  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/08 14:22:03  southa
 * Rotated desks
 *
 * Revision 1.5  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.3  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.2  2002/06/04 17:02:11  southa
 * More work
 *
 * Revision 1.1  2002/06/04 14:12:25  southa
 * Traits loader first stage
 *
 */

#include "GameTraits.h"
#include "GameData.h"

void
GameTraits::Verify(void)
{
    if (!m_traitsValid) RebuildTraits();
    if (!m_traitsValid)
    {
        string message("Trait with bases");
        for (U32 i=0; i<m_baseNames.size(); ++i)
        {
            message+=" ";
            message+=m_baseNames[i];
        }
        message+=" failed to build because";
        message+=m_failMessage;
        message+=" were missing";
        throw(VerifyFail(message));
    }
}



void
GameTraits::RebuildTraits(void) const
{
    COREASSERT(!m_traitsValid);
    m_baseTraits.resize(0);
    m_failMessage.erase();
    bool success=true;    
    for (U32 i=0;i<m_baseNames.size(); ++i)
    {
        try
        {
            m_baseTraits.push_back(GameData::Instance().TraitsGet(m_baseNames[i]));
        }
        catch (GameDataNotPresent& e)
        {
            success=false;
            m_failMessage+=" ";
            m_failMessage+=e.StringGet();
        }
    }
    m_traitsValid=success;
}


void
GameTraits::HandleBaseEnd(CoreXML& inXML)
{
    string inStr(inXML.TopData());
    U32 start=0;
    U32 end=0;
    while (end != string::npos && start < inStr.size())
    {
        end=inStr.find(',', start);
        m_baseNames.push_back(inStr.substr(start,end-start));
        start=end+1;
    }
}

void
GameTraits::HandleTraitsEnd(CoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameTraits::NullHandler(CoreXML& inXML)
{
}

void
GameTraits::Pickle(ostream& inOut, const string& inPrefix="") const
{
    if (m_baseNames.size() != 0)
    {
        inOut << inPrefix << "<base>";
        for (U32 i=0; i<m_baseNames.size(); i++)
        {
            inOut << m_baseNames[i];
            if (i+1 < m_baseNames.size()) inOut << ",";
        }
        inOut << "</base>" << endl;
    }
}

void
GameTraits::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["base"] = &GameTraits::NullHandler;
    m_endTable[kPickleData]["base"] = &GameTraits::HandleBaseEnd;
    m_endTable[kPickleData]["traits"] = &GameTraits::HandleTraitsEnd;
    m_pickleState=kPickleData;
    m_baseNames.clear();
}

void
GameTraits::UnpickleEpilogue(void)
{
    m_startTable.clear();
    m_endTable.clear();
}

void
GameTraits::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameTraits::XMLStartHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << "> in Traits.  Potential matches are";
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
GameTraits::XMLEndHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << "> in Traits.  Potential matches are";
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
GameTraits::XMLDataHandler(CoreXML& inXML)
{
}

const string
GameTraits::TraitsNameGet(void) const
{
    return "base";
}

