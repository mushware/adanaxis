/*
 * $Id$
 * $Log$
 */

#include "GameMotionSpec.h"

GameMotionSpec::GameMotionSpec() :
    pos(GLPoint(0,0)),
    angle(0),
    shape(GLRectangle(0,0,0,0)),
    deltaPos(GLPoint(0,0)),
    deltaAngle(0)
{
}
