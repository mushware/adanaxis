//%includeGuardStart {
#ifndef GAMEPIECE_H
#define GAMEPIECE_H
//%includeGuardStart } q9phvipr2Sb7bVhTMJCVdg
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GamePiece.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } nvXZRnl1q6KAg5yZslhO+w
/*
 * $Id: GamePiece.h,v 1.17 2003/08/21 23:08:51 southa Exp $
 * $Log: GamePiece.h,v $
 * Revision 1.17  2003/08/21 23:08:51  southa
 * Fixed file headers
 *
 * Revision 1.16  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.15  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.14  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.13  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.12  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 * Revision 1.11  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 * Revision 1.10  2002/11/24 23:18:23  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.9  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:25  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/18 15:13:15  southa
 * Adhesion handling
 *
 * Revision 1.6  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/18 11:40:35  southa
 * Overplotting and movement
 *
 * Revision 1.4  2002/07/16 17:48:08  southa
 * Collision and optimisation work
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

class GLPoint;
class GameControlFrameDef;
class GameMotionSpec;
class GameFloorMap;

class GamePiece: public MushcorePickle, protected MushcoreXMLHandler
{
public:
    GamePiece() {}
    virtual ~GamePiece() {}
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const = 0;
    virtual void Unpickle(MushcoreXML& inXML) = 0;
    virtual void Render(void) = 0;
    virtual void EnvironmentRead(const GameFloorMap& inFloorMap) {}
    virtual void MoveGet(GameMotionSpec& outSpec, const GameControlFrameDef& inDef) const = 0;
    virtual void MoveConfirm(const GameMotionSpec& inSpec) = 0;
    virtual char *TypeNameGet(void) const = 0;
    
protected:
    void UnpicklePrologue(void) {}
    void UnpickleEpilogue(void) {}

private:
};

inline std::ostream& operator<<(std::ostream &inOut, const GamePiece& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
