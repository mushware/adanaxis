//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLDraw.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } /RqmIFA9eflC/FQMn36oJw
/*
 * $Id$
 * $Log$
 */

#include "MushGLDraw.h"

using namespace Mushware;
using namespace std;

void
MushGLDraw::QuadsDraw(std::vector<Mushware::t2GLVal> inVertices,
                      std::vector<Mushware::t4GLVal> inColours)
{
    U32 quadLimit = inVertices.size();
    U32 colourLimit = inColours.size();
    
    if ((quadLimit % 4) != 0 ||
        (colourLimit % 4) != 0)
    {
        throw MushcoreDataFail("MushGLDraw::DrawQuad: Wrong vertex or colour size");
    }
    
    glBegin(GL_QUADS);

    for (U32 i=0; i < quadLimit; ++i)
    {
        if (i < colourLimit)
        {
            glColor4fv(&inColours[i].X());
        }
        glVertex2fv(&inVertices[i].X());
    }
    
    glEnd();
}
