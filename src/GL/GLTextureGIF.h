#ifndef GLTEXTUREGIF_H
#define GLTEXTUREGIF_H
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
 * $Id: GLTextureGIF.h,v 1.1 2002/05/10 16:40:38 southa Exp $
 * $Log: GLTextureGIF.h,v $
 * Revision 1.1  2002/05/10 16:40:38  southa
 * Changed .hp files to .h
 *
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

#endif
