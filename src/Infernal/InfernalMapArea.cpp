//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalMapArea.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } N/Ksv2fIuEazMRWTVRqxpQ
/*
 * $Id: InfernalMapArea.cpp,v 1.5 2005/05/19 13:02:05 southa Exp $
 * $Log: InfernalMapArea.cpp,v $
 * Revision 1.5  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.3  2003/10/04 15:32:10  southa
 * Module split
 *
 * Revision 1.2  2003/10/04 12:44:35  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:06  southa
 * File renaming
 *
 * Revision 1.10  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:08:48  southa
 * Fixed file headers
 *
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

#include "InfernalMapArea.h"

#include "InfernalSTL.h"

using namespace Mushware;
using namespace std;

void
InfernalMapArea::RectangleAdd(const GLRectangle& inRectangle)
{
    m_rectangles.push_back(inRectangle);
}

void
InfernalMapArea::CircleAdd(const GLPoint& inPoint, tVal inRadius)
{
    m_points.push_back(inPoint);
    m_radiiSquared.push_back(inRadius*inRadius);
}

bool
InfernalMapArea::IsWithin(const GLPoint& inPoint) const
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
InfernalMapArea::MinPointGet(void) const
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
InfernalMapArea::MaxPointGet(void) const
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
InfernalMapArea::BoundingBoxGet(void) const
{
    return GLRectangle(MinPointGet(), MaxPointGet());
}

bool
InfernalMapArea::IsEmpty(void) const
{
    return (m_rectangles.size() == 0 &&
            m_points.size() == 0);
}
