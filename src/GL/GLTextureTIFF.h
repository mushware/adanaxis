/*
 * $Id$
 * $Log$
 */

#include "GLTexture.h"

class GLTextureTIFF : public GLTexture
{
public:
    GLTextureTIFF(const string& inFilename);
    GLTextureTIFF *Clone(void) const {return new GLTextureTIFF(*this);}

protected:

private:
    const char *FiletypeName(void) const;
};
