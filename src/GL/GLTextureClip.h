#ifndef GLTEXTURECLIP_H
#define GLTEXTURECLIP_H
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
 * $Id: GLTextureClip.h,v 1.1 2002/05/28 16:37:40 southa Exp $
 * $Log: GLTextureClip.h,v $
 * Revision 1.1  2002/05/28 16:37:40  southa
 * Texture references and decomposer
 *
 */

#include "GLTexture.h"

class GLTextureClip : public GLTexture
{
public:
    GLTextureClip(const GLTexture& inTex, U32 inX1, U32 inY1, U32 inX2, U32 inY2);
    GLTextureClip *Clone(void) const {return new GLTextureClip(*this);}

protected:

private:
    const char *FiletypeName(void) const;
};
#endif
