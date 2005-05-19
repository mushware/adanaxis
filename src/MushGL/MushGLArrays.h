//%includeGuardStart {
#ifndef MUSHGLARRAYS_H
#define MUSHGLARRAYS_H
//%includeGuardStart } g2PetpgsUQpgHIBi+HMQeg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLArrays.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } jBYHjtYO6uDJ7iQ/m7qDDw

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
