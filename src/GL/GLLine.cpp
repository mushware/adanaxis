/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLLine.cpp,v 1.8 2002/10/22 20:42:00 southa Exp $
 * $Log: GLLine.cpp,v $
 * Revision 1.8  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
 *
 * Revision 1.6  2002/10/10 13:51:16  southa
 * Speed fixes and various others
 *
 * Revision 1.5  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.3  2002/08/01 16:47:09  southa
 * First multi-box collsion checking
 *
 * Revision 1.2  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 * Revision 1.1  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 */

#include "GLLine.h"

#include "GLStandard.h"
#include "GLState.h"
#include "GLUtils.h"

using namespace Mushware;

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

bool
GLLine::IsIntersecting(const GLLine& inLine) const
{
    // This function has been rearranged to avoid a MacOS X compiler bug
    GLPoint a(m_start);
    GLPoint b(m_end);
    GLPoint c(inLine.GetStart());
    GLPoint d(inLine.GetEnd());

    b-=a;
    d-=c;
    
    tVal f = b.x*d.y - b.y*d.x;

    tVal m = d.y*(c.x-a.x)+d.x*(a.y-c.y);
    tVal n = b.y*(c.x-a.x)+b.x*(a.y-c.y);
    
    bool isIntersecting;
    if (f < 0)
    {
        isIntersecting = (m<=0 && m>f && n<=0 && n>f);
    }
    else
    {
        isIntersecting = (m>=0 && m<f && n>=0 && n<f);
    }
    if (isIntersecting)
    {
        return true;
    }
    return false;
}

void
GLLine::Render(void) const
{
    GLState::TextureDisable();
    glBegin(GL_LINES);
    GLUtils::Vertex(m_start.x, m_start.y);
    GLUtils::Vertex(m_end.x, m_end.y);
    glEnd();
}
