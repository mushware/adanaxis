/*
 * $Id$
 * $Log$
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
        
        m_points[i].x = centre.x + x*cos(inAngle) + y*cos(inAngle);
        m_points[i].y = centre.y + y*cos(inAngle) - x*cos(inAngle);
    }
}

const GLPoint&
GLQuad::GetPoint(U32 inWhich) const
{
    COREASSERT(inWhich < 4);
    return m_points[inWhich];
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
    