#ifndef GAMECONTRACT_H
#define GAMECONTRACT_H
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
 * $Id: GameContract.h,v 1.13 2002/07/06 18:04:18 southa Exp $
 * $Log: GameContract.h,v $
 * Revision 1.13  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.12  2002/07/02 14:27:08  southa
 * First floor map designer build
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

#include "GameBase.h"

class GameFloorMap;
class GameTileMap;
class GamePiecePlayer;
class GameFloorDesigner;
class GameView;

class GameContract: public GameBase, public CorePickle, private CoreXMLHandler
{
public:
    GameContract();
    virtual ~GameContract();
    virtual void Process(void);
    virtual void Display(void);
    virtual void ScriptFunction(const string& inName) const;

    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    static CoreScalar LoadContract(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static void Install(void);

protected:
    enum GameState
    {
        kInit,
        kRunning,
        kDesigning
    };

    virtual void Init(void);
    virtual void Running(void);
    virtual void Designing(void);
    virtual void InitDisplay(void);
    virtual void RunningDisplay(void);
    virtual void DesigningDisplay(void);

    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

    void HandleContractStart(CoreXML& inXML);
    void HandleContractEnd(CoreXML& inXML);
    void HandleScriptStart(CoreXML& inXML);
    void HandleScriptEnd(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };
    
private:
    typedef map<string, void (GameContract::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    U32 m_pickleState;
    CoreScript m_script;

    GameState m_gameState;
    GameFloorMap *m_floorMap;
    GameTileMap *m_tileMap;
    GamePiecePlayer *m_player;
    tVal m_fps;
    U32 m_frames;
    GameFloorDesigner *m_floorDesigner;
    GameView *m_currentView;
};

inline ostream& operator<<(ostream &inOut, const GameContract& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}

#endif
