/*
 * $Id: GameMapPoint.h,v 1.1 2002/07/31 16:27:16 southa Exp $
 * $Log: GameMapPoint.h,v $
 * Revision 1.1  2002/07/31 16:27:16  southa
 * Collision checking work
 *
 */

#include "mushCore.h"
#include "mushGL.h"

class GameSpacePoint;

class GameMapPoint : public GLPoint
{
public:
    GameMapPoint() {}
    explicit GameMapPoint(const GLPoint& inPoint) { x=inPoint.x; y=inPoint.y; }

private:
    GameMapPoint(const GameSpacePoint &inPoint) {} // prevent this
    GameMapPoint& operator=(const GameSpacePoint& inPoint) { return *this; } // prevent this
};
