#ifndef GLTEXTUREDEF_H
#define GLTEXTUREDEF_H
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
 * $Id: GLTextureDef.h,v 1.3 2002/08/27 08:56:20 southa Exp $
 * $Log: GLTextureDef.h,v $
 * Revision 1.3  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 */

#include "mushCore.h"
#include "GLStandard.h"

class GLTextureDef
{
public:
    GLTextureDef(): m_needsAlphaValid(false), m_dataPtr(NULL) {}
    GLTextureDef(U32 *inDataPtr): m_needsAlphaValid(false), m_dataPtr(inDataPtr) {}
    ~GLTextureDef() {if (m_autoMonkey.FreeInDestructor(m_dataPtr)) delete[]m_dataPtr;}
    void WidthSet(GLsizei inWidth) {m_width=inWidth;}
    void HeightSet(GLsizei inHeight) {m_height=inHeight;}
    void PixelFormatSet(GLenum inPixelFormat) {m_pixelFormat=inPixelFormat;}
    void PixelTypeSet(GLenum inPixelType) {m_pixelType=inPixelType;}
    bool Valid(void) const {return (m_dataPtr != NULL);}
    GLsizei Width(void) const {return m_width;}
    GLsizei Height(void) const {return m_height;}
    GLenum PixelFormat(void) const {return m_pixelFormat;}
    GLenum PixelType(void) const {return m_pixelType;}
    bool NeedsAlpha(void) const;
    U32 *DataPtr(void) const {return m_dataPtr;}

private:
    void DetermineNeedsAlpha(void) const;
    
    GLsizei m_width;
    GLsizei m_height;
    GLenum m_pixelFormat;
    GLenum m_pixelType;
    mutable bool m_needsAlpha;
    mutable bool m_needsAlphaValid;
    U32 *m_dataPtr;
    CoreAutoMonkey m_autoMonkey;
};
#endif
