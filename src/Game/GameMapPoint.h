#ifndef GAMEMAPPOINT_H
#define GAMEMAPPOINT_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameMapPoint.h,v 1.7 2003/01/11 13:03:14 southa Exp $
 * $Log: GameMapPoint.h,v $
 * Revision 1.7  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.6  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:24  southa
 * Source conditioning
 *
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

#include "Mushcore.h"
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
