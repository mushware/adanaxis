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
 * $Id: GLQuad.cpp,v 1.5 2002/08/07 13:36:47 southa Exp $
 * $Log: GLQuad.cpp,v $
 * Revision 1.5  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.4  2002/08/01 16:47:10  southa
 * First multi-box collsion checking
 *
 * Revision 1.3  2002/07/23 14:22:52  southa
 * Rotation fix
 *
 * Revision 1.2  2002/07/23 14:10:46  southa
 * Added GameMotion
 *
 * Revision 1.1  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 */

#include "GLQuad.h"
#include "GLStandard.h"
#include "GLRectangle.h"


GLQuad::GLQuad(const GLRectangle& inRectangle)
{
    m_points[0].x=inRectangle.xmin;
    m_points[0].y=inRectangle.ymin;
    m_points[1].x=inRectangle.xmax;
    m_points[1].y=inRectangle.ymin;
    m_points[2].x=inRectangle.xmax;
    m_points[2].y=inRectangle.ymax;
    m_points[3].x=inRectangle.xmin;
    m_points[3].y=inRectangle.ymax;
}    

const GLQuad&
GLQuad::operator+=(const GLPoint& inPoint)
{
    for (U32 i=0; i<4; ++i)
    {
        m_points[i].x += inPoint.x;
        m_points[i].y += inPoint.y;
    }
    return *this;
}

void
GLQuad::CentreGet(GLPoint& outPoint) const
{
    tVal x=0;
    tVal y=0;
    
    for (U32 i=0; i<4; ++i)
    {
        x += m_points[i].x/4;
        y += m_points[i].y/4;
    }
    outPoint.x=x;
    outPoint.y=y;
}

void
GLQuad::RotateAboutCentre(tVal inAngle)
{
    GLPoint centre;
    CentreGet(centre);
    for (U32 i=0; i<4; ++i)
    {
        tVal x = m_points[i].x - centre.x;
        tVal y = m_points[i].y - centre.y;
        
        m_points[i].x = centre.x + x*cos(inAngle) + y*sin(inAngle);
        m_points[i].y = centre.y + y*cos(inAngle) - x*sin(inAngle);
    }
}

const GLPoint&
GLQuad::PointGet(U32 inWhich) const
{
    COREASSERT(inWhich < 4);
    return m_points[inWhich];
}

void
GLQuad::PointSet(U32 inWhich, const GLPoint &inPoint)
{
    COREASSERT(inWhich < 4);
    m_points[inWhich] = inPoint;
}

void
GLQuad::BoundingRectangleGet(GLRectangle& outRect) const
{
    outRect=GLRectangle(m_points[0], m_points[0]);
    for (U32 i=1; i<4; ++i)
    {
        if (m_points[i].x < outRect.xmin) outRect.xmin=m_points[i].x;
        if (m_points[i].y < outRect.ymin) outRect.ymin=m_points[i].y;
        if (m_points[i].x > outRect.xmax) outRect.xmax=m_points[i].x;
        if (m_points[i].y > outRect.ymax) outRect.ymax=m_points[i].y;
    }
}

void
GLQuad::Render(void) const
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(m_points[0].x, m_points[0].y);
    glVertex2f(m_points[1].x, m_points[1].y);
    glVertex2f(m_points[2].x, m_points[2].y);
    glVertex2f(m_points[3].x, m_points[3].y);
    glEnd();
}
    
