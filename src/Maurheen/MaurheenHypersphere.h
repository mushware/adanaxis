//%includeGuardStart {
#ifndef MAURHEENHYPERSPHERE_H
#define MAURHEENHYPERSPHERE_H
//%includeGuardStart } qUVaaJM6O/D2oxciTypL4A
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenHypersphere.h
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
//%Header } lw5kgx7iYFAUijO9vEOl3g
/*
 * $Id: MaurheenHypersphere.h,v 1.5 2006/06/01 15:39:12 southa Exp $
 * $Log: MaurheenHypersphere.h,v $
 * Revision 1.5  2006/06/01 15:39:12  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/01 13:40:37  southa
 * Rotating spheres and hypercube
 *
 * Revision 1.2  2005/01/29 14:06:12  southa
 * OpenGL buffers and extensions
 *
 * Revision 1.1  2005/01/27 21:00:39  southa
 * Division and rendering
 *
 */

#include "MaurheenStandard.h"

#include "mushMushGL.h"
#include "mushMushMesh.h"

class MaurheenHypersphere
{
public:
    typedef Mushware::t4Val tVertex;
    typedef MushMeshGroup tFacetGroup;
    
    MaurheenHypersphere();
    void Create(Mushware::tVal frame);
    void Render(Mushware::tVal frame);
    
private:
    enum
    {
        kNumVertices = 30000
    };
    std::vector<tVertex> m_vertices;
    MushGLVertexBuffer<Mushware::t3GLVal> m_vertexBuffer;
    MushGLVertexBuffer<Mushware::t4GLVal> m_colourBuffer;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
