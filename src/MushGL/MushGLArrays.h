//%includeGuardStart {
#ifndef MUSHGLARRAYS_H
#define MUSHGLARRAYS_H
//%includeGuardStart } g2PetpgsUQpgHIBi+HMQeg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLArrays.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 12xtCcB8QKvMZMww/Spdug

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
