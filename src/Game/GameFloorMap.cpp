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
 * $Id: GameFloorMap.cpp,v 1.5 2002/07/02 18:36:56 southa Exp $
 * $Log: GameFloorMap.cpp,v $
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

CoreInstaller GameFloorMapInstaller(GameFloorMap::Install);

void
GameFloorMap::Render(const GameTileMap& inTileMap)
{
    GLUtils  gl;
    glMatrixMode(GL_MODELVIEW);
    U32 xsize=XSize();
    U32 ysize=YSize();
    gl.SetPosition(0,0);
    GLUtils::SetColour(1,1,1);
    for (U32 x=0; x<xsize; x++)
    {
        for (U32 y=0; y<ysize; y++)
        {
            U32 mapVal=At(x,y);
            tVal basex=32*x;
            tVal basey=32*y;
            gl.MoveTo(basex,basey);
            GameTileTraits& tileTraits=dynamic_cast<GameTileTraits &>(*inTileMap.TraitsPtrGet(mapVal));
            tileTraits.Render();
        }
    }
}

void
GameFloorMap::Render(const GameTileMap& inTileMap, const GLRectangle& inHighlight)
{
    GLUtils  gl;
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());

    U32 timeNow=glAppHandler.GetMilliseconds();
    tVal xv=50*cos(timeNow/450.0);
    tVal yv=50*sin(timeNow/450.0);
    U32 xsize=XSize();
    U32 ysize=YSize();
    gl.SetPosition(0,0);
    for (U32 x=0; x<xsize; x++)
    {
        for (U32 y=0; y<ysize; y++)
        {
            U32 mapVal=At(x,y);
            tVal basex=m_xstep*x;
            tVal basey=m_ystep*y;
            gl.MoveTo(basex,basey);
            GameTileTraits& tileTraits=dynamic_cast<GameTileTraits &>(*inTileMap.TraitsPtrGet(mapVal));
            if (x>=inHighlight.xmin && x < inHighlight.xmax &&
                y>=inHighlight.ymin && y < inHighlight.ymax)
            {
		tVal clockNow=timeNow+x*xv+y*yv;
	    	tVal redBri=0.4+0.35*sin(clockNow/200.0);
    		tVal greenBri=0.4+0.35*sin(clockNow/201.0);
    		tVal blueBri=0.4+0.35*sin(clockNow/202.0);

                GLUtils::SetColour(redBri, greenBri, blueBri);
            }
            else
            {
                GLUtils::SetColour(1,1,1);
            }
            tileTraits.Render();
        }
    }
}

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
    temp=CoreScalar(32.0);
    inXML.GetAttrib(temp, "xstep");
    m_xstep=temp.ValGet();
    temp=CoreScalar(32.0);
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
    if (vec.size() != m_xsize)
    {
        cerr << "Warning: Data size does not match map size" << endl;
        vec.resize(m_xsize);
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
        cerr << "Warning: Data size does not match map size" << endl;
        m_map.resize(m_ysize);
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

