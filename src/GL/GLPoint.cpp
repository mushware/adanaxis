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
 * $Id: GLPoint.cpp,v 1.1 2002/07/18 11:40:34 southa Exp $
 * $Log: GLPoint.cpp,v $
 * Revision 1.1  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
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
