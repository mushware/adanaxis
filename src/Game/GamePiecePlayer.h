#ifndef GAMEPIECEPLAYER_H
#define GAMEPIECEPLAYER_H
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
 * $Id: GamePiecePlayer.h,v 1.9 2002/07/23 14:10:47 southa Exp $
 * $Log: GamePiecePlayer.h,v $
 * Revision 1.9  2002/07/23 14:10:47  southa
 * Added GameMotion
 *
 * Revision 1.8  2002/07/18 13:53:48  southa
 * Tuned player motion
 *
 * Revision 1.7  2002/07/18 11:40:36  southa
 * Overplotting and movement
 *
 * Revision 1.6  2002/07/16 19:30:09  southa
 * Simplistic collision checking
 *
 * Revision 1.5  2002/07/16 17:48:08  southa
 * Collision and optimisation work
 *
 * Revision 1.4  2002/07/10 16:16:31  southa
 * Player graphic
 *
 * Revision 1.3  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.1  2002/06/05 15:53:26  southa
 * Player and keyboard control
 *
 */

#include "GamePiece.h"
#include "GameMotion.h"

class GameGraphic;
class GameController;

class GamePiecePlayer: public GamePiece
{
public:
    GamePiecePlayer():
    m_controllerName("controller1"),
    m_controller(NULL)
        {}
    virtual ~GamePiecePlayer() {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual void MoveGet(GameMotionSpec& inSpec) const;
    virtual void MoveConfirm(const GameMotionSpec& inSpec);
    virtual void Render(void);
    virtual string TypeNameGet(void) const {return "player";};

    tVal XGet(void) {return m_motion.MotionSpecGet().pos.x;}
    tVal YGet(void) {return m_motion.MotionSpecGet().pos.y;}
    const GLPoint& PositionGet(void) { return m_motion.MotionSpecGet().pos; }
    tVal AngleGet(void) {return m_motion.MotionSpecGet().angle;}
    const GameMotionSpec& MotionSpecGet(void) const { return m_motion.MotionSpecGet(); }
    
    static CoreScalar LoadPlayer(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static void Install(void);

protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void HandleMotionStart(CoreXML& inXML);
    void HandlePlayerStart(CoreXML& inXML);
    void HandlePlayerEnd(CoreXML& inXML);
    void HandleGraphicStart(CoreXML& inXML);
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

    GameMotion m_motion;
    tVal m_adhesion;
    vector <GameGraphic *> m_graphics;
    string m_controllerName;
    mutable GameController *m_controller; // in GameData
};

inline ostream& operator<<(ostream &inOut, const GamePiecePlayer& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
