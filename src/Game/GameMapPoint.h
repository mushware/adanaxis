/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"
#include "mushGL.h"

class GameMapPoint : public GLPoint
{
public:
    explicit GameMapPoint(const GLPoint& inPoint) { x=inPoint.x; y=inPoint.y; }
};
