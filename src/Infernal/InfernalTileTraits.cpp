//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTileTraits.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } 4yeeFDuU+HH7ozxLKWvUVw
/*
 * $Id: InfernalTileTraits.cpp,v 1.6 2006/06/01 15:39:06 southa Exp $
 * $Log: InfernalTileTraits.cpp,v $
 * Revision 1.6  2006/06/01 15:39:06  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:06  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.3  2004/01/01 21:15:46  southa
 * Created XCode project
 *
 * Revision 1.2  2003/10/04 15:32:11  southa
 * Module split
 *
 * Revision 1.1  2003/10/04 12:23:07  southa
 * File renaming
 *
 * Revision 1.28  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
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

#include "InfernalTileTraits.h"

#include "InfernalSTL.h"

#include "mushGame.h"

using namespace Mushware;
using namespace std;

InfernalTileTraits::~InfernalTileTraits()
{
    for (U32 i=0; i<m_graphics.size(); ++i)
    {
        delete m_graphics[i];
    }
    // Delete GL list
    // glDeleteLists(m_listName, 1);
}

void
InfernalTileTraits::Render(void)
{
    U32 traitsSize=NumberOfTraitsGet();
    for (U32 i=0; i<traitsSize; ++i)
    {
        dynamic_cast<InfernalTileTraits&>(TraitsGet(i)).Render();
    }

    U32 graphicsSize=m_graphics.size();

    for (U32 i=0; i<graphicsSize; ++i)
    {
        m_graphics[i]->Render();
    }
}

bool
InfernalTileTraits::PermeabilityGet(tVal& outPermeability) const
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
        InfernalTileTraits& traits=dynamic_cast<InfernalTileTraits&>(TraitsGet(i));
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
InfernalTileTraits::AdhesionGet(tVal& outAdhesion) const
{
    // Adhesion return the first value it finds
    if (m_hasAdhesion)
    {
        outAdhesion=m_adhesion;
        return true;
    }

    for (U32 i=0; i<NumberOfTraitsGet(); ++i)
    {
        InfernalTileTraits& traits=dynamic_cast<InfernalTileTraits&>(TraitsGet(i));
        if (traits.AdhesionGet(outAdhesion))
        {
            return true;
        }
    }
    return false;
}

bool
InfernalTileTraits::LightGet(GLLightDef& outLight) const
{
    if (m_hasLight)
    {
        outLight=m_light;
        return true;
    }

    for (U32 i=0; i<NumberOfTraitsGet(); ++i)
    {
        InfernalTileTraits& traits=dynamic_cast<InfernalTileTraits&>(TraitsGet(i));
        if (traits.LightGet(outLight))
        {
            return true;
        }
    }

    return false;
}


void
InfernalTileTraits::NullHandler(MushcoreXML& inXML)
{
}

void
InfernalTileTraits::HandleGraphicStart(MushcoreXML& inXML)
{
    string typeStr=inXML.GetAttribOrThrow("type").StringGet();
    GameGraphic& graphic(GameGraphic::NewFromType(typeStr));
    m_graphics.push_back(&graphic);
    graphic.Unpickle(inXML);
}

void
InfernalTileTraits::HandlePermeabilityEnd(MushcoreXML& inXML)
{
    istringstream inStream(inXML.TopData());
    if (!(inStream >> m_permeability)) inXML.Throw("Expecting <permeability>1.0</permeability>");
    m_hasPermeability=true;
}

void
InfernalTileTraits::HandleAdhesionEnd(MushcoreXML& inXML)
{
    istringstream inStream(inXML.TopData());
    if (!(inStream >> m_adhesion)) inXML.Throw("Expecting <adhesion>1.0</adhesion>");
    m_hasAdhesion=true;
}

void
InfernalTileTraits::HandleLightStart(MushcoreXML& inXML)
{
    m_light.Unpickle(inXML);
    m_hasLight=true;
}

void
InfernalTileTraits::HandleTraitsEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
}

void
InfernalTileTraits::Pickle(ostream& inOut, const string& inPrefix) const
{
    InfernalTraits::Pickle(inOut, inPrefix);
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
InfernalTileTraits::Unpickle(MushcoreXML& inXML)
{
    InfernalTraits::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["graphic"] = &InfernalTileTraits::HandleGraphicStart;
    m_startTable[kPickleData]["permeability"] = &InfernalTileTraits::NullHandler;
    m_endTable[kPickleData]["permeability"] = &InfernalTileTraits::HandlePermeabilityEnd;
    m_startTable[kPickleData]["adhesion"] = &InfernalTileTraits::NullHandler;
    m_endTable[kPickleData]["adhesion"] = &InfernalTileTraits::HandleAdhesionEnd;
    m_startTable[kPickleData]["light"] = &InfernalTileTraits::HandleLightStart;
    m_endTable[kPickleData]["traits"] = &InfernalTileTraits::HandleTraitsEnd;
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
InfernalTileTraits::XMLStartHandler(MushcoreXML& inXML)
{
    ElementFunctionMap::iterator p2 = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p2 != m_startTable[m_pickleState].end())
    {
        (this->*p2->second)(inXML);
    }
    else
    {
        if (m_pickleState == kPickleData)
        {
            InfernalTraits::XMLStartHandler(inXML);
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
InfernalTileTraits::XMLEndHandler(MushcoreXML& inXML)
{
    ElementFunctionMap::iterator p2 = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p2 != m_endTable[m_pickleState].end())
    {
        (this->*p2->second)(inXML);
    }
    else
    {
        if (m_pickleState == kPickleWithinBase)
        {
            InfernalTraits::XMLEndHandler(inXML);
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
InfernalTileTraits::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
InfernalTileTraits::TypeNameGet(void) const
{
    return "gametiletraits";
}
