/*
 * $Id$
 * $Log$
 */

#include "GLTextureDef.h"

bool
GLTextureDef::NeedsAlpha(void) const
{
    if (!m_needsAlphaValid)
    {
        DetermineNeedsAlpha();
    }
    return m_needsAlpha;
}

void
GLTextureDef::DetermineNeedsAlpha(void) const
{
    U8 *dataPtr=reinterpret_cast<U8 *>(m_dataPtr);
    U32 dataSize=m_width*m_height; // Number of pixels to check
    
    COREASSERT(dataPtr != NULL || dataSize == 0);

    m_needsAlpha=false;
    dataPtr += 3; // Advance to first alpha byte
    for (U32 i=0; i<dataSize; ++i)
    {
        if (*dataPtr != 255)
        {
            m_needsAlpha = true;
            break;
        }
        dataPtr+=4;
    }
    m_needsAlphaValid=true;
}
