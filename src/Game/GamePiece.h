#ifndef GAMEPIECE_H
#define GAMEPIECE_H
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
 * $Id: GamePiece.h,v 1.13 2002/12/20 13:17:41 southa Exp $
 * $Log: GamePiece.h,v $
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
 * Added type name accessor to CorePickle
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

#include "mushCore.h"

class GLPoint;
class GameControlFrameDef;
class GameMotionSpec;
class GameFloorMap;

class GamePiece: public CorePickle, protected CoreXMLHandler
{
public:
    GamePiece() {}
    virtual ~GamePiece() {}
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const = 0;
    virtual void Unpickle(CoreXML& inXML) = 0;
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
#endif
