#ifndef GAMEMOTIONSPEC_H
#define GAMEMOTIONSPEC_H
/*
 * $Id: GameMotionSpec.h,v 1.2 2002/07/23 14:10:47 southa Exp $
 * $Log: GameMotionSpec.h,v $
 * Revision 1.2  2002/07/23 14:10:47  southa
 * Added GameMotion
 *
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
    void Windback(tVal inScale);
    const GameMotionSpec WindbackGet(tVal inScale) const;
    void Render(void) const;
    
    GLPoint pos;
    tVal angle;
    GLRectangle shape;
    GLPoint deltaPos;
    tVal deltaAngle;
};
#endif
