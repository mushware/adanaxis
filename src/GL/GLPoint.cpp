/*
 * $Id$
 * $Log$
 */

#include "GLPoint.h"
#include "GLUtils.h"

void
GLPoint::Render(void) const
{
    glBegin(GL_POINTS);
    GLUtils::Vertex(x, y);
    glEnd();
}