#ifndef GLTEXTURETIFF_H
#define GLTEXTURETIFF_H
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
 * $Id: GLTextureTIFF.h,v 1.8 2002/12/29 20:30:53 southa Exp $
 * $Log: GLTextureTIFF.h,v $
 * Revision 1.8  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.7  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:42:02  southa
 * Source conditioning
 *
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
    GLTextureTIFF(const std::string& inFilename);
    GLTextureTIFF *Clone(void) const {return new GLTextureTIFF(*this);}

protected:

private:
    const char *FiletypeName(void) const;
};
#endif
