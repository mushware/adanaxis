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
 * $Id: GameMapArea.cpp,v 1.8 2003/01/13 14:31:59 southa Exp $
 * $Log: GameMapArea.cpp,v $
 * Revision 1.8  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.7  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.6  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.4  2002/10/10 13:51:16  southa
 * Speed fixes and various others
 *
 * Revision 1.3  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/16 17:48:08  southa
 * Collision and optimisation work
 *
 */

#include "GameMapArea.h"

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

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

bool
GameMapArea::IsEmpty(void) const
{
    return (m_rectangles.size() == 0 &&
            m_points.size() == 0);
}
