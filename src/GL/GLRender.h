//%includeGuardStart {
#ifndef GLRENDER_H
#define GLRENDER_H
//%includeGuardStart } Y+fiEOiRr+UML9oBaQneSA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLRender.h
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
//%Header } xn+pO6LbYGEEpR4WbXYs3w
/*
 * $Id: GLRender.h,v 1.13 2006/06/01 15:38:52 southa Exp $
 * $Log: GLRender.h,v $
 * Revision 1.13  2006/06/01 15:38:52  southa
 * DrawArray verification and fixes
 *
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
