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
 * $Id$
 * $Log$
 */

#include "GLVector.h"
#include "GLUtils.h"

void
GLVector::Render(void) const
{
    glBegin(GL_POINTS);
    GLUtils::Vertex(x, y, z);
    glEnd();
}
