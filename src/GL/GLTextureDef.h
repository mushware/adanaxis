/*
 * $Id$
 * $Log$
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
