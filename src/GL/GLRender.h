#ifndef GLRENDER_H
#define GLRENDER_H
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
 * $Id: GLRender.h,v 1.2 2002/10/12 17:34:20 southa Exp $
 * $Log: GLRender.h,v $
 * Revision 1.2  2002/10/12 17:34:20  southa
 * Wall edges
 *
 * Revision 1.1  2002/10/12 15:24:58  southa
 * Facet renderer
 *
 */

#include "mushCore.h"
#include "GLStandard.h"
#include "GLState.h"
#include "GLTextureRef.h"

class GLTextureRef;

class GLRender
{
public:
    static void VertexArraySet(const GLfloat (*inArray)[3])
    {
        glVertexPointer(3, GL_FLOAT, 0, inArray);
        m_vertexArray=inArray;
    }
    static void TexCoordArraySet(const GLfloat (*inArray)[2])
    {
        glTexCoordPointer(2, GL_FLOAT, 0, inArray);
        m_texCoordArray=inArray;
    }
    static void NormalArraySet(const GLfloat (*inArray)[3])
    {
        glNormalPointer(GL_FLOAT, 0, inArray);
        m_normalArray=inArray;
    }
    static void TextureSet(const GLTextureRef& inTexRef)
    {
        GLState::BindTexture(inTexRef.BindingNameGet());
        GLState::TextureEnable();
    }
    static void DrawArrays(GLenum inType, U32 inSize)
    {
        glDrawArrays(inType, 0, inSize);
    }
    static void ArraysToList(GLenum inType, U32 inSize);

private:
    static const GLfloat (*m_vertexArray)[3];
    static const GLfloat (*m_texCoordArray)[2];
    static const GLfloat (*m_normalArray)[3];
};


#endif
