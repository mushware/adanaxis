#ifndef GLTEXTURETIFF_H
#define GLTEXTURETIFF_H
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
 * $Id: GLTextureTIFF.h,v 1.1 2002/05/28 13:07:00 southa Exp $
 * $Log: GLTextureTIFF.h,v $
 * Revision 1.1  2002/05/28 13:07:00  southa
 * Command parser extensions and TIFF loader
 *
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
#endif
