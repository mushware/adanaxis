/*
 * $Id: GLLine.cpp,v 1.1 2002/07/16 17:48:07 southa Exp $
 * $Log: GLLine.cpp,v $
 * Revision 1.1  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 */

#include "GLLine.h"

#include "GLStandard.h"
#include "GLUtils.h"

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

    m_start.RotateAboutZ(centre, inAngle);
    m_end.RotateAboutZ(centre, inAngle);    
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
    GLUtils::Vertex(m_start.x, m_start.y);
    GLUtils::Vertex(m_end.x, m_end.y);
    glEnd();
}
