/*
 * $Id$
 * $Log$
 */

#include "GameMapArea.h"

void
GameMapArea::RectangleAdd(const GLRectangle& inRectangle)
{
    m_rectangles.push_back(inRectangle);
}

void
GameMapArea::CircleAdd(const GLPoint& inPoint, tVal inRadius)
{
    m_points.push_back(inPoint);
    m_radiiSquared.push_back(inRadius*inRadius);
}

bool
GameMapArea::IsWithin(const GLPoint& inPoint) const
{
    for (U32 i=0; i<m_rectangles.size(); ++i)
    {
        if (m_rectangles[i].IsWithin(inPoint)) return true;
    }

    for (U32 i=0; i<m_points.size(); ++i)
    {
        GLPoint relative = inPoint-m_points[i];
        if (relative.MagnitudeSquared() <= m_radiiSquared[i]) return true;
    }
    return false;
}

const GLPoint
GameMapArea::MinPointGet(void) const
{
    GLPoint outPoint(0,0);
    bool notFoundPoint=true;
    for (U32 i=0; i<m_rectangles.size(); ++i)
    {
        if (notFoundPoint || m_rectangles[i].xmin < outPoint.x)
        {
            outPoint.x = m_rectangles[i].xmin;
        }
        if (notFoundPoint || m_rectangles[i].ymin < outPoint.y)
        {
            outPoint.y = m_rectangles[i].ymin;
        }
        notFoundPoint=false;
    }

    for (U32 i=0; i<m_points.size(); ++i)
    {
        tVal magnitude=sqrt(m_radiiSquared[i]);
        if (notFoundPoint || m_points[i].x-magnitude < outPoint.x)
        {
            outPoint.x = m_points[i].x-magnitude;
        }
        if (notFoundPoint || m_points[i].y-magnitude < outPoint.y)
        {
            outPoint.y = m_points[i].y-magnitude;
        }
        notFoundPoint=false;
    }
    return outPoint;
}    

const GLPoint
GameMapArea::MaxPointGet(void) const
{
    GLPoint outPoint(0,0);
    bool notFoundPoint=true;
    for (U32 i=0; i<m_rectangles.size(); ++i)
    {
        if (notFoundPoint || m_rectangles[i].xmax > outPoint.x)
        {
            outPoint.x = m_rectangles[i].xmax;
        }
        if (notFoundPoint || m_rectangles[i].ymax > outPoint.y)
        {
            outPoint.y = m_rectangles[i].ymax;
        }
        notFoundPoint=false;
    }

    for (U32 i=0; i<m_points.size(); ++i)
    {
        tVal magnitude=sqrt(m_radiiSquared[i]);
        if (notFoundPoint || m_points[i].x+magnitude > outPoint.x)
        {
            outPoint.x = m_points[i].x+magnitude;
        }
        if (notFoundPoint || m_points[i].y+magnitude > outPoint.y)
        {
            outPoint.y = m_points[i].y+magnitude;
        }
        notFoundPoint=false;
    }
    return outPoint;
}

const GLRectangle
GameMapArea::BoundingBoxGet(void) const
{
    return GLRectangle(MinPointGet(), MaxPointGet());
}