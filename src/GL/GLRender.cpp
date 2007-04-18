//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLRender.cpp
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
//%Header } B72hrbyC9veGkO/KDFdOyg
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
