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
 * $Id: GameContract.cpp,v 1.32 2002/07/19 15:52:34 southa Exp $
 * $Log: GameContract.cpp,v $
 * Revision 1.32  2002/07/19 15:52:34  southa
 * Fixed
 *
 * Revision 1.31  2002/07/19 15:44:40  southa
 * Graphic optimisations
 *
 * Revision 1.30  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 * Revision 1.29  2002/07/16 19:30:08  southa
 * Simplistic collision checking
 *
 * Revision 1.28  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 * Revision 1.27  2002/07/11 10:17:18  southa
 * Removed debug code
 *
 * Revision 1.26  2002/07/10 16:37:39  southa
 * Cursor removal
 *
 * Revision 1.25  2002/07/10 16:16:30  southa
 * Player graphic
 *
 * Revision 1.24  2002/07/07 11:16:07  southa
 * More designer work
 *
 * Revision 1.23  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.22  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 * Revision 1.21  2002/07/02 14:27:08  southa
 * First floor map designer build
 *
 * Revision 1.20  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.19  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
 * Revision 1.18  2002/06/13 15:15:55  southa
 * New directory structure, FPS printing, load command
 *
 * Revision 1.17  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 * Revision 1.16  2002/06/05 15:53:25  southa
 * Player and keyboard control
 *
 * Revision 1.15  2002/06/05 12:28:05  southa
 * Map rendered using traits
 *
 * Revision 1.14  2002/06/04 20:27:35  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.13  2002/06/04 17:02:11  southa
 * More work
 *
 * Revision 1.12  2002/06/04 14:12:25  southa
 * Traits loader first stage
 *
 * Revision 1.11  2002/06/02 16:41:18  southa
 * Rotated sprite plotting
 *
 * Revision 1.10  2002/05/31 17:46:46  southa
 * FPS tweaks
 *
 * Revision 1.9  2002/05/31 16:05:55  southa
 * FPS printout
 *
 * Revision 1.8  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.7  2002/05/30 16:21:53  southa
 * Pickleable GameContract
 *
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

#include "GameFloorMap.h"
#include "GameData.h"
#include "GameTileMap.h"
#include "GameGlobalConfig.h"
#include "GameAppHandler.h"
#include "GameTileTraits.h"
#include "GamePiecePlayer.h"
#include "GameFloorDesigner.h"
#include "GameMapArea.h"
#include "GameMotionSpec.h"
#include "GameView.h"

CoreInstaller GameContractInstaller(GameContract::Install);

GameContract::GameContract() :
    m_gameState(kInit),
    m_fps(0),
    m_frames(0),
    m_currentView(NULL)
{
}

GameContract::~GameContract()
{
    CoreEnv::Instance().PopConfig(GameGlobalConfig::Instance());
}

void
GameContract::Process(void)
{
    switch (m_gameState)
    {
        case kInit:
            Init();
            m_gameState=kRunning;
            GLUtils::PostRedisplay();
            break;

        case kRunning:
            Running();
            break;

        case kDesigning:
            Designing();
            break;
    }
}

void
GameContract::Display(void)
{
    switch (m_gameState)
    {
        case kInit:
            InitDisplay();
            break;
        
        case kRunning:
            RunningDisplay();
            break;

        case kDesigning:
            DesigningDisplay();
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
    COREASSERT(m_floorMap != NULL);

    GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());

    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::IdentityPrologue();
    GLPoint aimingPoint=GLPoint(m_player->XGet() / m_floorMap->XStep(),
                                m_player->YGet() / m_floorMap->YStep());
    {
        GameMotionSpec motion;
        // GLPoint scale(m_floorMap->XStep(), m_floorMap->YStep());
        m_player->MoveGet(motion);
        // m_floorMap->SolidMapGet().TrimMotion(motion);
        m_player->MoveConfirm(motion);
    }
    GLUtils::OrthoLookAt(m_player->XGet(), m_player->YGet(), m_player->AngleGet());
    GameMapArea visibleArea;
    tVal xRadius=(gameHandler.WidthGet() / 2) / m_floorMap->XStep();
    tVal yRadius=(gameHandler.HeightGet() / 2) / m_floorMap->YStep();
    tVal circleRadius=1+sqrt(xRadius*xRadius + yRadius*yRadius);
    visibleArea.CircleAdd(aimingPoint, circleRadius);

    GameMapArea highlightArea; // Empty area
    
    m_floorMap->Render(visibleArea, highlightArea);

    if (gameHandler.KeyStateGet('m'))
    {
        m_floorMap->RenderSolidMap(visibleArea);
    }
    
    GLUtils::IdentityEpilogue();
    
    GLUtils::IdentityPrologue();
    GLUtils::OrthoLookAt(m_player->XGet(), m_player->YGet(), m_player->AngleGet());
    GLUtils gl;
    glMatrixMode(GL_MODELVIEW);
    gl.SetPosition(0,0);
    GLUtils::ModulateSet(false);
    gl.MoveTo(m_player->XGet(), m_player->YGet());
    GLUtils::RotateAboutZ(-90-m_player->AngleGet()*180/3.14);
    GLUtils::Scale(64,64,1);
    m_player->Render();
    GLUtils::IdentityEpilogue();

    GLUtils::IdentityPrologue();
    GLUtils::OrthoLookAt(m_player->XGet(), m_player->YGet(), m_player->AngleGet());
    glMatrixMode(GL_MODELVIEW);
    COREASSERT(m_currentView != NULL);
    GLUtils::BlendSet(GLUtils::kBlendNone);
    m_currentView->OverPlotGet().Render();
    m_currentView->OverPlotGet().Clear();
    GLUtils::IdentityEpilogue();
    
    ostringstream message;
    message << "FPS " << m_fps;
    GLUtils::OrthoPrologue();
    GLUtils::SetColour(0.5,0.5,0.5);
    GLUtils::RasterPos(8,8);
    GLUtils::BitmapText(message.str());
    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
    ++m_frames;
}

void
GameContract::DesigningDisplay(void)
{
    COREASSERT(m_floorDesigner != NULL);
    m_floorDesigner->Display();
}

void
GameContract::Init(void)
{
    GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());

    m_tileMap=GameData::Instance().TileMapGet("tiles");
    m_floorMap=GameData::Instance().FloorMapGet("floor");
    COREASSERT(m_tileMap != NULL);
    COREASSERT(m_floorMap != NULL);
    m_floorMap->AttachTileMap(m_tileMap);
    m_tileMap->Load();
    GameData::Instance().ControllerGetOrCreate("controller1");
    m_player=dynamic_cast<GamePiecePlayer *>(GameData::Instance().PieceGet("player1"));
    COREASSERT(m_player != NULL);
    m_floorDesigner=new GameFloorDesigner; // This is leaked
    m_floorDesigner->Init();
    GameData::Instance().ViewGetOrCreate("view1");
    m_currentView=GameData::Instance().CurrentViewGet();
    COREASSERT(m_currentView != NULL);
    m_currentView->RectangleSet(GLRectangle(0,0,gameHandler.WidthGet(),gameHandler.HeightGet()));
    // GameData::Instance().DumpAll(cout);
}

void
GameContract::Running(void)
{
    GLUtils::PostRedisplay();
    {
        static U32 lastPrint=0;
        GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());

        U32 timeNow=glAppHandler.GetMilliseconds();
        //srand(timeNow);
        if (timeNow > lastPrint && timeNow - lastPrint > 5000)
        {
            // Print FPS every 5 seconds
            m_fps=(((double) m_frames * 1000) / (timeNow - lastPrint));
            cout << "FPS " << m_fps << endl;
            lastPrint=timeNow;
            m_frames=0;
        }
    }
    GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
    if (gameHandler.KeyStateGet('d'))
    {
        gameHandler.SetCursorState(true);
        m_gameState=kDesigning;
    }
}

void
GameContract::Designing(void)
{
    m_floorDesigner->Move();
    GLUtils::PostRedisplay();
    GameAppHandler& gameHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
    if (gameHandler.KeyStateGet('p'))
    {
        gameHandler.SetCursorState(false);
        m_gameState=kRunning;
    }
}

void
GameContract::ScriptFunction(const string& inName) const
{
    m_script.Execute();
}

void
GameContract::NullHandler(CoreXML& inXML)
{
}

void
GameContract::HandleContractStart(CoreXML& inXML)
{
    m_pickleState=kPickleData;
}

void
GameContract::HandleContractEnd(CoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameContract::HandleScriptStart(CoreXML& inXML)
{
}

void
GameContract::HandleScriptEnd(CoreXML& inXML)
{
    m_script=CoreScript(inXML.TopData());
}

void
GameContract::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<script type=\"text/core\">" << endl;
    inOut << m_script;
    inOut << inPrefix << "</script>" << endl;
}

void
GameContract::Unpickle(CoreXML& inXML)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleInit]["contract"] = &GameContract::HandleContractStart;
    m_startTable[kPickleData]["script"] = &GameContract::HandleScriptStart;
    m_endTable[kPickleData]["contract"] = &GameContract::HandleContractEnd;
    m_endTable[kPickleData]["script"] = &GameContract::HandleScriptEnd;

    m_pickleState=kPickleInit;
    inXML.ParseStream(*this);
}

void
GameContract::XMLStartHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << ">.  Potential matches are";
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
GameContract::XMLEndHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << ">.  Potential matches are";
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
GameContract::XMLDataHandler(CoreXML& inXML)
{
}

CoreScalar
GameContract::LoadContract(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: loadcontract <name> <filename>"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(LoaderFail(filename, "Could not open file"));
    CoreXML xml(inStream, filename);
    GameData::Instance().ContractGetOrCreate(name)->Unpickle(xml);
    return CoreScalar(0);
}

void
GameContract::Install(void)
{
    CoreApp::Instance().AddHandler("loadcontract", LoadContract);
}
