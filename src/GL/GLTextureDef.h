#ifndef GLTEXTUREDEF_H
#define GLTEXTUREDEF_H
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
 * $Id: GLTextureDef.h,v 1.5 2002/12/20 13:17:36 southa Exp $
 * $Log: GLTextureDef.h,v $
 * Revision 1.5  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:01  southa
 * Source conditioning
 *
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

#include "GLStandard.h"
#include "mushCore.h"

class GLTextureDef
{
public:
    GLTextureDef(): m_needsAlphaValid(false), m_dataPtr(NULL) {}
    GLTextureDef(Mushware::U32 *inDataPtr): m_needsAlphaValid(false), m_dataPtr(inDataPtr) {}
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
    Mushware::U32 *DataPtr(void) const {return m_dataPtr;}

private:
    void DetermineNeedsAlpha(void) const;
    
    GLsizei m_width;
    GLsizei m_height;
    GLenum m_pixelFormat;
    GLenum m_pixelType;
    mutable bool m_needsAlpha;
    mutable bool m_needsAlphaValid;
    Mushware::U32 *m_dataPtr;
    MushcoreAutoMonkey m_autoMonkey;
};
#endif
