//%includeGuardStart {
#ifndef GLTEXTUREDEF_H
#define GLTEXTUREDEF_H
//%includeGuardStart } qL7Y8RwqMVx301+wicLY9Q
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureDef.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } A/CNrT+Qg4gpGy329MDcbA
/*
 * $Id: GLTextureDef.h,v 1.11 2004/01/06 20:46:49 southa Exp $
 * $Log: GLTextureDef.h,v $
 * Revision 1.11  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.10  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.9  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:31  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.6  2003/01/09 14:56:59  southa
 * Created Mushcore
 *
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
#include "mushMushcore.h"

class GLTextureDef
{
public:
    GLTextureDef(): m_needsAlphaValid(false), m_dataPtr(NULL) {}
    GLTextureDef(Mushware::U32 *inDataPtr): m_needsAlphaValid(false), m_dataPtr(inDataPtr) {}
    ~GLTextureDef() {if (m_autoMonkey.FreeInDestructor(m_dataPtr)) delete[] m_dataPtr;}
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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
