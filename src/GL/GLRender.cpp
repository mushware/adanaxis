/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GLRender.cpp,v 1.2 2002/10/14 13:03:00 southa Exp $
 * $Log: GLRender.cpp,v $
 * Revision 1.2  2002/10/14 13:03:00  southa
 * Display list test
 *
 * Revision 1.1  2002/10/12 15:24:58  southa
 * Facet renderer
 *
 */

#include "GLRender.h"

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
