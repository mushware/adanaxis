/*
 * $Id: GameSpacePoint.h,v 1.1 2002/07/31 16:27:17 southa Exp $
 * $Log: GameSpacePoint.h,v $
 * Revision 1.1  2002/07/31 16:27:17  southa
 * Collision checking work
 *
 */

#include "mushCore.h"
#include "mushGL.h"

class GameSpacePoint : public GLPoint
{
public:
    GameSpacePoint() {}
    explicit GameSpacePoint(const GLPoint& inPoint) { x=inPoint.x; y=inPoint.y; }

private:
    GameSpacePoint(const GameMapPoint &inPoint) {} // prevent this
    GameSpacePoint& operator=(const GameMapPoint& inPoint) { return *this; } // prevent this
};
