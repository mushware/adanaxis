#ifndef GAMEMAPAREA_H
#define GAMEMAPAREA_H
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
 * $Id: GameMapArea.h,v 1.1 2002/07/16 17:48:08 southa Exp $
 * $Log: GameMapArea.h,v $
 * Revision 1.1  2002/07/16 17:48:08  southa
 * Collision and optimisation work
 *
 */

#include "mushCore.h"
#include "mushGL.h"

class GameMapArea
{
public:
    void RectangleAdd(const GLRectangle& inRectangle);
    void CircleAdd(const GLPoint& inPoint, tVal inRadius);
    bool IsWithin(const GLPoint& inPoint) const;
    const GLPoint MinPointGet(void) const;
    const GLPoint MaxPointGet(void) const;
    const GLRectangle BoundingBoxGet(void) const;
    
private:
    vector<GLRectangle> m_rectangles;
    vector<tVal> m_radiiSquared;
    vector<GLPoint> m_points;
};
#endif
