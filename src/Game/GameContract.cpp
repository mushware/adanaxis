/*
 * $Id: GameContract.cpp,v 1.2 2002/05/28 13:05:55 southa Exp $
 * $Log: GameContract.cpp,v $
 * Revision 1.2  2002/05/28 13:05:55  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.1  2002/05/27 12:58:43  southa
 * GameContract and global configs added
 *
 */

#include "GameContract.h"

#include "mushCore.h"
#include "mushGL.h"

#include "GameMap.h"
#include "GameGlobalConfig.h"

GameContract::GameContract(): m_state(kInit), m_gameMap(NULL)
{
    string appPath(CoreGlobalConfig::Instance().Get("APPLPATH").String());
    GameGlobalConfig::Instance().Set("MAPPATH", appPath+"/../game");
    GameGlobalConfig::Instance().Set("IMAGEPATH", appPath+"/../game");
}

GameContract::~GameContract()
{
    if (m_gameMap != NULL)
    {
        delete m_gameMap;
    }
}

void
GameContract::Process(bool &outDoQuit, bool &outRedraw)
{
    switch (m_state)
    {
        case kInit:
            Init();
            m_state=kRunning;
            break;

        case kRunning:
            Running(outRedraw);
            break;
    }
}

void
GameContract::Display(void)
{
    switch (m_state)
    {
        case kInit:
            InitDisplay();
            break;
        
        case kRunning:
            RunningDisplay();
            break;
    }
}


void
GameContract::InitDisplay(void)
{
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::OrthoPrologue();
    GLUtils::RasterPos(100,100);
    GLUtils::SetColour(1,1,1);
    GLUtils::BitmapText("Loading...");
    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
}
    
void
GameContract::RunningDisplay(void)
{
    COREASSERT(m_gameMap != NULL);
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::OrthoPrologue();

    U32 xsize=m_gameMap->XSize();
    U32 ysize=m_gameMap->YSize();
    for (U32 x=0; x<xsize; x++)
    {
        for (U32 y=0; y<ysize; y++)
        {
            U32 mapVal=m_gameMap->At(x,y);
            GLUtils::SetColour(mapVal, 0, 1-mapVal);
            tVal basex=32*x;
            tVal basey=32*y;
            GLUtils::DrawRectangle(basex, basey, basex+31, basey+31);
        }
    }
    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
}

void
GameContract::Init(void)
{
    string filename;
    // Load and decompose the pixel maps
    filename=GameGlobalConfig::Instance().Get("IMAGEPATH").String() + "/gra1.tiff";
    CoreApp::Instance().Process("loadpixmap gra1 "+filename);
    CoreApp::Instance().Process("decompose gra1 gra1-@ 32 32");
    GLData::Instance().DumpTextures(cerr);
    
    // Load the game map
    m_gameMap=new GameMap;
    filename=GameGlobalConfig::Instance().Get("MAPPATH").String() + "/GameMap.xml";
    ifstream inStream(filename.c_str());
    if (!inStream) throw(LoaderFail(filename, "Could not open file"));
    CoreXML xml(inStream, filename);
    m_gameMap->Unpickle(xml);
    m_gameMap->Pickle(cout);
}

void
GameContract::Running(bool &outRedraw)
{
    // outRedraw=true;
}