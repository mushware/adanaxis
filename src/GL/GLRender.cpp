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
 * $Id: GLRender.cpp,v 1.5 2002/12/29 20:59:52 southa Exp $
 * $Log: GLRender.cpp,v $
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
