/*
 * $Id: GameContract.cpp,v 1.5 2002/05/29 08:56:16 southa Exp $
 * $Log: GameContract.cpp,v $
 * Revision 1.5  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.4  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.3  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
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
#include "GameData.h"
#include "GameTileMap.h"
#include "GameGlobalConfig.h"

GameContract::GameContract(): m_state(kInit)
{
    CoreEnv::Instance().PushConfig(GameGlobalConfig::Instance());
    string appPath(CoreGlobalConfig::Instance().Get("APPLPATH").String());
    GameGlobalConfig::Instance().Set("MAPPATH", appPath+"/../game");
    GameGlobalConfig::Instance().Set("IMAGEPATH", appPath+"/../game");
}

GameContract::~GameContract()
{
    CoreEnv::Instance().PopConfig(GameGlobalConfig::Instance());
}

void
GameContract::Process(bool &outDoQuit, bool &outRedraw)
{
    switch (m_state)
    {
        case kInit:
            Init();
            m_state=kRunning;
            outRedraw=true;
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
    COREASSERT(m_tileMap != NULL);
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
            S32 basex=32*x;
            S32 basey=32*y;
            GLTextureRef texRef(m_tileMap->NameGet(mapVal));
            if (texRef.Exists())
            {
                GLUtils::DrawBitmap(*texRef.TextureGet(), basex, basey);
            }
        }
    }
    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
}

void
GameContract::Init(void)
{
    CoreApp::Instance().Process("loadtilemap('map1',$MAPPATH+'/TileMap.xml')");
    m_tileMap=GameData::Instance().TileMapGet("map1");
    
    // Load the game map
    {
        m_gameMap.reset(new GameMap);
        string filename=GameGlobalConfig::Instance().Get("MAPPATH").String() + "/GameMap.xml";
        ifstream inStream(filename.c_str());
        if (!inStream) throw(LoaderFail(filename, "Could not open file"));
        CoreXML xml(inStream, filename);
        m_gameMap->Unpickle(xml);
    }

    COREASSERT(m_tileMap != NULL);
    m_tileMap->Load();
    cerr << *m_tileMap;
}

void
GameContract::Running(bool &outRedraw)
{
    // outRedraw=true;
}
