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
 * $Id: GameFloorMap.cpp,v 1.22 2002/08/18 20:44:34 southa Exp $
 * $Log: GameFloorMap.cpp,v $
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

void
GameFloorMap::Render(const GameMapArea& inArea, const GameMapArea& inHighlight)
{
    COREASSERT(m_tileMap != NULL);

    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());
    U32 timeNow=glAppHandler.MillisecondsGet();
    tVal xv=50*cos(timeNow/450.0);
    tVal yv=50*sin(timeNow/450.0);
    
    GLUtils gl;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    gl.SetPosition(0,0);
    GLUtils::Scale(m_xstep, m_ystep, 1);
    GLUtils::ColourSet(1,1,1);
    GLPoint minPoint=inArea.MinPointGet();
    GLPoint maxPoint=inArea.MaxPointGet();

    GLRectangle wholeMap(0, 0, m_xsize, m_ysize);
    wholeMap.ConstrainPoint(minPoint);
    wholeMap.ConstrainPoint(maxPoint);

    minPoint.MakeInteger();
    maxPoint.MakeInteger();
    
    GLPoint point;
    
    bool highlightOn=true;
    
    for (point.x=minPoint.x; point.x<maxPoint.x; ++point.x)
    {
        for (point.y=minPoint.y; point.y<maxPoint.y; ++point.y)
        {
            if (inArea.IsWithin(point))
            {
                if (inHighlight.IsWithin(point))
                {
                    tVal clockNow=timeNow+point.x*xv+point.y*yv;
                    tVal redBri=0.4+0.35*sin(clockNow/200.0);
                    tVal greenBri=0.4+0.35*sin(clockNow/201.0);
                    tVal blueBri=0.4+0.35*sin(clockNow/202.0);

                    GLUtils::ColourSet(redBri, greenBri, blueBri);
                    GLUtils::ModulateSet(true);
                    highlightOn=true;
                }
                else if (highlightOn)
                {
                    GLUtils::ModulateSet(false);
                    highlightOn=false;
                }
                
                gl.MoveTo(point.x, point.y);
                U32 mapVal=ElementGet(point);
                glPushMatrix();
                GameTileTraits& tileTraits=dynamic_cast<GameTileTraits &>
                    (*m_tileMap->TraitsPtrGet(mapVal));
                tileTraits.Render();
                glPopMatrix();
            }
        }
    }
    glPopMatrix();
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

U32
GameFloorMap::ElementGet(const GLPoint &inPoint) const
{
    COREASSERT(inPoint.x < m_xsize);
    COREASSERT(inPoint.y < m_ysize);
    return m_map[inPoint.U32YGet()][inPoint.U32XGet()];
}

U32
GameFloorMap::ElementGet(const GameSpacePoint& inPoint) const
{
    GameMapPoint mapPoint(SpaceToMap(inPoint));
    return ElementGet(mapPoint);
}

U32
GameFloorMap::ElementGet(const GameMapPoint& inPoint) const
{
    if (inPoint.x < 0 || inPoint.y < 0) return 0;
    U32 x=static_cast<U32>(inPoint.x+0.5);
    U32 y=static_cast<U32>(inPoint.y+0.5);
    if (x >= m_xsize || y>= m_ysize) return 0;
    return m_map[y][x];
}

void
GameFloorMap::ElementSet(const GLPoint &inPoint, U32 inValue)
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
            U32 mapVal=ElementGet(GLPoint(x,y));
            GameTileTraits& tileTraits=
                dynamic_cast<GameTileTraits &>(*m_tileMap->TraitsPtrGet(mapVal));
            tVal value;
            if (!tileTraits.PermeabilityGet(value))
            {
                cerr << tileTraits << endl;
                throw(ReferenceFail("TileTrait missing permeability value"));
            }
            m_solidMap.PermeabilitySet(value, x, y);

            if (!tileTraits.AdhesionGet(value))
            {
                cerr << tileTraits << endl;
                throw(ReferenceFail("TileTrait missing adhesion value"));
            }
            m_solidMap.AdhesionSet(value, x, y);            
        }
    }
    m_solidMapValid=true;
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
    U32 data;
    vector<U32> vec;
    while (inStream >> data)
    {
        char isComma;
        vec.push_back(data);
        if ((inStream >> isComma) && (isComma == ','))
        {
            // Carry on - comma's there so expect more data
        }
        else
        {
            break;
        }
    }
    m_map.insert(m_map.begin(), vec);
}

void
GameFloorMap::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<gamemap xsize=\"" << m_xsize << "\" ysize=\"" << m_ysize << "\">" << endl;
    for (vector< vector<U32> >::const_reverse_iterator x_it = m_map.rbegin(); x_it != m_map.rend(); x_it++)
    {
        inOut << inPrefix << "  <data>";
        for (vector<U32>::const_iterator y_it = x_it->begin(); y_it != x_it->end(); y_it++)
        {
            inOut << *y_it;
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

