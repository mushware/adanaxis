/*
 * $Id: GameContract.h,v 1.6 2002/05/31 15:18:16 southa Exp $
 * $Log: GameContract.h,v $
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
        kRunning
    };

    virtual void Init(void);
    virtual void Running(void);
    virtual void InitDisplay(void);
    virtual void RunningDisplay(void);

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
};
