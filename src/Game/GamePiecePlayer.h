/*
 * $Id$
 * $Log$
 */

#include "GamePiece.h"

class GameGraphic;
class GameController;

class GamePiecePlayer: public GamePiece
{
public:
    GamePiecePlayer():
    m_x(0),
    m_y(0),
    m_angle(0),
    m_controllerName("controller1"),
    m_controller(NULL)
        {}
    virtual ~GamePiecePlayer() {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual void Move(void);
    virtual void Render(void);
    virtual string TypeNameGet(void) const {return "player";};

    tVal XGet(void) {return m_x;}
    tVal YGet(void) {return m_y;}
    tVal AngleGet(void) {return m_angle;}
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void HandlePlayerEnd(CoreXML& inXML);
    void HandleNameEnd(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef map<string, void (GamePiecePlayer::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;

    tVal m_x;
    tVal m_y;
    tVal m_angle;
    vector <GameGraphic *> m_graphics;
    string m_controllerName;
    mutable GameController *m_controller; // in GameData
};

inline ostream& operator<<(ostream &inOut, const GamePiecePlayer& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}