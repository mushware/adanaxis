/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"
#include "mushGL.h"

class GameSpacePoint : public GLPoint
{
public:
    explicit GameSpacePoint(const GLPoint& inPoint) { x=inPoint.x; y=inPoint.y; }
};
