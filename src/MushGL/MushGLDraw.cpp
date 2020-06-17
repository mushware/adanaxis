//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLDraw.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } lt9iCKaqvh7pvuD7YmMSww
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
