#ifndef GAMEMAPPOINT_H
#define GAMEMAPPOINT_H
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
 * $Id: GameMapPoint.h,v 1.3 2002/08/07 13:36:50 southa Exp $
 * $Log: GameMapPoint.h,v $
 * Revision 1.3  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.2  2002/08/01 16:47:12  southa
 * First multi-box collsion checking
 *
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
#endif
