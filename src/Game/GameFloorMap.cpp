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
 * $Id: GameFloorMap.cpp,v 1.32 2002/10/11 20:10:14 southa Exp $
 * $Log: GameFloorMap.cpp,v $
 * Revision 1.32  2002/10/11 20:10:14  southa
 * Various fixes and new files
 *
 * Revision 1.31  2002/10/11 14:01:12  southa
 * Lighting work
 *
 * Revision 1.30  2002/10/10 22:47:57  southa
 * Full light definitions
 *
 * Revision 1.29  2002/10/10 18:25:15  southa
 * Light links and test lights
 *
 * Revision 1.28  2002/10/10 13:51:16  southa
 * Speed fixes and various others
 *
 * Revision 1.27  2002/10/08 21:44:10  southa
 * 3D maps
 *
 * Revision 1.26  2002/10/08 17:13:17  southa
 * Tiered maps
 *
 * Revision 1.25  2002/10/07 17:49:45  southa
 * Multiple values per map element
 *
 * Revision 1.24  2002/10/06 22:09:59  southa
 * Initial lighting test
 *
 * Revision 1.23  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.22  2002/08/18 20:44:34  southa
 * Initial chequepoint work
 *
 * Revision 1.21  2002/08/18 15:13:15  southa
 * Adhesion handling
 *
 * Revision 1.20  2002/08/16 19:46:07  southa
 * MediaSound work
 *
 * Revision 1.19  2002/08/08 18:20:30  southa
 * Plot on screen of dimension 1.0
 *
 * Revision 1.18  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.17  2002/08/02 15:20:55  southa
 * Frame rate timing
 *
 * Revision 1.16  2002/08/01 16:47:11  southa
 * First multi-box collsion checking
 *
 * Revision 1.15  2002/07/31 16:27:16  southa
 * Collision checking work
 *
 * Revision 1.14  2002/07/19 17:51:11  southa
 * Texture tweaks
 *
 * Revision 1.13  2002/07/19 15:44:41  southa
 * Graphic optimisations
 *
 * Revision 1.12  2002/07/16 19:30:09  southa
 * Simplistic collision checking
 *
 * Revision 1.11  2002/07/16 17:48:08  southa
 * Collision and optimisation work
 *
 * Revision 1.10  2002/07/10 16:16:30  southa
 * Player graphic
 *
 * Revision 1.9  2002/07/08 14:22:02  southa
 * Rotated desks
 *
 * Revision 1.8  2002/07/07 11:16:07  southa
 * More designer work
 *
 * Revision 1.7  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.6  2002/07/02 19:29:02  southa
 * Tidied up selection effect in designer
 *
 * Revision 1.5  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 * Revision 1.4  2002/07/02 14:27:10  southa
 * First floor map designer build
 *
 * Revision 1.3  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/04 14:12:26  southa
 * Traits loader first stage
 *
 * Revision 1.1  2002/05/30 16:21:53  southa
 * Pickleable GameContract
 *
 * Revision 1.5  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.4  2002/05/28 13:05:55  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.3  2002/05/26 16:08:48  southa
 * CoreXML loader
 *
 * Revision 1.2  2002/05/25 17:16:15  southa
 * CoreXML implementation
 *
 * Revision 1.1  2002/05/24 18:08:35  southa
 * CoreXML and game map
 *
 */

#include "GameFloorMap.h"
#include "GameData.h"
#include "GameTileMap.h"
#include "GameTileTraits.h"
#include "GameMapArea.h"
#include "GameMapPoint.h"
#include "GameSpacePoint.h"

CoreInstaller GameFloorMapInstaller(GameFloorMap::Install);

GameFloorMap::tMapVector GameFloorMap::m_emptyMapVector;

const GameMapPoint
GameFloorMap::SpaceToMapFractional(const GameSpacePoint inPoint) const
{
    GameMapPoint retVal(inPoint / GLPoint(m_xstep, m_ystep));
    return retVal;
}

const GameMapPoint
GameFloorMap::SpaceToMap(const GameSpacePoint inPoint) const
{
    GameMapPoint retVal(inPoint / GLPoint(m_xstep, m_ystep));
    retVal += GLPoint(0.5,0.5);
    retVal.MakeInteger();
    return retVal;
}

const GameSpacePoint
GameFloorMap::MapToSpace(const GameMapPoint inPoint) const
{
    return GameSpacePoint(inPoint * GLPoint(m_xstep, m_ystep));
}

bool
GameFloorMap::IsInMap(const GameMapPoint inPoint) const
{
    return inPoint.x > 0 && inPoint.x < m_xsize && inPoint.y > 0 && inPoint.y < m_ysize;
}

void
GameFloorMap::Render(const GameMapArea& inArea, const GameMapArea& inHighlight, const vector<bool>& inTierHighlight)
{
    COREASSERT(m_tileMap != NULL);

    if (!m_lightMapValid)
    {
        RebuildLightMap();
    }
    
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());
    U32 timeNow=glAppHandler.MillisecondsGet();
    tVal xv=50*cos(timeNow/450.0);
    tVal yv=50*sin(timeNow/450.0);
    
    GLUtils gl;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    gl.SetPosition(0,0);
    GLUtils::Scale(m_xstep, m_ystep, 1);
    GLState::ColourSet(1,1,1);
    GLPoint minPoint=inArea.MinPointGet();
    GLPoint maxPoint=inArea.MaxPointGet();

    GLRectangle wholeMap(0, 0, m_xsize, m_ysize);
    wholeMap.ConstrainPoint(minPoint);
    wholeMap.ConstrainPoint(maxPoint);

    minPoint.MakeInteger();
    maxPoint.MakeInteger();

    bool isHighlight = !inHighlight.IsEmpty();

    bool highlightOn=false;
    GLState::ModulationSet(GLState::kModulationLighting);

    U32 areaXSize=maxPoint.U32XGet() - minPoint.U32XGet();
    U32 areaXMin=minPoint.U32XGet();
    U32 areaXMax=maxPoint.U32XGet();
    U32 areaYSize=maxPoint.U32YGet() - minPoint.U32YGet();
    U32 areaYMin=minPoint.U32YGet();
    U32 areaYMax=maxPoint.U32YGet();

    tValarray<bool> areaFlags(areaXSize*areaYSize);
    
    for (U32 x=areaXMin; x<areaXMax; ++x)
    {
        for (U32 y=areaYMin; y<areaYMax; ++y)
        {

            U32 areaFlagIndex=(x-areaXMin) * areaYSize + (y-areaYMin);
            COREASSERT(areaFlagIndex < areaXSize * areaYSize);
            areaFlags[areaFlagIndex] =
                inArea.IsWithin(GLPoint(x,y));
        }
    }

    GLLights *pLights=GLData::Instance().LightsGet();
    pLights->DisableAll();
    GameLightLinks lastLinks;
    U32 lightChangeCtr=0;
    
    U32 m_numTiers=5;
    U32 tierHighlightSize=inTierHighlight.size();
    for (U32 tier=0; tier<m_numTiers; ++tier)
    {
        if (tier < tierHighlightSize)
        {
            if (inTierHighlight[tier])
            {
                GLState::AmbientLightSet(1.0);
            }
            else
            {
                GLState::AmbientLightSet(0.2);
            }
        }
        for (U32 x=areaXMin; x<areaXMax; ++x)
        {
            for (U32 y=areaYMin; y<areaYMax; ++y)
            {
                U32 areaFlagIndex=(x-areaXMin) * areaYSize + (y-areaYMin);
                COREASSERT(areaFlagIndex < areaXSize * areaYSize);

                if (areaFlags[areaFlagIndex])
                {
                    const tMapVector& mapVector=m_map[y][x];
                    U32 vecSize=mapVector.size();

                    if (tier < vecSize && mapVector[tier] != 0)
                    {
                        if (isHighlight)
                        {
                            if (inHighlight.IsWithin(GLPoint(x,y)))
                            {
                                tVal clockNow=timeNow+x*xv+y*yv;
                                tVal redBri=0.4+0.35*sin(clockNow/200.0);
                                tVal greenBri=0.4+0.35*sin(clockNow/201.0);
                                tVal blueBri=0.4+0.35*sin(clockNow/202.0);

                                GLState::ColourSet(redBri, greenBri, blueBri);
                                GLState::ModulationSet(GLState::kModulationColour);
                                highlightOn=true;
                            }
                            else if (highlightOn)
                            {
                                GLState::ModulationSet(GLState::kModulationLighting);
                                highlightOn=false;
                            }
                        }
                        

                        GameTileTraits& tileTraits=dynamic_cast<GameTileTraits &>
                            (*m_tileMap->TraitsPtrGet(mapVector[tier]));

                        const GameLightLinks& links=m_lightMap.ElementGet(x,y);

                        if (links != lastLinks)
                        {
                            U32 lastLinksSize=lastLinks.SizeGet();
                            for (U32 link=0; link<lastLinksSize && lastLinks.ValidGet(link); ++link)
                            {
                                pLights->LightDisable(lastLinks.LinkGet(link));
                            }
                            U32 linksSize=links.SizeGet();
                            for (U32 link=0; link<linksSize && links.ValidGet(link); ++link)
                            {
                                gl.MoveTo(0,0);
                                pLights->LightEnable(links.LinkGet(link));
                            }
                            lastLinks=links;
                            lightChangeCtr++;
                        }
                            
                        gl.MoveTo(x, y);
                        tileTraits.Render();
                    }
                }
            }
        }
    }
    glPopMatrix();
    // cerr << "Light changes=" << lightChangeCtr << endl;
}

void
GameFloorMap::RenderSolidMap(const GameMapArea& inArea)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    if (!m_solidMapValid)
    {
        RebuildSolidMap();
    }
    m_solidMap.Render(inArea);
    glPopMatrix();
}

const GameFloorMap::tMapVector&
GameFloorMap::ElementGet(const GLPoint &inPoint) const
{
    COREASSERT(inPoint.x < m_xsize);
    COREASSERT(inPoint.y < m_ysize);
    return m_map[inPoint.U32YGet()][inPoint.U32XGet()];
}

const GameFloorMap::tMapVector&
GameFloorMap::ElementGet(const GameSpacePoint& inPoint) const
{
    GameMapPoint mapPoint(SpaceToMap(inPoint));
    return ElementGet(mapPoint);
}

const GameFloorMap::tMapVector&
GameFloorMap::ElementGet(const GameMapPoint& inPoint) const
{
    if (inPoint.x < 0 || inPoint.y < 0) return m_emptyMapVector;
    U32 x=static_cast<U32>(inPoint.x+0.5);
    U32 y=static_cast<U32>(inPoint.y+0.5);
    if (x >= m_xsize || y>= m_ysize) return m_emptyMapVector;
    return m_map[y][x];
}

void
GameFloorMap::ElementSet(const GLPoint &inPoint, const tMapVector& inValue)
{
    COREASSERT(inPoint.x < m_xsize);
    COREASSERT(inPoint.y < m_ysize);
    if (m_map.size() < inPoint.y)
    {
        cerr << "Warning: Had to grow map vector to accomodate y=" << inPoint.y << endl;
        m_map.resize(inPoint.U32YGet()+1);
    }
    if (m_map[inPoint.U32YGet()].size() < inPoint.x)
    {
        cerr << "Warning: Had to grow map vector to accomodate x=" << inPoint.x << endl;
        m_map[inPoint.U32YGet()].resize(inPoint.U32XGet()+1);
    }
    m_map[inPoint.U32YGet()][inPoint.U32XGet()]=inValue;
}

tVal
GameFloorMap::PermeabilityGet(const GameMapPoint &inPoint) const
{
    if (!m_solidMapValid)
    {
        RebuildSolidMap();
    }
    return m_solidMap.PermeabilityGet(inPoint);
}

tVal
GameFloorMap::AdhesionGet(const GameMapPoint &inPoint) const
{
    if (!m_solidMapValid)
    {
        RebuildSolidMap();
    }
    return m_solidMap.AdhesionGet(inPoint);
}

tVal
GameFloorMap::AdhesionGet(const GameSpacePoint &inPoint) const
{
    if (!m_solidMapValid)
    {
        RebuildSolidMap();
    }
    return m_solidMap.AdhesionGet(inPoint);
}

void
GameFloorMap::SetLightingFor(const GameSpacePoint& inPoint) const
{
    GameMapPoint mapPoint(SpaceToMap(inPoint));
    return SetLightingFor(mapPoint);
}

void
GameFloorMap::SetLightingFor(const GameMapPoint &inPoint) const
{
    GLLights *pLights=GLData::Instance().LightsGet();
    pLights->DisableAll();
    if (IsInMap(inPoint))
    {
        if (!m_lightMapValid)
        {
            RebuildLightMap();
        }
        const GameLightLinks& links=m_lightMap.ElementGet(inPoint.x,inPoint.y);
        U32 linksSize=links.SizeGet();
        for (U32 link=0; link<linksSize && links.ValidGet(link); ++link)
        {
            pLights->LightEnable(links.LinkGet(link));
        }
    }
}    

const GameSolidMap&
GameFloorMap::SolidMapGet(void) const
{
    if (!m_solidMapValid)
    {
        RebuildSolidMap();
    }
    return m_solidMap;
}
void
GameFloorMap::RebuildSolidMap(void) const
{
    COREASSERT(m_tileMap != NULL);

    m_solidMap.SizeSet(m_xsize, m_ysize);
    m_solidMap.StepSet(m_xstep, m_ystep);
    for (U32 x=0; x<m_xsize; ++x)
    {
        for (U32 y=0; y<m_ysize; ++y)
        {
            const tMapVector& mapVec=ElementGet(GLPoint(x,y));
            U32 size=mapVec.size();
            tVal adhesion=-1;
            tVal permeability=4;
            for (U32 i=0; i<size; ++i)
            {
                GameTileTraits& tileTraits=
                dynamic_cast<GameTileTraits &>(*m_tileMap->TraitsPtrGet(mapVec[i]));

                tVal value;
                if (tileTraits.PermeabilityGet(value))
                {
                    if (value < permeability) permeability = value;
                }

                if (tileTraits.AdhesionGet(value))
                {
                    if (value > adhesion) adhesion = value;
                }
            }
            if (adhesion < 0 || adhesion > 1.0 || permeability < 0 || permeability >= 4)
            {

                ostringstream message;
                message << "TileTrait [";
                for (U32 i=0; i<size; ++i)
                {
                    GameTileTraits& tileTraits=
                    dynamic_cast<GameTileTraits &>(*m_tileMap->TraitsPtrGet(mapVec[i]));
                    cerr << tileTraits << endl;
                    message << mapVec[i];
                    if (i+1 != size) message << ",";
                }
                message << "] bad adhesion or permeability value at (" << x << "," << y << ")";
                throw(ReferenceFail(message.str()));
            }
            m_solidMap.PermeabilitySet(permeability, x, y);
            m_solidMap.AdhesionSet(adhesion, x, y);
        }
    }
    m_solidMapValid=true;
}

void
GameFloorMap::RebuildLightMap(void) const
{
    COREASSERT(m_tileMap != NULL);

    m_lightMap.SizeSet(m_xsize, m_ysize);

    vector<GLLightDef> lightDefs;
    
    // Collect lights
    for (U32 x=0; x<m_xsize; ++x)
    {
        for (U32 y=0; y<m_ysize; ++y)
        {
            const tMapVector& mapVec=ElementGet(GLPoint(x,y));
            U32 size=mapVec.size();

            for (U32 i=0; i<size; ++i)
            {
                GameTileTraits& tileTraits=
                dynamic_cast<GameTileTraits &>(*m_tileMap->TraitsPtrGet(mapVec[i]));

                GLLightDef lightDef;
                if (tileTraits.LightGet(lightDef))
                {
                    lightDef.BasePositionSet(GLVector(x,y,0));
                    GLData::Instance().LightsGet()->LightAdd(lightDefs.size(), lightDef);
                    lightDefs.push_back(lightDef);
                }
            }
        }
    }
    // cerr << "Num lights=" << lightDefs.size() << endl;
    // Link each tile position to the nearest lights
    GameLightLinks lightLinks;
    U32 linksSize=lightLinks.SizeGet();
    
    U32 lightDefsSize=lightDefs.size();
    
    for (U32 x=0; x<m_xsize; ++x)
    {
        for (U32 y=0; y<m_ysize; ++y)
        {
            // Looping over the map
            lightLinks=GameLightLinks();
            GLVector here(x,y,0);
            for (U32 light=0; light<lightDefsSize; ++light)
            {
                // Looping over each light which we read into the lightDefs above
                tVal distance = (here - lightDefs[light].PositionGet()).Magnitude();

                bool slotFound=false;
                U32 linkSlot=0;
                tVal linkDistance;
                
                for (U32 link=0; link<linksSize; ++link)
                {
                    // Looping over each light link slot for this map position
                    if (!lightLinks.ValidGet(link))
                    {
                        // Empty slot, so fill immediately
                        slotFound=true;
                        linkSlot=link;
                        linkDistance=distance;
                        break;
                    }
                    
                    if (distance < lightLinks.DistanceGet(link))
                    {
                        // If we could replace this link because we're closer...
                        if (!slotFound ||
                            lightLinks.DistanceGet(link) > lightLinks.DistanceGet(linkSlot))
                        {
                            // If this slot is weaker than the current slot we had in mind...
                            slotFound=true;
                            linkSlot=link;
                            linkDistance=distance;
                        }
                    }
                }
                if (slotFound)
                {
                    lightLinks.LinkSet(linkSlot, light);
                    lightLinks.DistanceSet(linkSlot, distance);
                    lightLinks.ValidSet(linkSlot, true);
                }
            }
            lightLinks.Sort();
            m_lightMap.ElementSet(lightLinks, x, y);
        }
    }
    m_lightMapValid=true;
}

void
GameFloorMap::RenderLightMap(const GameMapArea& inArea) const
{
    if (!m_lightMapValid)
    {
        RebuildLightMap();
    }
    GLUtils::PushMatrix();
    GLUtils::Scale(m_xstep, m_ystep, 1);
    GLPoint minPoint=inArea.MinPointGet();
    GLPoint maxPoint=inArea.MaxPointGet();

    GLRectangle wholeMap(0, 0, m_xsize, m_ysize);
    wholeMap.ConstrainPoint(minPoint);
    wholeMap.ConstrainPoint(maxPoint);

    minPoint.MakeInteger();
    maxPoint.MakeInteger();

    GLPoint point;
    GLState::BlendSet(GLState::kBlendLine);
    GLState::ModulationSet(GLState::kModulationColour);
    GLState::ColourSet(1, 1, 1, 0.2);
    
    for (point.x=minPoint.x; point.x<maxPoint.x; ++point.x)
    {
        for (point.y=minPoint.y; point.y<maxPoint.y; ++point.y)
        {
            if (inArea.IsWithin(point))
            {
                const GameLightLinks& links=m_lightMap.ElementGet(point);
                for (U32 i=0; i<links.SizeGet(); ++i)
                {
                    if (links.ValidGet(i))
                    {
                        U32 lightNum=links.LinkGet(i);

                        GLVector linkVec=GLData::Instance().LightsGet()->LightGet(lightNum).PositionGet();
                        GLLine line(point, GLPoint(linkVec.x, linkVec.y));

                        line.Render();
                    }
                }
            }
        }
    }
    GLUtils::PopMatrix();
}

/* --- XML stuff --- */

void
GameFloorMap::NullHandler(CoreXML& inXML)
{
}

void
GameFloorMap::HandleGameFloorMapStart(CoreXML& inXML)
{
    m_xsize=inXML.GetAttribOrThrow("xsize").U32Get();
    m_ysize=inXML.GetAttribOrThrow("ysize").U32Get();
    CoreScalar temp;
    temp=CoreScalar(1.0);
    inXML.GetAttrib(temp, "xstep");
    m_xstep=temp.ValGet();
    temp=CoreScalar(1.0);
    inXML.GetAttrib(temp, "ystep");
    m_ystep=temp.ValGet();
    if (m_xstep == 0 || m_ystep == 0)
    {
        inXML.Throw("Bad values for x/ystep");
    }
    m_state=kData;
}

void
GameFloorMap::HandleGameFloorMapEnd(CoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameFloorMap::HandleDataEnd(CoreXML& inXML)
{
    istringstream inStream(inXML.TopData());

    tMapValue data;
    vector<tMapVector> rowVector;
    char seperator;

    CoreScalar tierScalar(1);
    inXML.GetAttrib(tierScalar, "tier");
    U32 tier=tierScalar.U32Get();
    if (tier > 0 ) --tier;
    while (inStream >> data)
    {
        tMapVector mapVector(tier, 0);
        mapVector.push_back(data);
        while ((inStream >> seperator) && seperator == '|')
        {
            if (!(inStream >> data))
            {
                inXML.Throw("Bad format for data element");
            }
            mapVector.push_back(data);
        }
        rowVector.push_back(mapVector);

        if (seperator == ',')
        {
            // Move to next element
        }
        else
        {
            break;
        }
    }
    m_map.insert(m_map.begin(), rowVector);
}

void
GameFloorMap::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<gamemap xsize=\"" << m_xsize << "\" ysize=\"" << m_ysize << "\">" << endl;
    for (vector< vector< tMapVector > >::const_reverse_iterator x_it = m_map.rbegin(); x_it != m_map.rend(); ++x_it)
    {
        inOut << inPrefix << "  <data>";
        for (vector< tMapVector >::const_iterator y_it = x_it->begin(); y_it != x_it->end(); ++y_it)
        {
            for (tMapVector::const_iterator z_it = y_it->begin(); z_it != y_it->end(); ++z_it)
            {
                inOut << *z_it;
                if (z_it+1 != y_it->end())
                {
                    inOut << "|";
                }
            }
            if (y_it+1 != x_it->end())
            {
                inOut << ",";
            }
        }
        inOut << "</data>" << endl;
    }
    inOut << inPrefix << "</gamemap>" << endl;
}

void
GameFloorMap::Unpickle(CoreXML& inXML)
{
    m_startTable.resize(kNumStates);
    m_endTable.resize(kNumStates);
    m_startTable[kInit]["gamemap"] = &GameFloorMap::HandleGameFloorMapStart;
    m_startTable[kData]["data"] = &GameFloorMap::NullHandler;
    m_endTable[kData]["gamemap"] = &GameFloorMap::HandleGameFloorMapEnd;
    m_endTable[kData]["data"] = &GameFloorMap::HandleDataEnd;

    m_map.clear();
    inXML.ParseStream(*this);
    if (m_map.size() != m_ysize)
    {
        cerr << "Warning: Data y size does not match map size" << endl;
        m_map.resize(m_ysize);
    }
    for (U32 i=0; i<m_ysize; ++i)
    {
        if (m_map[i].size() != m_xsize)
        {
            cerr << "Warning: Data x size does not match map size at line " << i << endl;
            m_map[i].resize(m_xsize);
        }
    }
}

void
GameFloorMap::XMLStartHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_startTable[m_state].find(inXML.TopTag());

    if (p != m_startTable[m_state].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << ">.  Potential matches are";
ElementFunctionMap::iterator p = m_startTable[m_state].begin();
        while (p != m_startTable[m_state].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
GameFloorMap::XMLEndHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_state].find(inXML.TopTag());

    if (p != m_endTable[m_state].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << ">.  Potential matches are";
ElementFunctionMap::iterator p = m_endTable[m_state].begin();
        while (p != m_endTable[m_state].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
GameFloorMap::XMLDataHandler(CoreXML& inXML)
{
}

CoreScalar
GameFloorMap::LoadFloorMap(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: loadfloormap <name> <filename>"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(LoaderFail(filename, "Could not open file"));
    CoreXML xml(inStream, filename);
    GameData::Instance().FloorMapGetOrCreate(name)->Unpickle(xml);
    return CoreScalar(0);
}

void
GameFloorMap::Install(void)
{
    CoreApp::Instance().AddHandler("loadfloormap", LoadFloorMap);
}

