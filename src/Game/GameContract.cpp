/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameContract.cpp,v 1.105 2002/12/05 23:52:50 southa Exp $
 * $Log: GameContract.cpp,v $
 * Revision 1.105  2002/12/05 23:52:50  southa
 * Network management and status
 *
 * Revision 1.104  2002/12/05 13:20:11  southa
 * Client link handling
 *
 * Revision 1.103  2002/12/04 15:39:57  southa
 * Multiplayer work
 *
 * Revision 1.102  2002/12/04 12:54:40  southa
 * Network control work
 *
 * Revision 1.101  2002/12/04 00:37:10  southa
 * ControlFrameDef work
 *
 * Revision 1.100  2002/12/03 20:28:15  southa
 * Network, player and control work
 *
 * Revision 1.99  2002/11/25 12:06:17  southa
 * Received net message routing
 *
 * Revision 1.98  2002/11/24 23:18:07  southa
 * Added type name accessor to CorePickle
 *
 * Revision 1.97  2002/11/20 22:35:25  southa
 * Multiplayer setup
 *
 * Revision 1.96  2002/11/19 18:43:26  southa
 * Fixed macosx dynamic libraries
 *
 * Revision 1.95  2002/11/18 18:55:57  southa
 * Game resume and quit
 *
 * Revision 1.94  2002/11/18 11:31:13  southa
 * Return to game mode
 *
 * Revision 1.93  2002/11/16 12:43:21  southa
 * GameApp mode switching
 *
 * Revision 1.92  2002/11/15 18:58:33  southa
 * Configuration mode
 *
 * Revision 1.91  2002/11/15 12:59:25  southa
 * Auto-open configuration on startup
 *
 * Revision 1.90  2002/11/05 18:15:00  southa
 * Web server
 *
 * Revision 1.89  2002/11/04 13:11:57  southa
 * Link setup work
 *
 * Revision 1.88  2002/11/04 01:02:37  southa
 * Link checks
 *
 * Revision 1.87  2002/11/03 20:09:59  southa
 * Initial message unpacking
 *
 * Revision 1.86  2002/11/03 18:43:08  southa
 * Network fixes
 *
 * Revision 1.85  2002/11/01 18:46:24  southa
 * UDP Links
 *
 * Revision 1.84  2002/11/01 17:24:49  southa
 * Network links on win32
 *
 * Revision 1.83  2002/11/01 16:15:26  southa
 * Network send and receive
 *
 * Revision 1.82  2002/10/31 19:55:53  southa
 * Network links
 *
 * Revision 1.81  2002/10/31 16:41:32  southa
 * Network client
 *
 * Revision 1.80  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.79  2002/10/17 16:41:20  southa
 * Initialisation fix and player facet
 *
 * Revision 1.78  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
 *
 * Revision 1.77  2002/10/15 14:02:31  southa
 * Mode changes
 *
 * Revision 1.76  2002/10/14 15:13:39  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.75  2002/10/13 12:26:46  southa
 * Facetised map rendering
 *
 * Revision 1.74  2002/10/12 15:25:11  southa
 * Facet renderer
 *
 * Revision 1.73  2002/10/11 20:10:14  southa
 * Various fixes and new files
 *
 * Revision 1.72  2002/10/11 14:01:11  southa
 * Lighting work
 *
 * Revision 1.71  2002/10/10 22:47:57  southa
 * Full light definitions
 *
 * Revision 1.70  2002/10/10 18:25:14  southa
 * Light links and test lights
 *
 * Revision 1.69  2002/10/08 21:44:09  southa
 * 3D maps
 *
 * Revision 1.68  2002/10/08 17:13:17  southa
 * Tiered maps
 *
 * Revision 1.67  2002/10/08 11:58:52  southa
 * Light cache
 *
 * Revision 1.66  2002/10/07 17:49:45  southa
 * Multiple values per map element
 *
 * Revision 1.65  2002/10/07 12:15:37  southa
 * First specular lighting
 *
 * Revision 1.64  2002/10/06 22:09:59  southa
 * Initial lighting test
 *
 * Revision 1.63  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.62  2002/08/24 19:23:32  southa
 * Don't reload the tile map
 *
 * Revision 1.61  2002/08/24 15:57:35  southa
 * Reset player position
 *
 * Revision 1.60  2002/08/24 15:42:24  southa
 * Race state change
 *
 * Revision 1.59  2002/08/24 15:27:07  southa
 * Race restart
 *
 * Revision 1.58  2002/08/22 10:11:11  southa
 * Save records, spacebar dialogues
 *
 * Revision 1.57  2002/08/21 16:09:04  southa
 * GameTypeRace state tweaks
 *
 * Revision 1.56  2002/08/20 11:43:25  southa
 * GameRewards added
 *
 * Revision 1.55  2002/08/19 11:09:55  southa
 * GameTypeRace rendering
 *
 * Revision 1.54  2002/08/18 21:47:53  southa
 * Added temporary sound test
 *
 * Revision 1.53  2002/08/18 20:44:33  southa
 * Initial chequepoint work
 *
 * Revision 1.52  2002/08/18 15:13:15  southa
 * Adhesion handling
 *
 * Revision 1.51  2002/08/17 10:41:50  southa
 * Designer fixes
 *
 * Revision 1.50  2002/08/16 19:46:06  southa
 * MediaSound work
 *
 * Revision 1.49  2002/08/15 13:39:30  southa
 * CoreData and CoreDatRef
 *
 * Revision 1.48  2002/08/13 17:50:20  southa
 * Added playsound command
 *
 * Revision 1.47  2002/08/10 12:34:47  southa
 * Added current dialogues
 *
 * Revision 1.46  2002/08/09 17:09:03  southa
 * GameDialogue added
 *
 * Revision 1.45  2002/08/08 18:20:29  southa
 * Plot on screen of dimension 1.0
 *
 * Revision 1.44  2002/08/08 13:39:09  southa
 * Text rendering
 *
 * Revision 1.43  2002/08/07 13:36:49  southa
 * Conditioned source
 *
 * Revision 1.42  2002/08/05 16:14:18  southa
 * Windback at low frame rates
 *
 * Revision 1.41  2002/08/05 15:15:21  southa
 * Improved windback and released FPS limit
 *
 * Revision 1.40  2002/08/05 13:37:28  southa
 * Windback work
 *
 * Revision 1.39  2002/08/02 15:20:54  southa
 * Frame rate timing
 *
 * Revision 1.38  2002/08/02 12:56:39  southa
 * Working collision checking
 *
 * Revision 1.37  2002/08/02 09:05:10  southa
 * Movement modification in collison checking
 *
 * Revision 1.36  2002/08/01 16:47:10  southa
 * First multi-box collsion checking
 *
 * Revision 1.35  2002/07/31 16:27:16  southa
 * Collision checking work
 *
 * Revision 1.34  2002/07/23 14:10:46  southa
 * Added GameMotion
 *
 * Revision 1.33  2002/07/19 17:51:10  southa
 * Texture tweaks
 *
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
#include "mushMedia.h"
#include "mushPlatform.h"

#include "GameController.h"
#include "GameControlFrameDef.h"
#include "GameFloorMap.h"
#include "GameData.h"
#include "GameTileMap.h"
#include "GameGlobalConfig.h"
#include "GameAppHandler.h"
#include "GameTileTraits.h"
#include "GamePiecePlayer.h"
#include "GamePlayerUtils.h"
#include "GameFloorDesigner.h"
#include "GameMapArea.h"
#include "GameMotionSpec.h"
#include "GameView.h"
#include "GameTimer.h"
#include "GameMapPoint.h"
#include "GameDefClient.h"
#include "GameDialogue.h"
#include "GameDataUtils.h"
#include "GameTypeRace.h"
#include "GameEvent.h"
#include "GameNetUtils.h"
#include "GameRewards.h"
#include "GameRouter.h"
#include "GameSpacePoint.h"
#include "GameConfig.h"
#include "GameConfigDef.h"

CoreInstaller GameContractInstaller(GameContract::Install);

GameContract::GameContract() :
    m_gameState(kGameStateInit),
    m_tileMap(NULL),    m_fps(0),
    m_frames(0),
    m_floorDesigner(),
    m_currentView(NULL),
    m_modeKeypressTime(0),
    m_newMode(0),
    m_renderDiagnostics(kDiagnosticNone),
    m_fastDiagnostics(false)
{
}

GameContract::~GameContract()
{
    // GameData::Instance().Clear();
}

void
GameContract::Process(GameAppHandler& inAppHandler)
{
    switch (m_gameState)
    {
        case kGameStateInit:
            Init(inAppHandler);
            m_gameState=kGameStateRunning;
            GLUtils::PostRedisplay();
            break;

        case kGameStateRunning:
            Running(inAppHandler);
            break;

        case kGameStateDesigning:
            Designing();
            break;

        case kGameStateOver:
            Running(inAppHandler);
            Over();
            break;

        case kGameStatePaused:
            Paused();
            break;

        default:
            throw(LogicFail("Bad value for m_gameState"));
    }
}

void
GameContract::Display(GameAppHandler& inAppHandler)
{
    switch (m_gameState)
    {            
        case kGameStateInit:
            InitDisplay();
            break;
        
        case kGameStateRunning:
        case kGameStateOver:
        case kGameStatePaused:
            RunningDisplay();
            break;

        case kGameStateDesigning:
            DesigningDisplay();
            break;

        default:
            throw(LogicFail("Bad value for m_gameState"));
    }
}

void
GameContract::SwapIn(GameAppHandler& inAppHandler)
{
    try
    {
        GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(CoreAppHandler::Instance());
        glAppHandler.EnterScreen(PlatformVideoUtils::Instance().ModeDefGet(GameConfig::Instance().DisplayModeGet()));
    }
    catch (...)
    {
        GameConfig::Instance().DisplayModeSetDefault();
        throw;
    }
    GLUtils::CheckGLError();
}

void
GameContract::SwapOut(GameAppHandler& inAppHandler)
{
}

void
GameContract::Init(GameAppHandler& inAppHandler)
{
    // Run the load script in the contract definition
    m_script.Execute();
    
    GameData::Instance().TimerGet().Reset();
    if (m_tileMap == NULL)
    {
        m_tileMap=GameData::Instance().TileMapGet("tiles");
        m_floorMap=GameData::Instance().FloorMapGet("floor");
        COREASSERT(m_tileMap != NULL);
        COREASSERT(m_floorMap != NULL);
        m_floorMap->AttachTileMap(m_tileMap);
        m_tileMap->Load();
    }
    GameData::Instance().ControllerGetOrCreate("controller1");

    if (!inAppHandler.MultiplayerIs())
    {
        // Create the player for a single player game
        const GamePiecePlayer *templatePlayer=dynamic_cast<const GamePiecePlayer *>(GameData::Instance().TemplateGet("player1"));
        COREASSERT(templatePlayer != NULL);

        GameData::Instance().PlayerGet().Give("singleplayer", new GamePiecePlayer(*templatePlayer));
    }
    
    if (m_floorDesigner == NULL) m_floorDesigner=new GameFloorDesigner; // This is leaked
    m_floorDesigner->Init();
    GameData::Instance().ViewGetOrCreate("view1");
    m_currentView=GameData::Instance().CurrentViewGet();
    COREASSERT(m_currentView != NULL);
    m_currentView->RectangleSet(GLRectangle(0,0,inAppHandler.WidthGet(),inAppHandler.HeightGet()));  // Might be wrong
    // GameData::Instance().DumpAll(cout);

    GameData::Instance().TypeGet().Initialise();

    GameData::Instance().CurrentDialoguesClear();
    GameDataUtils::NamedDialoguesAdd("^start");
    m_newMode=GameConfig::Instance().DisplayModeGet();
    GameData::Instance().CurrentViewGet()->AmbientLightingSet(0.01);
}

void
GameContract::InitDisplay(void)
{
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::OrthoPrologue();
    GLUtils::RasterPos(100,100);
    GLState::ColourSet(1,1,1);
    GLUtils::BitmapText("Loading...");
    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
}

void
GameContract::RunningMove(GameTimer& inTimer, U32 inNumFrames)
{
    COREASSERT(m_floorMap != NULL);
    U32 startFrameNum = inTimer.ClientGet().FrameNumGet();
    
    CoreData<GamePiecePlayer>::tMapIterator endValue=GameData::Instance().PlayerGet().End();

    for (U32 i=0; i<inNumFrames; ++i)
    {
        U32 frameNum = startFrameNum + i; // Add control delay here
        
        for (CoreData<GamePiecePlayer>::tMapIterator p=GameData::Instance().PlayerGet().Begin();
                p != endValue; ++p)
        {
            GamePiecePlayer& playerRef=*p->second;
            
            playerRef.EnvironmentRead(*m_floorMap);
            GameEventStandingOn standingOn(playerRef.StandingOnGet());
    
            GameData::Instance().TypeGet().EventHandler(standingOn);

            const GameControlFrameDef *frameDef = NULL;
            if (playerRef.ControlFrameDefGet(frameDef, frameNum))
            {
                COREASSERT(frameDef != NULL);
    
                GameMotionSpec motion;
                playerRef.MoveGet(motion, *frameDef);
                
                if (m_renderDiagnostics == kDiagnosticCollision)
                {
                    GLState::DepthSet(GLState::kDepthNone);
                    GLState::ModulationSet(GLState::kModulationColour);
                    GLState::BlendSet(GLState::kBlendLine);
                    m_floorMap->SolidMapGet().OverPlotCollisionSet(motion);
                }
                m_floorMap->SolidMapGet().TrimMotion(motion);
                playerRef.MoveConfirm(motion);
                if (m_renderDiagnostics == kDiagnosticCollision)
                {
                    motion.Render();
                }
            }
        }
    }
    
    const GameData::DialogueMap& currentDialogues(GameData::Instance().CurrentDialogueMapGet());
    string killName;
    
    for (map<string, GameDialogue *>::const_iterator p = currentDialogues.begin();
         p != currentDialogues.end(); ++p)
    {
        for (U32 i=0; i<inNumFrames; ++i)
        {
            p->second->Move();
        }
        if (p->second->ExpiredGet())
        {
            killName=p->first;
        }
    }
    
    if (killName != "")
    {
        GameData::Instance().CurrentDialogueDelete(killName);
    }

    for (U32 i=0; i<inNumFrames; ++i)
    {
        GameData::Instance().TypeGet().Move();
    }
    
    if (GameData::Instance().TypeGet().IsGameOver())
    {
        if (m_gameState == kGameStateRunning) m_gameState = kGameStateOver;
    }
}

void
GameContract::RunningDisplay(void)
{
    COREASSERT(m_tileMap != NULL);
    COREASSERT(m_floorMap != NULL);
    m_floorMap->AttachTileMap(m_tileMap);

    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
    GameTimer& timer(GameData::Instance().TimerGet());

    timer.CurrentMsecSet(gameAppHandler.MillisecondsGet());
    tVal windbackValue = timer.ClientGet().WindbackValueGet();
    
    GameView& currentView = *GameData::Instance().CurrentViewGet();

    GLState::AmbientLightSet(currentView.AmbientLightingGet());
    GLState::LightingAlphaSet(1.0);
    GLData::Instance().LightsGet()->AmbientLightingSet(currentView.AmbientLightingGet());
    GLData::Instance().LightsGet()->LightingFactorSet(currentView.LightingFactorGet());
    
    GLUtils::DisplayPrologue();

    // DisplayPrologue swaps in the previously rendered screen, so note the time here
    timer.CurrentMsecSet(gameAppHandler.MillisecondsGet());
    timer.ClientGet().DisplayedFrameAt();
    ++m_frames;
    
    GLUtils::ClearScreen();
    GLUtils::IdentityPrologue();

    // Just pick the first player for now
    CoreData<GamePiecePlayer>::tMapIterator playerIter = GameData::Instance().PlayerGet().Begin();
    if (playerIter != GameData::Instance().PlayerGet().End())
    {
        GameMotionSpec playerSpec(playerIter->second->MotionSpecGet());
        playerSpec.Windback(windbackValue);
        currentView.MoveCameraToPlayer(GLVector(playerSpec.pos.x, playerSpec.pos.y, 0), playerSpec.angle);
    }

    GLPoint lookAtPoint(currentView.LookAtPosGet().x, currentView.LookAtPosGet().y);
    GameMapPoint aimingPoint(lookAtPoint / m_floorMap->StepGet());
    
    GLUtils::PerspectiveLookAt(currentView.CameraPosGet(), currentView.LookAtPosGet(), currentView.CameraAngleGet());

    GLUtils::PushMatrix();
    
    GLState::DepthSet(GLState::kDepthTest);
    
    // Work out how many map pieces we can see in our view
    GameMapArea visibleArea;
    GLPoint screenRatios(GLUtils::ScreenRatiosGet());
    GLPoint screenRadius((screenRatios / 2) / m_floorMap->StepGet());
    tVal circleRadius=1+screenRadius.Magnitude()*GLUtils::ScreenScaleGet();
    visibleArea.CircleAdd(aimingPoint, circleRadius);

    GameMapArea highlightArea; // Empty area
    
    m_floorMap->Render(visibleArea, highlightArea, vector<bool>());
    GLUtils::Flush();
    switch(m_renderDiagnostics)
    {
        case kDiagnosticLights:
            m_floorMap->RenderLightMap(visibleArea);
            break;

        case kDiagnosticSolidMap:
            m_floorMap->RenderSolidMap(visibleArea);
            break;

        case kDiagnosticAdhesionMap:
            m_floorMap->RenderAdhesionMap(visibleArea);
            break;

        default:
            break;
    }
            
    GLUtils::PopMatrix();

    // Set states for player rendering
    GLState::DepthSet(GLState::kDepthTest);

    {
        CoreData<GamePiecePlayer>::tMapIterator endValue = GameData::Instance().PlayerGet().End();
    
        for (CoreData<GamePiecePlayer>::tMapIterator p=GameData::Instance().PlayerGet().Begin(); p != endValue; ++p)
        {
            GLUtils::PushMatrix();
            GameMotionSpec playerSpec(p->second->MotionSpecGet());
            playerSpec.Windback(windbackValue);
            m_floorMap->SetLightingFor(GameSpacePoint(playerSpec.pos));
    
            GLUtils gl;
            gl.SetPosition(0,0);
            gl.MoveTo(playerSpec.pos.x, playerSpec.pos.y);
            GLUtils::RotateAboutZ(-90-playerSpec.angle*(180/M_PI));

            if (p->second->ImageIs())
            {
                GLState::LightingAlphaSet(0.8);
            }
            else
            {
                GLState::LightingAlphaSet(1.0);
            }
            // Reset the lighting with the new alpha
            GLState::ModulationSet(GLState::kModulationLighting);

            p->second->Render();
        
            GLUtils::PopMatrix();
        }
    }
    COREASSERT(m_currentView != NULL);
    GLState::DepthSet(GLState::kDepthNone);
    GLState::ModulationSet(GLState::kModulationColour);
    GLState::BlendSet(GLState::kBlendLine);
    m_currentView->OverPlotGet().Render();
    m_currentView->OverPlotGet().Clear();
    GLUtils::IdentityEpilogue();

    RenderText();
    
    if (m_fastDiagnostics)
    {
        RenderFastDiagnostics();
    }
    GLUtils::Flush();

    GameData::Instance().TypeGet().Render();

    if (m_gameState == kGameStatePaused)
    {
        static tVal rotateAdd=0;
        static tVal rotateTime=0;
        static tVal rotateCtr=0;
        rotateCtr+=0.1*cos(rotateAdd-rotateTime*1.5);
        rotateAdd+=0.01*cos(sin(rotateAdd*1.3)-cos(rotateCtr*1.7)+sin(rotateTime*1.8));
        rotateTime+= 0.01;
        GLUtils::OrthoPrologue();
        GLState::ColourSet(1,0.5+0.5*sin(rotateCtr*0.85),0.5+0.5*cos(rotateCtr*1.23),0.8);
        GLString glStr("PAUSED", GLFontRef("font-mono1", 0.07+0.05*cos(rotateCtr*1.35)),0);
        GLUtils::RotateAboutZ(rotateCtr);
        glStr.Render();
        GLUtils::OrthoEpilogue();
    }
    GLUtils::DisplayEpilogue();
}

void
GameContract::RenderFastDiagnostics(void) const
{
    ostringstream message;

    message << "FPS " << m_fps;
    GLUtils::OrthoPrologue();
    GLState::ColourSet(0.0,0.0,1.0,0.5);
    GLUtils orthoGL;
    orthoGL.MoveToEdge(-1,-1);
    orthoGL.MoveRelative(0.02,0.02);
    GLString fpsStr(message.str(), GLFontRef("font-mono1", 0.02), -1.0);
    fpsStr.Render();
    GLUtils::OrthoEpilogue();
}

void
GameContract::RenderText(void) const
{
    const GameData::DialogueMap currentDialogues(GameData::Instance().CurrentDialogueMapGet());

    GLUtils::OrthoPrologue();
    for (map<string, GameDialogue *>::const_iterator p = currentDialogues.begin();
         p != currentDialogues.end(); ++p)
    {
        GLUtils::PushMatrix();
        p->second->Render();
        GLUtils::PopMatrix();
    }
    if (m_modeKeypressTime != 0)
    {
        PlatformVideoUtils::Instance().RenderModeInfo(m_newMode);
    }
    GLUtils::OrthoEpilogue();
}

void
GameContract::DesigningDisplay(void)
{
    COREASSERT(m_floorDesigner != NULL);
    m_floorDesigner->Display();
}


void
GameContract::Running(GameAppHandler& inAppHandler)
{
    GameTimer& timer(GameData::Instance().TimerGet());
        
    // Get the control events up to date
    inAppHandler.PollForControlEvents();

    timer.CurrentMsecSet(inAppHandler.MillisecondsGet());

    if (timer.JudgementValid())
    {
        U32 numMotionFrames=timer.ClientGet().IntegerElapsedFramesGet();
        if (inAppHandler.MultiplayerIs())
        {
            // Can't skip frames in a network game, but this avoids a total hang
            if (numMotionFrames > 100) numMotionFrames=100;
        }
        else
        {
            if (numMotionFrames > 6) numMotionFrames=6;
        }

        GamePlayerUtils::FillControlQueues(timer, numMotionFrames);

        if (inAppHandler.MultiplayerIs())
        {
            GamePlayerUtils::SendControlQueues(timer, numMotionFrames);
            GameNetUtils::NetReceive();
        }
        
        RunningMove(timer, numMotionFrames);

        timer.ClientGet().FramesDone(numMotionFrames);
        
        // Discard any motion frames we haven't caught up with
        if (!inAppHandler.MultiplayerIs())
        {
            timer.ClientGet().FramesDiscard();
        }
        
        if (timer.ClientGet().RedisplayGet())
        {
            GLUtils::PostRedisplay();
            timer.ClientGet().RedisplayDone();
        }

        tVal numPeriodic10ms=timer.Periodic10msGet();
        // cerr << "numPeriodic10ms=" << numPeriodic10ms << endl;
        for (tVal i=0; i<numPeriodic10ms && i<10; ++i)
        {
            if (i == 0)
            {
                GlobalKeyControl();
            }
        }
        timer.Periodic10msDone(numPeriodic10ms);

        tVal numPeriodic100ms=timer.Periodic100msGet();
        for (tVal i=0; i<numPeriodic100ms && i<10; ++i)
        {
            // Keep web links ticking over
            if (i == 0)
            {
                GameNetUtils::WebReceive();
            }
        }
        timer.Periodic100msDone(numPeriodic100ms);

        tVal numPeriodic1s=timer.Periodic1sGet();
        // cerr << "numPeriodic1s=" << numPeriodic1s << endl;
        for (tVal i=0; i<numPeriodic1s && i<10; ++i)
        {
            if (inAppHandler.MultiplayerIs())
            {
                GameNetUtils::NetTicker();
                GamePlayerUtils::ManagePlayers(inAppHandler);
            }

            static U32 lastPrint=0;
            m_fps=m_frames;
            m_frames=0;
            if (++lastPrint >= 5)
            {
                // Print FPS every 5 seconds

                cout << "FPS " << m_fps << endl;
                lastPrint=0;
            }
            timer.Periodic1sDone(1);
        }
        timer.CurrentMsecSet(inAppHandler.MillisecondsGet());
        // CoreUtils::Sleep(timer.SleepTimeGet());
    }
    MediaAudio::Instance().Ticker();
}

void
GameContract::Paused(void)
{
    GLUtils::PostRedisplay();
    GlobalKeyControl();
    MediaAudio::Instance().Ticker();
}


void
GameContract::Over(void)
{
    // Expects Running to have been called as well
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
    // Needs sorting out
    if (gameAppHandler.KeyStateGet(' '))
    {
        m_gameState=kGameStateInit;
    }
}

void
GameContract::GlobalKeyControl(void)
{
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
    GameTimer& timer(GameData::Instance().TimerGet());

    if (gameAppHandler.LatchedKeyStateTake('d'))
    {
        if (m_gameState == kGameStateRunning)
        {
            GameData::Instance().CurrentViewGet()->AmbientLightingSet(0.7);
            gameAppHandler.SetCursorState(true);
            m_gameState=kGameStateDesigning;
        }
        else
        {
            GameData::Instance().CurrentViewGet()->AmbientLightingSet(0.01);
            m_floorMap->SolidMapInvalidate();
            gameAppHandler.SetCursorState(false);
            m_gameState=kGameStateRunning;
        }
        GLState::AmbientLightSet(GameData::Instance().CurrentViewGet()->AmbientLightingGet());
        GLData::Instance().LightsGet()->AmbientLightingSet(GameData::Instance().CurrentViewGet()->AmbientLightingGet());
        GLData::Instance().LightsGet()->LightingFactorSet(GameData::Instance().CurrentViewGet()->LightingFactorGet());
        gameAppHandler.LatchedKeyStateTake('-');
        gameAppHandler.LatchedKeyStateTake('=');
    }
    if (gameAppHandler.LatchedKeyStateTake('p'))
    {
        if (m_gameState == kGameStateRunning)
        {
            m_gameState=kGameStatePaused;
        }
        else if (m_gameState == kGameStatePaused)
        {
            m_gameState=kGameStateRunning;
        }
    }
    
    if (gameAppHandler.LatchedKeyStateTake('q'))
    {
        m_gameState=kGameStateInit;
    }
    
    if (gameAppHandler.LatchedKeyStateTake('m'))
    {
        m_renderDiagnostics = static_cast<tDiagnostic>(m_renderDiagnostics+1);
        if (m_renderDiagnostics == kDiagnosticLast) m_renderDiagnostics=kDiagnosticNone;
    }
    if (gameAppHandler.LatchedKeyStateTake('n'))
    {
        m_fastDiagnostics=!m_fastDiagnostics;
    }
    if (gameAppHandler.LatchedKeyStateTake(' '))
    {
        GameData::Instance().CurrentDialoguesClear();
    }
    if (gameAppHandler.LatchedKeyStateTake('-'))
    {
        if (m_modeKeypressTime != 0)
        {
            m_newMode=PlatformVideoUtils::Instance().PreviousModeDef(m_newMode);
        }
        m_modeKeypressTime=timer.CurrentMsecGet();
    }
    if (gameAppHandler.LatchedKeyStateTake('='))
    {
        if (m_modeKeypressTime != 0)
        {
            m_newMode=PlatformVideoUtils::Instance().NextModeDef(m_newMode);
        }
        m_modeKeypressTime=timer.CurrentMsecGet();
    }
    if (m_modeKeypressTime != 0 && m_modeKeypressTime +3000 < timer.CurrentMsecGet())
    {
        if (m_newMode != GameConfig::Instance().DisplayModeGet())
        {
            gameAppHandler.EnterScreen(PlatformVideoUtils::Instance().ModeDefGet(m_newMode));
        }
        GameConfig::Instance().DisplayModeSet(m_newMode);
        m_modeKeypressTime=0;
    }
}

void
GameContract::Designing(void)
{
    m_floorDesigner->Move();
    GLUtils::PostRedisplay();
    GlobalKeyControl();
}

void
GameContract::ScriptFunction(const string& inName, GameAppHandler& inAppHandler) const
{
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
GameContract::HandleDialogueStart(CoreXML& inXML)
{
    string name(inXML.GetAttribOrThrow("name").StringGet());
    GameData::Instance().DialogueDeleteAndCreate(name, new GameDialogue)->Unpickle(inXML);
}

void
GameContract::HandleGameStart(CoreXML& inXML)
{
    string type(inXML.GetAttribOrThrow("type").StringGet());
    if (type == "race")
    {
    GameData::Instance().TypeSet(new GameTypeRace);
    }
    else
    {
        inXML.Throw("Game type must be 'race'");
    }
    GameData::Instance().TypeGet().Unpickle(inXML);
}

void
GameContract::HandleRewardsStart(CoreXML& inXML)
{
    GameData::Instance().RewardsSet(new GameRewards);
    GameData::Instance().RewardsGet().Unpickle(inXML);
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
    m_startTable[kPickleData]["dialogue"] = &GameContract::HandleDialogueStart;
    m_startTable[kPickleData]["game"] = &GameContract::HandleGameStart;
    m_startTable[kPickleData]["rewards"] = &GameContract::HandleRewardsStart;
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

char *
GameContract::TypeNameGet(void) const
{
    return "gamecontract";
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
