#ifndef GLRENDER_H
#define GLRENDER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GLRender.h,v 1.6 2003/01/11 13:03:11 southa Exp $
 * $Log: GLRender.h,v $
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
#include "Mushcore.h"

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


#endif
