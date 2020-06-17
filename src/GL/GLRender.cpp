//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLRender.cpp
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
//%Header } 2mIj8jQ3lsCMr5XYYffcgA
/*
 * $Id: GLRender.cpp,v 1.11 2006/06/01 15:38:52 southa Exp $
 * $Log: GLRender.cpp,v $
 * Revision 1.11  2006/06/01 15:38:52  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/05/19 13:01:59  southa
 * Mac release work
 *
 * Revision 1.9  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:08:26  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.5  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.4  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.2  2002/10/14 13:03:00  southa
 * Display list test
 *
 * Revision 1.1  2002/10/12 15:24:58  southa
 * Facet renderer
 *
 */

#include "GLRender.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

const GLfloat (*GLRender::m_vertexArray)[3] = NULL;
const GLfloat (*GLRender::m_texCoordArray)[2] = NULL;
const GLfloat (*GLRender::m_normalArray)[3] = NULL;

void
GLRender::ArraysToList(GLenum inType, U32 inSize)
{
    glBegin(inType);
    const GLfloat (*vertexArray)[3] = m_vertexArray;
    const GLfloat (*texCoordArray)[2] = m_texCoordArray;
    const GLfloat (*normalArray)[3] = m_normalArray;
    for (U32 i=0; i<inSize; ++i)
    {
        glNormal3f((*normalArray)[0], (*normalArray)[1], (*normalArray)[2]);
        glTexCoord2f((*texCoordArray)[0], (*texCoordArray)[1]);
        glVertex3f((*vertexArray)[0], (*vertexArray)[1], (*vertexArray)[2]);
        ++normalArray;
        ++texCoordArray;
        ++vertexArray;
    }
    glEnd();
}
