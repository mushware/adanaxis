/*
 * $Id$
 * $Log$
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
