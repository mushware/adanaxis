//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameTileTraits.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } gQa9T5ShIH0/Fn5CThHB9Q
/*
 * $Id: GameTileTraits.cpp,v 1.27 2003/08/21 23:08:56 southa Exp $
 * $Log: GameTileTraits.cpp,v $
 * Revision 1.27  2003/08/21 23:08:56  southa
 * Fixed file headers
 *
 * Revision 1.26  2003/01/13 14:32:00  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.25  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.24  2003/01/07 17:13:43  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.23  2002/12/29 20:59:57  southa
 * More build fixes
 *
 * Revision 1.22  2002/12/20 13:17:43  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.21  2002/11/24 23:18:25  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.20  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.19  2002/10/14 15:13:40  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.18  2002/10/14 13:03:00  southa
 * Display list test
 *
 * Revision 1.17  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
 * Revision 1.16  2002/10/11 20:10:15  southa
 * Various fixes and new files
 *
 * Revision 1.15  2002/10/10 22:47:57  southa
 * Full light definitions
 *
 * Revision 1.14  2002/10/10 18:25:15  southa
 * Light links and test lights
 *
 * Revision 1.13  2002/08/27 08:56:26  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/18 15:13:16  southa
 * Adhesion handling
 *
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
#include "GameSTL.h"

using namespace Mushware;
using namespace std;

GameTileTraits::~GameTileTraits()
{
    for (U32 i=0; i<m_graphics.size(); ++i)
    {
        delete m_graphics[i];
    }
    // Delete GL list
    // glDeleteLists(m_listName, 1);
}

void
GameTileTraits::Render(void)
{
    U32 traitsSize=NumberOfTraitsGet();
    for (U32 i=0; i<traitsSize; ++i)
    {
        dynamic_cast<GameTileTraits&>(TraitsGet(i)).Render();
    }

    U32 graphicsSize=m_graphics.size();

    for (U32 i=0; i<graphicsSize; ++i)
    {
        m_graphics[i]->Render();
    }
}

bool
GameTileTraits::PermeabilityGet(tVal& outPermeability) const
{
    // Permeability returns the highest value it finds
    bool found=false;
    tVal bestValue=0;
    
    if (m_hasPermeability)
    {
        bestValue=m_permeability;
        found=true;
    }

    for (U32 i=0; i<NumberOfTraitsGet(); ++i)
    {
        tVal newValue;
        GameTileTraits& traits=dynamic_cast<GameTileTraits&>(TraitsGet(i));
        if (traits.PermeabilityGet(newValue))
        {
            if (!found || newValue < bestValue)
            {
                bestValue=newValue;
                found=true;
            }
        }
    }

    if (found) outPermeability=bestValue;
    return found;    
}

bool
GameTileTraits::AdhesionGet(tVal& outAdhesion) const
{
    // Adhesion return the first value it finds
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

bool
GameTileTraits::LightGet(GLLightDef& outLight) const
{
    if (m_hasLight)
    {
        outLight=m_light;
        return true;
    }

    for (U32 i=0; i<NumberOfTraitsGet(); ++i)
    {
        GameTileTraits& traits=dynamic_cast<GameTileTraits&>(TraitsGet(i));
        if (traits.LightGet(outLight))
        {
            return true;
        }
    }

    return false;
}


void
GameTileTraits::NullHandler(MushcoreXML& inXML)
{
}

void
GameTileTraits::HandleGraphicStart(MushcoreXML& inXML)
{
    string typeStr=inXML.GetAttribOrThrow("type").StringGet();
    GameGraphic& graphic(GameGraphic::NewFromType(typeStr));
    m_graphics.push_back(&graphic);
    graphic.Unpickle(inXML);
}

void
GameTileTraits::HandlePermeabilityEnd(MushcoreXML& inXML)
{
    istringstream inStream(inXML.TopData());
    if (!(inStream >> m_permeability)) inXML.Throw("Expecting <permeability>1.0</permeability>");
    m_hasPermeability=true;
}

void
GameTileTraits::HandleAdhesionEnd(MushcoreXML& inXML)
{
    istringstream inStream(inXML.TopData());
    if (!(inStream >> m_adhesion)) inXML.Throw("Expecting <adhesion>1.0</adhesion>");
    m_hasAdhesion=true;
}

void
GameTileTraits::HandleLightStart(MushcoreXML& inXML)
{
    m_light.Unpickle(inXML);
    m_hasLight=true;
}

void
GameTileTraits::HandleTraitsEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameTileTraits::Pickle(ostream& inOut, const string& inPrefix) const
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
    inOut << inPrefix << "<!-- Incomplete -->" << endl;
}

void
GameTileTraits::Unpickle(MushcoreXML& inXML)
{
    GameTraits::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["graphic"] = &GameTileTraits::HandleGraphicStart;
    m_startTable[kPickleData]["permeability"] = &GameTileTraits::NullHandler;
    m_endTable[kPickleData]["permeability"] = &GameTileTraits::HandlePermeabilityEnd;
    m_startTable[kPickleData]["adhesion"] = &GameTileTraits::NullHandler;
    m_endTable[kPickleData]["adhesion"] = &GameTileTraits::HandleAdhesionEnd;
    m_startTable[kPickleData]["light"] = &GameTileTraits::HandleLightStart;
    m_endTable[kPickleData]["traits"] = &GameTileTraits::HandleTraitsEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    m_permeability=-1;
    m_hasPermeability=false;
    m_adhesion=-1;
    m_hasAdhesion=false;
    m_hasLight=false;
    
    inXML.ParseStream(*this);
}

void
GameTileTraits::XMLStartHandler(MushcoreXML& inXML)
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
GameTileTraits::XMLEndHandler(MushcoreXML& inXML)
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
GameTileTraits::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
GameTileTraits::TypeNameGet(void) const
{
    return "gametiletraits";
}
