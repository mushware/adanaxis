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
 * $Id$
 * $Log$
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
    }
    static void TexCoordArraySet(const GLfloat (*inArray)[2])
    {
        glTexCoordPointer(2, GL_FLOAT, 0, inArray);
    }
    static void TextureSet(const GLTextureRef& inTexRef)
    {
        GLState::BindTexture(inTexRef.BindingNameGet());
        GLState::TextureEnable();
    }

    static void VertexTextureArrayQuads(U32 inSize)
    {
        glDrawArrays(GL_QUADS, 0, inSize);
    }

private:
};


#endif
