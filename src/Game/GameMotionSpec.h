#ifndef GAMEMOTIONSPEC_H
#define GAMEMOTIONSPEC_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: GameMotionSpec.h,v 1.6 2002/08/27 08:56:24 southa Exp $
 * $Log: GameMotionSpec.h,v $
 * Revision 1.6  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/09 17:09:04  southa
 * GameDialogue added
 *
 * Revision 1.4  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.3  2002/08/05 13:37:29  southa
 * Windback work
 *
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
    GameMotionSpec() {}
    GameMotionSpec(const GLPoint& inPoint, tVal inAngle);
    void Windback(tVal inScale);
    const GameMotionSpec WindbackGet(tVal inScale) const;
    void ApplyDelta(void);
    void Render(void) const;
    void ZeroSet(void);
    
    GLPoint pos;
    tVal angle;
    GLRectangle shape;
    GLPoint deltaPos;
    tVal deltaAngle;
};
#endif
