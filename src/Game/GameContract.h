#ifndef GAMECONTRACT_H
#define GAMECONTRACT_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameContract.h,v 1.39 2002/12/29 20:30:53 southa Exp $
 * $Log: GameContract.h,v $
 * Revision 1.39  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.38  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.37  2002/12/10 19:00:16  southa
 * Split timer into client and server
 *
 * Revision 1.36  2002/12/04 15:39:58  southa
 * Multiplayer work
 *
 * Revision 1.35  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.34  2002/12/03 20:28:16  southa
 * Network, player and control work
 *
 * Revision 1.33  2002/11/24 23:18:07  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.32  2002/11/16 12:43:22  southa
 * GameApp mode switching
 *
 * Revision 1.31  2002/11/15 18:58:34  southa
 * Configuration mode
 *
 * Revision 1.30  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.29  2002/10/17 15:50:59  southa
 * Config saving, pause and quit
 *
 * Revision 1.28  2002/10/15 14:02:31  southa
 * Mode changes
 *
 * Revision 1.27  2002/10/08 17:13:17  southa
 * Tiered maps
 *
 * Revision 1.26  2002/10/07 17:49:45  southa
 * Multiple values per std::map element
 *
 * Revision 1.25  2002/10/06 22:09:59  southa
 * Initial lighting test
 *
 * Revision 1.24  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.23  2002/08/24 15:27:07  southa
 * Race restart
 *
 * Revision 1.22  2002/08/20 11:43:25  southa
 * GameRewards added
 *
 * Revision 1.21  2002/08/18 20:44:34  southa
 * Initial chequepoint work
 *
 * Revision 1.20  2002/08/10 12:34:48  southa
 * Added current dialogues
 *
 * Revision 1.19  2002/08/09 17:09:04  southa
 * GameDialogue added
 *
 * Revision 1.18  2002/08/08 18:20:30  southa
 * Plot on screen of dimension 1.0
 *
 * Revision 1.17  2002/08/07 13:36:49  southa
 * Conditioned source
 *
 * Revision 1.16  2002/08/02 15:20:55  southa
 * Frame rate timing
 *
 * Revision 1.15  2002/08/02 12:56:40  southa
 * Working collision checking
 *
 * Revision 1.14  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 * Revision 1.13  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.12  2002/07/02 14:27:08  southa
 * First floor std::map designer build
 *
 * Revision 1.11  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.10  2002/06/13 15:15:55  southa
 * New directory structure, FPS printing, load command
 *
 * Revision 1.9  2002/06/05 15:53:25  southa
 * Player and keyboard control
 *
 * Revision 1.8  2002/06/04 20:27:36  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.7  2002/06/04 14:12:25  southa
 * Traits loader first stage
 *
 * Revision 1.6  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.5  2002/05/30 16:21:53  southa
 * Pickleable GameContract
 *
 * Revision 1.3  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.2  2002/05/28 13:05:55  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.1  2002/05/27 12:58:43  southa
 * GameContract and global configs added
 *
 */

#include "mushCore.h"
#include "mushGL.h"

#include "GameBase.h"
#include "GameTimer.h"

class GameDefClient;
class GameFloorMap;
class GameTileMap;
class GamePiecePlayer;
class GameFloorDesigner;
class GameView;

class GameContract: public GameBase, public MushcorePickle, private MushcoreXMLHandler
{
public:
    GameContract();
    virtual ~GameContract();
    virtual void Process(GameAppHandler& inAppHandler);
    virtual void Display(GameAppHandler& inAppHandler);
    virtual void ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const;
    virtual void SwapIn(GameAppHandler& inAppHandler);
    virtual void SwapOut(GameAppHandler& inAppHandler);
    
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;

    static MushcoreScalar LoadContract(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

protected:
    enum tGameState
    {
        kGameStateInvalid,
        kGameStateInit,
        kGameStateRunning,
        kGameStatePaused,
        kGameStateDesigning,
        kGameStateOver
    };

    void Init(GameAppHandler& inAppHandler);
    void Running(GameAppHandler& inAppHandler);
    void Paused(void);
    void Designing(void);
    void Over(void);
    void InitDisplay(void);
    void RunningDisplay(void);
    void RenderText(void) const;
    void RenderFastDiagnostics(void) const;
    void DesigningDisplay(void);
    void GlobalKeyControl(void);
    void RunningMove(GameTimer& inTimer, Mushware::U32 inNumFrames);
    void FillControlQueues(const GameTimer& inTimer, Mushware::U32 inNumFrames);
    void SendControl(const GameDefClient& inClient, const GamePiecePlayer& inPlayer, const GameTimer& inTimer, Mushware::U32 inNumFrames);
    void SendControlQueues(const GameTimer& inTimer, Mushware::U32 inNumFrames);
    bool VerifyOrCreateImagePlayer(const std::string& inName, GameDefClient& inClientDef);
    bool VerifyPlayer(const std::string& inName, GamePiecePlayer& inPlayer);
    bool VerifyOrCreateLocalPlayer(const std::string& inName, GameDefClient& inClientDef);
    void ManagePlayers(GameAppHandler& inAppHandler);
    
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

    void HandleContractStart(MushcoreXML& inXML);
    void HandleContractEnd(MushcoreXML& inXML);
    void HandleScriptStart(MushcoreXML& inXML);
    void HandleScriptEnd(MushcoreXML& inXML);
    void HandleDialogueStart(MushcoreXML& inXML);
    void HandleGameStart(MushcoreXML& inXML);
    void HandleRewardsStart(MushcoreXML& inXML);
    void NullHandler(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };
    
private:
    typedef std::map<string, void (GameContract::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    Mushware::U32 m_pickleState;
    MushcoreScript m_script;

    enum tDiagnostic
    {
        kDiagnosticInvalid,
        kDiagnosticNone,
        kDiagnosticCollision,
        kDiagnosticSolidMap,
        kDiagnosticAdhesionMap,
        kDiagnosticLights,
        kDiagnosticLast
    };
    
    tGameState m_gameState;
    GameFloorMap *m_floorMap;
    GameTileMap *m_tileMap;
    Mushware::tVal m_fps;
    Mushware::U32 m_frames;
    GameFloorDesigner *m_floorDesigner;
    GameView *m_currentView;
    GameTimer::tMsec m_modeKeypressTime;
    Mushware::U32 m_newMode;
    tDiagnostic m_renderDiagnostics;
    bool m_fastDiagnostics;
};

inline std::ostream& operator<<(std::ostream &inOut, const GameContract& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}

#endif
