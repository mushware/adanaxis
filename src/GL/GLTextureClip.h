#ifndef GLTEXTURECLIP_H
#define GLTEXTURECLIP_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLTextureClip.h,v 1.6 2002/10/22 20:42:01 southa Exp $
 * $Log: GLTextureClip.h,v $
 * Revision 1.6  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/28 16:37:40  southa
 * Texture references and decomposer
 *
 */

#include "GLTexture.h"

class GLTextureClip : public GLTexture
{
public:
    GLTextureClip(const GLTexture& inTex, Mushware::U32 inX1, Mushware::U32 inY1, Mushware::U32 inX2, Mushware::U32 inY2);
    GLTextureClip *Clone(void) const {return new GLTextureClip(*this);}

protected:

private:
    const char *FiletypeName(void) const;
};
#endif
