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
 * $Id: GameTileTraits.cpp,v 1.11 2002/08/07 13:36:51 southa Exp $
 * $Log: GameTileTraits.cpp,v $
 * Revision 1.11  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.10  2002/07/18 11:40:36  southa
 * Overplotting and movement
 *
 * Revision 1.9  2002/07/16 19:30:09  southa
 * Simplistic collision checking
 *
 * Revision 1.8  2002/07/16 17:48:09  southa
 * Collision and optimisation work
 *
 * Revision 1.7  2002/07/08 14:22:03  southa
 * Rotated desks
 *
 * Revision 1.6  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.4  2002/06/05 12:28:05  southa
 * Map rendered using traits
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

#include "GameTileTraits.h"
#include "GameGraphicSprite.h"

GameTileTraits::~GameTileTraits()
{
    for (U32 i=0; i<m_graphics.size(); ++i)
    {
        delete m_graphics[i];
    }
}

void
GameTileTraits::Render(void)
{
    for (U32 i=0; i<NumberOfTraitsGet(); ++i)
    {
        dynamic_cast<GameTileTraits&>(TraitsGet(i)).Render();
    }
    for (U32 i=0; i<m_graphics.size(); ++i)
    {
        m_graphics[i]->Render();
    }
}

bool
GameTileTraits::PermeabilityGet(tVal& outPermeability) const
{
    outPermeability=1;
    bool foundPerm=false;
    if (m_hasPermeability)
    {
        outPermeability=m_permeability;
        foundPerm=true;
    }

    for (U32 i=0; i<NumberOfTraitsGet(); ++i)
    {
        tVal newPerm;
        GameTileTraits& traits=dynamic_cast<GameTileTraits&>(TraitsGet(i));
        if (traits.PermeabilityGet(newPerm))
        {
            if (!foundPerm || newPerm < outPermeability)
            {
                outPermeability=newPerm;
                foundPerm=true;
            }
        }
    }

    // This logic is flawed.  Only works at the top level
    static bool notWarnedYet=true;
    if (!foundPerm && notWarnedYet)
    {
        cerr << "Warning: GameTileTrait with unknown permeability:" << endl;
        Pickle(cerr);
        notWarnedYet=false;
    }
    return foundPerm;
}

bool
GameTileTraits::AdhesionGet(tVal& outAdhesion) const
{
    outAdhesion=1;
    if (m_hasAdhesion)
    {
        outAdhesion=m_adhesion;
        return true;
    }
    
    for (U32 i=0; i<NumberOfTraitsGet(); ++i)
    {
        GameTileTraits& traits=dynamic_cast<GameTileTraits&>(TraitsGet(i));
        if (traits.AdhesionGet(outAdhesion))
        {
            return true;
        }
    }

    return false;
}


void
GameTileTraits::NullHandler(CoreXML& inXML)
{
}

void
GameTileTraits::HandleGraphicStart(CoreXML& inXML)
{
    GameGraphicSprite *pSprite(new GameGraphicSprite);
    m_graphics.push_back(pSprite);
    pSprite->Unpickle(inXML);
}

void
GameTileTraits::HandlePermeabilityEnd(CoreXML& inXML)
{
    istringstream inStream(inXML.TopData());
    if (!(inStream >> m_permeability)) inXML.Throw("Expecting <permeability>1.0</permeability>");
    m_hasPermeability=true;
}

void
GameTileTraits::HandleAdhesionEnd(CoreXML& inXML)
{
    istringstream inStream(inXML.TopData());
    if (!(inStream >> m_adhesion)) inXML.Throw("Expecting <adhesion>1.0</adhesion>");
    m_hasAdhesion=true;
}

void
GameTileTraits::HandleTraitsEnd(CoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameTileTraits::Pickle(ostream& inOut, const string& inPrefix="") const
{
    GameTraits::Pickle(inOut, inPrefix);
    for (U32 i=0; i<m_graphics.size(); ++i)
    {
        inOut << inPrefix << "<graphic type=\"" << m_graphics[i]->TypeNameGet() << "\">" << endl;
        m_graphics[i]->Pickle(inOut, inPrefix+"  ");
        inOut << inPrefix << "</graphic>" << endl;
    }
    if (m_hasPermeability)
    {
        inOut << inPrefix << "<permeability>" << m_permeability << "</permeability>" << endl;
    }
}

void
GameTileTraits::Unpickle(CoreXML& inXML)
{
    GameTraits::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["graphic"] = &GameTileTraits::HandleGraphicStart;
    m_startTable[kPickleData]["permeability"] = &GameTileTraits::NullHandler;
    m_endTable[kPickleData]["permeability"] = &GameTileTraits::HandlePermeabilityEnd;
    m_startTable[kPickleData]["adhesion"] = &GameTileTraits::NullHandler;
    m_endTable[kPickleData]["adhesion"] = &GameTileTraits::HandleAdhesionEnd;
    m_endTable[kPickleData]["traits"] = &GameTileTraits::HandleTraitsEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    m_permeability=1.001;
    m_hasPermeability=false;
    m_adhesion=1.001;
    m_hasAdhesion=false;
    inXML.ParseStream(*this);
}

void
GameTileTraits::XMLStartHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        if (m_pickleState == kPickleData)
        {
            GameTraits::XMLStartHandler(inXML);
            m_pickleState=kPickleWithinBase;
            ++m_baseThreaded;
        }
        else
        {
            ostringstream message;
            message << "Unexpected tag <" << inXML.TopTag() << "> in TileTraits.  Potential matches are";
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
GameTileTraits::XMLEndHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        if (m_pickleState == kPickleWithinBase)
        {
            GameTraits::XMLEndHandler(inXML);
            --m_baseThreaded;
            if (m_baseThreaded == 0)
            {
                m_pickleState=kPickleData;
            }
        }
        else
        {
            ostringstream message;
            message << "Unexpected end of tag </" << inXML.TopTag() << "> in TileTraits.  Potential matches are";
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
GameTileTraits::XMLDataHandler(CoreXML& inXML)
{
}
