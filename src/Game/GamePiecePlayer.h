#ifndef GAMEPIECEPLAYER_H
#define GAMEPIECEPLAYER_H
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
 * $Id: GamePiecePlayer.h,v 1.23 2002/12/10 20:38:05 southa Exp $
 * $Log: GamePiecePlayer.h,v $
 * Revision 1.23  2002/12/10 20:38:05  southa
 * Server timing
 *
 * Revision 1.22  2002/12/04 15:39:58  southa
 * Multiplayer work
 *
 * Revision 1.21  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.20  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 * Revision 1.19  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 * Revision 1.18  2002/11/24 23:18:24  southa
 * Added type name accessor to CorePickle
 *
 * Revision 1.17  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.16  2002/10/08 11:58:53  southa
 * Light cache
 *
 * Revision 1.15  2002/08/27 08:56:25  southa
 * Source conditioning
 *
 * Revision 1.14  2002/08/18 20:44:35  southa
 * Initial chequepoint work
 *
 * Revision 1.13  2002/08/18 15:13:16  southa
 * Adhesion handling
 *
 * Revision 1.12  2002/08/08 18:20:30  southa
 * Plot on screen of dimension 1.0
 *
 * Revision 1.11  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.10  2002/08/05 13:37:29  southa
 * Windback work
 *
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

#include "mushCore.h"

#include "GameControlFrameDef.h"
#include "GameFloorMap.h"
#include "GameMotion.h"
#include "GamePiece.h"

class GameGraphic;

class GamePiecePlayer: public GamePiece
{
public:
    GamePiecePlayer();
    virtual ~GamePiecePlayer() {}
    virtual void Pickle(std::ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual void MoveGet(GameMotionSpec& outSpec, const GameControlFrameDef& inDef) const;
    virtual void MoveConfirm(const GameMotionSpec& inSpec);
    virtual void EnvironmentRead(const GameFloorMap& inFloorMap);
    virtual void Render(void);
    virtual char *TypeNameGet(void) const;

    Mushware::tVal XGet(void) {return m_motion.MotionSpecGet().pos.x;}
    Mushware::tVal YGet(void) {return m_motion.MotionSpecGet().pos.y;}
    const GLPoint& PositionGet(void) { return m_motion.MotionSpecGet().pos; }
    Mushware::tVal AngleGet(void) {return m_motion.MotionSpecGet().angle;}
    const GameMotionSpec& MotionSpecGet(void) const { return m_motion.MotionSpecGet(); }
    const GameFloorMap::tMapVector& StandingOnGet(void) { return m_standingOn; }
    
    bool ImageIs(void) const { return m_imageIs; }
    void ImageIsSet(bool inImageIs) { m_imageIs = inImageIs; }
    bool ControlFrameDefGet(const GameControlFrameDef *& outFrameDef, Mushware::U32 inFrameNum);
    CoreHistoryIterator<U32, GameControlFrameDef> ControlFrameDefIteratorGet(Mushware::U32 inFrameNum) const;
    void ControlFrameDefAdd(const GameControlFrameDef& inDef, Mushware::U32 inFrameNum);
    Mushware::U32 LastValidControlFrameGet(void) const;
    
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
    void HandleAccelerationEnd(CoreXML& inXML);
    void HandleSpeedLimitEnd(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);
    
    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<string, void (GamePiecePlayer::*)(CoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;

    enum
    {
        kFrameDefBufferSize=100
    };

    GameMotion m_motion;
    Mushware::tVal m_adhesion;
    std::vector <GameGraphic *> m_graphics;
    Mushware::tVal m_speedLim;
    Mushware::tVal m_acceleration;
    GameFloorMap::tMapVector m_standingOn;
    CoreHistory<U32, GameControlFrameDef> m_frameDefHistory;
    bool m_imageIs;
};

inline std::ostream& operator<<(std::ostream &inOut, const GamePiecePlayer& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
