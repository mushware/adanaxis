//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalFloorMap.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 2fmRrjQdlXl0zix4qq0b6w
/*
 * $Id: InfernalFloorMap.cpp,v 1.2 2003/10/04 15:32:10 southa Exp $
 * $Log: InfernalFloorMap.cpp,v $
 * Revision 1.2  2003/10/04 15:32:10  southa
 * Module split
 *
 * Revision 1.1  2003/10/04 12:23:05  southa
 * File renaming
 *
 * Revision 1.50  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.49  2003/08/21 23:08:44  southa
 * Fixed file headers
 *
 * Revision 1.48  2003/01/20 12:23:21  southa
 * Code and interface tidying
 *
 * Revision 1.47  2003/01/20 10:45:26  southa
 * Singleton tidying
 *
 * Revision 1.46  2003/01/13 14:31:58  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.45  2003/01/12 17:32:54  southa
 * Mushcore work
 *
 * Revision 1.44  2003/01/11 17:07:51  southa
 * Mushcore library separation
 *
 * Revision 1.43  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.42  2003/01/07 17:13:42  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.41  2002/12/29 20:59:55  southa
 * More build fixes
 *
 * Revision 1.40  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.39  2002/12/03 20:28:16  southa
 * Network, player and control work
 *
 * Revision 1.38  2002/11/24 23:18:16  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.37  2002/11/18 11:31:14  southa
 * Return to game mode
 *
 * Revision 1.36  2002/10/22 20:42:04  southa
 * Source conditioning
 *
 * Revision 1.35  2002/10/17 15:50:59  southa
 * Config saving, pause and quit
 *
 * Revision 1.34  2002/10/13 12:26:47  southa
 * Facetised map rendering
 *
 * Revision 1.33  2002/10/12 15:25:13  southa
 * Facet renderer
 *
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
 * Pickleable InfernalContract
 *
 * Revision 1.5  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.4  2002/05/28 13:05:55  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.3  2002/05/26 16:08:48  southa
 * MushcoreXML loader
 *
 * Revision 1.2  2002/05/25 17:16:15  southa
 * MushcoreXML implementation
 *
 * Revision 1.1  2002/05/24 18:08:35  southa
 * MushcoreXML and game map
 *
 */

#include "InfernalFloorMap.h"
#include "InfernalData.h"
#include "InfernalMapArea.h"
#include "InfernalMapPoint.h"
#include "InfernalSTL.h"
#include "InfernalSpacePoint.h"
#include "InfernalTileMap.h"
#include "InfernalTileTraits.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller GameFloorMapInstaller(InfernalFloorMap::Install);

InfernalFloorMap::tMapVector InfernalFloorMap::m_emptyMapVector;

const InfernalMapPoint
InfernalFloorMap::SpaceToMapFractional(const InfernalSpacePoint inPoint) const
{
    InfernalMapPoint retVal(inPoint / GLPoint(m_xstep, m_ystep));
    return retVal;
}

const InfernalMapPoint
InfernalFloorMap::SpaceToMap(const InfernalSpacePoint inPoint) const
{
    InfernalMapPoint retVal(inPoint / GLPoint(m_xstep, m_ystep));
    retVal += GLPoint(0.5,0.5);
    retVal.MakeInteger();
    return retVal;
}

const InfernalSpacePoint
InfernalFloorMap::MapToSpace(const InfernalMapPoint inPoint) const
{
    return InfernalSpacePoint(inPoint * GLPoint(m_xstep, m_ystep));
}

bool
InfernalFloorMap::IsInMap(const InfernalMapPoint inPoint) const
{
    return inPoint.x > 0 && inPoint.x < m_xsize && inPoint.y > 0 && inPoint.y < m_ysize;
}

void
InfernalFloorMap::Render(const InfernalMapArea& inArea, const InfernalMapArea& inHighlight, const vector<bool>& inTierHighlight)
{
    MUSHCOREASSERT(m_tileMap != NULL);

    if (!m_lightMapValid)
    {
        RebuildLightMap();
    }
    
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());
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

    MushwareValarray<bool> areaFlags(areaXSize*areaYSize);
    
    for (U32 x=areaXMin; x<areaXMax; ++x)
    {
        for (U32 y=areaYMin; y<areaYMax; ++y)
        {

            U32 areaFlagIndex=(x-areaXMin) * areaYSize + (y-areaYMin);
            MUSHCOREASSERT(areaFlagIndex < areaXSize * areaYSize);
            areaFlags[areaFlagIndex] =
                inArea.IsWithin(GLPoint(x,y));
        }
    }

    GLLights *pLights=GLData::Sgl().LightsGet();
    pLights->DisableAll();
    InfernalLightLinks lastLinks;
    U32 lightChangeCtr=0;
    
    U32 m_numTiers=5;
    U32 tierHighlightSize=inTierHighlight.size();
    for (U32 tier=0; tier<m_numTiers; ++tier)
    {
        // Don't miss control events
        glAppHandler.PollForControlEvents();
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
                MUSHCOREASSERT(areaFlagIndex < areaXSize * areaYSize);

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
                        
                        const InfernalTileSpec& tileSpec = m_tileMap->TileSpecGet(mapVector[tier]);

                        const InfernalLightLinks& links=m_lightMap.ElementGet(x,y);

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
                        tileSpec.RenderPrologue();
                        tileSpec.TileTraitsGet().Render();
                        tileSpec.RenderEpilogue();
                    }
                }
            }
        }
    }
    glPopMatrix();
    // cerr << "Light changes=" << lightChangeCtr << endl;
}

void
InfernalFloorMap::RenderSolidMap(const InfernalMapArea& inArea) const
{
    if (!m_solidMapValid)
    {
        RebuildSolidMap();
    }
    m_solidMap.RenderSolid(inArea);
}

void
InfernalFloorMap::RenderAdhesionMap(const InfernalMapArea& inArea) const
{
    if (!m_solidMapValid)
    {
        RebuildSolidMap();
    }
    m_solidMap.RenderAdhesion(inArea);
}

const InfernalFloorMap::tMapVector&
InfernalFloorMap::ElementGet(const GLPoint &inPoint) const
{
    MUSHCOREASSERT(inPoint.x < m_xsize);
    MUSHCOREASSERT(inPoint.y < m_ysize);
    return m_map[inPoint.U32YGet()][inPoint.U32XGet()];
}

const InfernalFloorMap::tMapVector&
InfernalFloorMap::ElementGet(const InfernalSpacePoint& inPoint) const
{
    InfernalMapPoint mapPoint(SpaceToMap(inPoint));
    return ElementGet(mapPoint);
}

const InfernalFloorMap::tMapVector&
InfernalFloorMap::ElementGet(const InfernalMapPoint& inPoint) const
{
    if (inPoint.x < 0 || inPoint.y < 0) return m_emptyMapVector;
    U32 x=static_cast<U32>(inPoint.x+0.5);
    U32 y=static_cast<U32>(inPoint.y+0.5);
    if (x >= m_xsize || y>= m_ysize) return m_emptyMapVector;
    return m_map[y][x];
}

void
InfernalFloorMap::ElementSet(const GLPoint &inPoint, const tMapVector& inValue)
{
    MUSHCOREASSERT(inPoint.x < m_xsize);
    MUSHCOREASSERT(inPoint.y < m_ysize);
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
InfernalFloorMap::PermeabilityGet(const InfernalMapPoint &inPoint) const
{
    if (!m_solidMapValid)
    {
        RebuildSolidMap();
    }
    return m_solidMap.PermeabilityGet(inPoint);
}

tVal
InfernalFloorMap::AdhesionGet(const InfernalMapPoint &inPoint) const
{
    if (!m_solidMapValid)
    {
        RebuildSolidMap();
    }
    return m_solidMap.AdhesionGet(inPoint);
}

tVal
InfernalFloorMap::AdhesionGet(const InfernalSpacePoint &inPoint) const
{
    if (!m_solidMapValid)
    {
        RebuildSolidMap();
    }
    return m_solidMap.AdhesionGet(inPoint);
}

void
InfernalFloorMap::SetLightingFor(const InfernalSpacePoint& inPoint) const
{
    InfernalMapPoint mapPoint(SpaceToMap(inPoint));
    return SetLightingFor(mapPoint);
}

void
InfernalFloorMap::SetLightingFor(const InfernalMapPoint &inPoint) const
{
    GLLights *pLights=GLData::Sgl().LightsGet();
    pLights->DisableAll();
    if (IsInMap(inPoint))
    {
        if (!m_lightMapValid)
        {
            RebuildLightMap();
        }
        const InfernalLightLinks& links=m_lightMap.ElementGet(inPoint.U32XGet(),inPoint.U32YGet());
        U32 linksSize=links.SizeGet();
        for (U32 link=0; link<linksSize && links.ValidGet(link); ++link)
        {
            pLights->LightEnable(links.LinkGet(link));
        }
    }
}    

const InfernalSolidMap&
InfernalFloorMap::SolidMapGet(void) const
{
    if (!m_solidMapValid)
    {
        RebuildSolidMap();
    }
    return m_solidMap;
}
void
InfernalFloorMap::RebuildSolidMap(void) const
{
    MUSHCOREASSERT(m_tileMap != NULL);

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
                const InfernalTileSpec& tileSpec=m_tileMap->TileSpecGet(mapVec[i]);

                tVal value;
                if (tileSpec.TileTraitsGet().PermeabilityGet(value))
                {
                    if (value < permeability) permeability = value;
                }

                if (tileSpec.TileTraitsGet().AdhesionGet(value))
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
                    const InfernalTileSpec& tileSpec=m_tileMap->TileSpecGet(mapVec[i]);
                    cerr << tileSpec << endl;
                    message << mapVec[i];
                    if (i+1 != size) message << ",";
                }
                message << "] bad adhesion or permeability value at (" << x << "," << y << ")";
                throw(MushcoreReferenceFail(message.str()));
            }
            m_solidMap.PermeabilitySet(permeability, x, y);
            m_solidMap.AdhesionSet(adhesion, x, y);
        }
    }
    m_solidMapValid=true;
}

void
InfernalFloorMap::RebuildLightMap(void) const
{
    MUSHCOREASSERT(m_tileMap != NULL);

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
                const InfernalTileSpec& tileSpec=m_tileMap->TileSpecGet(mapVec[i]);

                GLLightDef lightDef;
                if (tileSpec.TileTraitsGet().LightGet(lightDef))
                {
                    lightDef.BasePositionSet(GLVector(x,y,0));
                    GLData::Sgl().LightsGet()->LightAdd(lightDefs.size(), lightDef);
                    lightDefs.push_back(lightDef);
                }
            }
        }
    }
    // cerr << "Num lights=" << lightDefs.size() << endl;
    // Link each tile position to the nearest lights
    InfernalLightLinks lightLinks;
    U32 linksSize=lightLinks.SizeGet();
    
    U32 lightDefsSize=lightDefs.size();
    
    for (U32 x=0; x<m_xsize; ++x)
    {
        for (U32 y=0; y<m_ysize; ++y)
        {
            // Looping over the map
            lightLinks=InfernalLightLinks();
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
InfernalFloorMap::RenderLightMap(const InfernalMapArea& inArea) const
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
    GLState::DepthSet(GLState::kDepthNone);
    GLState::ModulationSet(GLState::kModulationColour);
    GLState::BlendSet(GLState::kBlendLine);
    
    GLState::ColourSet(1, 1, 1, 0.2);
    
    for (point.x=minPoint.x; point.x<maxPoint.x; ++point.x)
    {
        for (point.y=minPoint.y; point.y<maxPoint.y; ++point.y)
        {
            if (inArea.IsWithin(point))
            {
                const InfernalLightLinks& links=m_lightMap.ElementGet(point);
                for (U32 i=0; i<links.SizeGet(); ++i)
                {
                    if (links.ValidGet(i))
                    {
                        U32 lightNum=links.LinkGet(i);

                        GLVector linkVec=GLData::Sgl().LightsGet()->LightGet(lightNum).PositionGet();
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
InfernalFloorMap::NullHandler(MushcoreXML& inXML)
{
}

void
InfernalFloorMap::HandleGameFloorMapStart(MushcoreXML& inXML)
{
    m_xsize=inXML.GetAttribOrThrow("xsize").U32Get();
    m_ysize=inXML.GetAttribOrThrow("ysize").U32Get();
    MushcoreScalar temp;
    temp=MushcoreScalar(1.0);
    inXML.GetAttrib(temp, "xstep");
    m_xstep=temp.ValGet();
    temp=MushcoreScalar(1.0);
    inXML.GetAttrib(temp, "ystep");
    m_ystep=temp.ValGet();
    if (m_xstep == 0 || m_ystep == 0)
    {
        inXML.Throw("Bad values for x/ystep");
    }
    m_state=kData;
}

void
InfernalFloorMap::HandleGameFloorMapEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
}

void
InfernalFloorMap::HandleDataEnd(MushcoreXML& inXML)
{
    istringstream inStream(inXML.TopData());

    tMapValue data;
    vector<tMapVector> rowVector;
    char seperator;

    MushcoreScalar tierScalar(1);
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
InfernalFloorMap::Pickle(ostream& inOut, const string& inPrefix) const
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
InfernalFloorMap::Unpickle(MushcoreXML& inXML)
{
    m_startTable.resize(kNumStates);
    m_endTable.resize(kNumStates);
    m_startTable[kInit]["gamemap"] = &InfernalFloorMap::HandleGameFloorMapStart;
    m_startTable[kData]["data"] = &InfernalFloorMap::NullHandler;
    m_endTable[kData]["gamemap"] = &InfernalFloorMap::HandleGameFloorMapEnd;
    m_endTable[kData]["data"] = &InfernalFloorMap::HandleDataEnd;

    m_state=kInit;
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
InfernalFloorMap::XMLStartHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p2 = m_startTable[m_state].find(inXML.TopTag());

    if (p2 != m_startTable[m_state].end())
    {
        (this->*p2->second)(inXML);
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
InfernalFloorMap::XMLEndHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p2 = m_endTable[m_state].find(inXML.TopTag());

    if (p2 != m_endTable[m_state].end())
    {
        (this->*p2->second)(inXML);
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
InfernalFloorMap::XMLDataHandler(MushcoreXML& inXML)
{
}


char *
InfernalFloorMap::TypeNameGet(void) const
{
    return "gamefloormap";
}

MushcoreScalar
InfernalFloorMap::LoadFloorMap(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: loadfloormap <name> <filename>"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(MushcoreFileFail(filename, "Could not open file"));
    MushcoreXML xml(inStream, filename);
    InfernalData::Sgl().FloorMapGetOrCreate(name)->Unpickle(xml);
    return MushcoreScalar(0);
}

void
InfernalFloorMap::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("loadfloormap", LoadFloorMap);
}

