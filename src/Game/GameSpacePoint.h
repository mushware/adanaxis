#ifndef GAMESPACEPOINT_H
#define GAMESPACEPOINT_H
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
 * $Id: GameSpacePoint.h,v 1.3 2002/08/07 13:36:50 southa Exp $
 * $Log: GameSpacePoint.h,v $
 * Revision 1.3  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.2  2002/08/01 16:47:12  southa
 * First multi-box collsion checking
 *
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
#endif
