#ifndef GAMEMOTIONSPEC_H
#define GAMEMOTIONSPEC_H
/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"
#include "mushGL.h"

class GameMotionSpec
{
public:
    GameMotionSpec();
    
    GLPoint pos;
    tVal angle;
    GLRectangle shape;
    GLPoint deltaPos;
    tVal deltaAngle;
};
#endif
