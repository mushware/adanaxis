//%includeGuardStart {
#ifndef MUSHGLARRAYS_H
#define MUSHGLARRAYS_H
//%includeGuardStart } g2PetpgsUQpgHIBi+HMQeg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLArrays.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } MtPxJe+UpXQKx2fyU1CPCg

#include "MushGLStandard.h"

class MushGLArrays
{
public:
    static void TriangleStripDraw(const Mushware::t3GLVal *inVertices, Mushware::U32 inSize);
    static void TriangleStripDraw(const Mushware::t3GLVal *inVertices, const Mushware::t3GLVal *inNormals, Mushware::U32 inSize);
    
private:
    static void NormalArrayDisable(void);
    static void NormalArrayEnable(void);
    static void TexCoordArrayDisable(void);
    static void TexCoordArrayEnable(void);
    
    static bool m_normalArrayState;
    static bool m_texCoordArrayState;    
};

inline void
MushGLArrays::NormalArrayDisable(void)
{
    if (m_normalArrayState)
    {
        glDisableClientState(GL_NORMAL_ARRAY);
        m_normalArrayState = false;
    }
}

inline void
MushGLArrays::NormalArrayEnable(void)
{
    if (!m_normalArrayState)
    {
        glEnableClientState(GL_NORMAL_ARRAY);
        m_normalArrayState = true;
    }
}

inline void
MushGLArrays::TexCoordArrayDisable(void)
{
    if (m_texCoordArrayState)
    {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        m_texCoordArrayState = false;
    }
}

inline void
MushGLArrays::TexCoordArrayEnable(void)
{
    if (!m_texCoordArrayState)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        m_texCoordArrayState = true;
    }
}

inline void
MushGLArrays::TriangleStripDraw(const Mushware::t3GLVal *inVertices, Mushware::U32 inSize)
{
    NormalArrayDisable();
    TexCoordArrayDisable();
    glVertexPointer(3, MUSHGL_VALTYPE, 0, inVertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, inSize);
}

inline void
MushGLArrays::TriangleStripDraw(const Mushware::t3GLVal *inVertices, const Mushware::t3GLVal *inNormals, Mushware::U32 inSize)
{
    NormalArrayEnable();
    TexCoordArrayDisable();
    glVertexPointer(3, MUSHGL_VALTYPE, 0, inVertices);
    glNormalPointer(MUSHGL_VALTYPE, 0, inNormals);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, inSize);
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
