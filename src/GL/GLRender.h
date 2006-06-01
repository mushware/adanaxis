//%includeGuardStart {
#ifndef GLRENDER_H
#define GLRENDER_H
//%includeGuardStart } Y+fiEOiRr+UML9oBaQneSA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLRender.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } B9I13uB44WrymglfRfbUCg
/*
 * $Id: GLRender.h,v 1.12 2005/05/19 13:01:59 southa Exp $
 * $Log: GLRender.h,v $
 * Revision 1.12  2005/05/19 13:01:59  southa
 * Mac release work
 *
 * Revision 1.11  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 * Revision 1.10  2004/01/06 20:46:49  southa
 * Build fixes
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
 * Revision 1.6  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.5  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.3  2002/10/14 13:03:00  southa
 * Display std::list test
 *
 * Revision 1.2  2002/10/12 17:34:20  southa
 * Wall edges
 *
 * Revision 1.1  2002/10/12 15:24:58  southa
 * Facet renderer
 *
 */

#include "GLStandard.h"
#include "GLState.h"
#include "GLTextureRef.h"
#include "mushMushcore.h"

class GLTextureRef;

class GLRender
{
public:
    static void VertexArraySet(const GLfloat (*inArray)[3])
    {
        glVertexPointer(3, GL_FLOAT, 0, inArray);
        m_vertexArray=inArray;
    }
    static void VertexArraySet(const GLfloat *inArray)
    {
        glVertexPointer(3, GL_FLOAT, 0, inArray);
    }
    
    static void TexCoordArraySet(const GLfloat (*inArray)[2])
    {
        glTexCoordPointer(2, GL_FLOAT, 0, inArray);
        m_texCoordArray=inArray;
    }
    static void TexCoordArraySet(const GLfloat *inArray)
    {
        glTexCoordPointer(4, GL_FLOAT, 0, inArray);
    }

    static void NormalArraySet(const GLfloat (*inArray)[3])
    {
        glNormalPointer(GL_FLOAT, 0, inArray);
        m_normalArray=inArray;
    }

    static void NormalArraySet(const GLfloat *inArray)
    {
        glNormalPointer(GL_FLOAT, 0, inArray);
    }
    
    static void TextureSet(const GLTextureRef& inTexRef)
    {
        GLState::BindTexture(inTexRef.BindingNameGet());
        GLState::TextureEnable();
    }
    static void DrawArrays(GLenum inType, Mushware::U32 inSize)
    {
        glDrawArrays(inType, 0, inSize);
    }
    static void ArraysToList(GLenum inType, Mushware::U32 inSize);

private:
    static const GLfloat (*m_vertexArray)[3];
    static const GLfloat (*m_texCoordArray)[2];
    static const GLfloat (*m_normalArray)[3];
};


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
