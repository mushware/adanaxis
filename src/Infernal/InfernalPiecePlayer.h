//%includeGuardStart {
#ifndef INFERNALPIECEPLAYER_H
#define INFERNALPIECEPLAYER_H
//%includeGuardStart } rlQIUvcen6uu6xVsAaDz+g
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalPiecePlayer.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } QArvKp6Us6D/57JZwuM6eg
/*
 * $Id: InfernalPiecePlayer.h,v 1.6 2006/06/01 15:39:04 southa Exp $
 * $Log: InfernalPiecePlayer.h,v $
 * Revision 1.6  2006/06/01 15:39:04  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/04 15:32:11  southa
 * Module split
 *
 * Revision 1.1  2003/10/04 12:44:36  southa
 * File renaming
 *
 * Revision 1.32  2003/10/04 12:23:01  southa
 * File renaming
 *
 * Revision 1.31  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
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
 * Added InfernalMotion
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

#include "mushMushcore.h"

#include "InfernalFloorMap.h"
#include "InfernalMotion.h"
#include "InfernalPiece.h"

#include "mushGame.h"

class GameGraphic;

class InfernalPiecePlayer: public InfernalPiece
{
public:
    InfernalPiecePlayer();
    virtual ~InfernalPiecePlayer() {}
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual void MoveGet(InfernalMotionSpec& outSpec, const GameControlFrameDef& inDef) const;
    virtual void MoveConfirm(const InfernalMotionSpec& inSpec);
    virtual void EnvironmentRead(const InfernalFloorMap& inFloorMap);
    virtual void Render(void);
    virtual char *TypeNameGet(void) const;

    Mushware::tVal XGet(void) {return m_motion.MotionSpecGet().pos.x;}
    Mushware::tVal YGet(void) {return m_motion.MotionSpecGet().pos.y;}
    const GLPoint& PositionGet(void) { return m_motion.MotionSpecGet().pos; }
    Mushware::tVal AngleGet(void) {return m_motion.MotionSpecGet().angle;}
    const InfernalMotionSpec& MotionSpecGet(void) const { return m_motion.MotionSpecGet(); }
    const InfernalFloorMap::tMapVector& StandingOnGet(void) { return m_standingOn; }
    
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

    typedef std::map<std::string, void (InfernalPiecePlayer::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;

    enum
    {
        kFrameDefBufferSize=100
    };

    InfernalMotion m_motion;
    Mushware::tVal m_adhesion;
    std::vector <GameGraphic *> m_graphics;
    Mushware::tVal m_speedLim;
    Mushware::tVal m_acceleration;
    InfernalFloorMap::tMapVector m_standingOn;
    MushcoreHistory<Mushware::U32, GameControlFrameDef> m_frameDefHistory;
    bool m_imageIs;
};

inline std::ostream& operator<<(std::ostream &inOut, const InfernalPiecePlayer& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
