#ifndef GLTEXTURETIFF_H
#define GLTEXTURETIFF_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GLTextureTIFF.h,v 1.5 2002/08/27 08:56:21 southa Exp $
 * $Log: GLTextureTIFF.h,v $
 * Revision 1.5  2002/08/27 08:56:21  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:05  southa
 * Build process fixes
 *
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
