/*
 * $Id$
 * $Log$
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
