#ifndef GAMEMOTIONSPEC_H
#define GAMEMOTIONSPEC_H
/*
 * $Id: GameMotionSpec.h,v 1.1 2002/07/18 11:40:35 southa Exp $
 * $Log: GameMotionSpec.h,v $
 * Revision 1.1  2002/07/18 11:40:35  southa
 * Overplotting and movement
 *
 */

#include "mushCore.h"
#include "mushGL.h"

class GameMotionSpec
{
public:
    GameMotionSpec();
    void Render(void) const;
    
    GLPoint pos;
    tVal angle;
    GLRectangle shape;
    GLPoint deltaPos;
    tVal deltaAngle;
};
#endif
