/*
 * $Id$
 * $Log$
 */

#include "GLLine.h"
#include "GLStandard.h"


GLLine::GLLine(const GLPoint& inStart, const GLPoint& inEnd):
    m_start(inStart),
    m_end(inEnd)
{
}

void
GLLine::CentreGet(GLPoint& outPoint) const
{
    outPoint=(m_start+m_end)/2;
}

void
GLLine::RotateAboutCentre(tVal inAngle)
{
    GLPoint centre;
    CentreGet(centre);

    m_start.RotateAboutPoint(centre, inAngle);
    m_end.RotateAboutPoint(centre, inAngle);    
}

const GLPoint&
GLLine::GetStart(void) const
{
    return m_start;
}

const GLPoint&
GLLine::GetEnd(void) const
{
    return m_end;
}

void
GLLine::Render(void) const
{
    glBegin(GL_LINES);
    glVertex2f(m_start.x, m_start.y);
    glVertex2f(m_end.x, m_end.y);
    glEnd();
}
