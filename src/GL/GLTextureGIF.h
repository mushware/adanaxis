/*
 * $Id: GLTextureGIF.h,v 1.1 2002/02/25 23:05:15 southa Exp $
 * $Log: GLTextureGIF.h,v $
 * Revision 1.1  2002/02/25 23:05:15  southa
 * Subclassed GLTexture
 *
 */

#include "GLTexture.h"

class GLTextureGIF : public GLTexture
{
public:
    GLTextureGIF(const string& inFilename);
    GLTextureGIF *Clone(void) const {return new GLTextureGIF(*this);}

protected:

private:
    void ThrowGifError(const string& inFilename, int inRC);
    const char *FiletypeName(void) const;
};

