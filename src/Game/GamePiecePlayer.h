//%includeGuardStart {
#ifndef GAMEPIECEPLAYER_H
#define GAMEPIECEPLAYER_H
//%includeGuardStart } ja1RTnDkMy390nDBve3cKw
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GamePiecePlayer.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Xkb9AaqPPoJ778vYkqsb9Q
/*
 * $Id: GamePiecePlayer.h,v 1.30 2003/08/21 23:08:51 southa Exp $
 * $Log: GamePiecePlayer.h,v $
 * Revision 1.30  2003/08/21 23:08:51  southa
 * Fixed file headers
 *
 * Revision 1.29  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.28  2003/01/11 17:07:52  southa
 * Mushcore library separation
 *
 * Revision 1.27  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.26  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.25  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.24  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
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
 * Added type name accessor to MushcorePickle
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

#include "Mushcore.h"

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
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
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
    MushcoreHistoryIterator<Mushware::U32, GameControlFrameDef> ControlFrameDefIteratorGet(Mushware::U32 inFrameNum) const;
    void ControlFrameDefAdd(const GameControlFrameDef& inDef, Mushware::U32 inFrameNum);
    Mushware::U32 LastValidControlFrameGet(void) const;
    
    static MushcoreScalar LoadPlayer(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void HandleMotionStart(MushcoreXML& inXML);
    void HandlePlayerStart(MushcoreXML& inXML);
    void HandlePlayerEnd(MushcoreXML& inXML);
    void HandleGraphicStart(MushcoreXML& inXML);
    void HandleNameEnd(MushcoreXML& inXML);
    void HandleAccelerationEnd(MushcoreXML& inXML);
    void HandleSpeedLimitEnd(MushcoreXML& inXML);
    void NullHandler(MushcoreXML& inXML);
    
    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<std::string, void (GamePiecePlayer::*)(MushcoreXML& inXML)> ElementFunctionMap;
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
    MushcoreHistory<Mushware::U32, GameControlFrameDef> m_frameDefHistory;
    bool m_imageIs;
};

inline std::ostream& operator<<(std::ostream &inOut, const GamePiecePlayer& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
