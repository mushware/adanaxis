//%includeGuardStart {
#ifndef TESSERACTTRAINERHYPERCUBE_H
#define TESSERACTTRAINERHYPERCUBE_H
//%includeGuardStart } N2+eFZbi2SVio7k4AGYf3Q
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerHypercube.h
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
//%Header } qgZaxyORMR85/C5rhgo4kQ
/*
 * $Id: TesseractTrainerHypercube.h,v 1.6 2006/06/01 15:39:59 southa Exp $
 * $Log: TesseractTrainerHypercube.h,v $
 * Revision 1.6  2006/06/01 15:39:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.4  2005/03/13 00:34:48  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.3  2005/02/26 17:53:46  southa
 * Plane sets and pairs
 *
 * Revision 1.2  2005/02/13 22:44:08  southa
 * Tesseract stuff
 *
 * Revision 1.1  2005/02/03 15:46:58  southa
 * Quaternion work
 *
 */

#include "TesseractTrainerStandard.h"

#include "mushMushGL.h"
#include "mushMushMesh.h"

//:generate
class TesseractTrainerHypercube
{
public:
    typedef Mushware::t4Val tVertex;
    typedef Mushware::t2Val tTexCoord;
    typedef MushMeshGroup tFacetGroup;
    
    TesseractTrainerHypercube() {}
    void Create(Mushware::tVal frame, const std::vector<Mushware::t4GLVal>& inColours);
    void Render(Mushware::tVal frame);
    void OrientationSet(const Mushware::tQValPair& inOrient) { m_orientation = inOrient; }
    
private:
    std::vector<tVertex> m_vertices;
    std::vector<Mushware::t4GLVal> m_colours;
    std::vector<tTexCoord> m_texCoords;
    MushcoreDataRef<GLTexture> m_textureRef;
    tFacetGroup m_facetGroup;
    Mushware::tQValPair m_orientation;
    Mushware::U32 m_renderFaces; //:readwrite
    bool m_renderFaceOutlines; //:readwrite
    bool m_renderFaceTextures; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& RenderFaces(void) const { return m_renderFaces; }
    void RenderFacesSet(const Mushware::U32& inValue) { m_renderFaces=inValue; }
    const bool& RenderFaceOutlines(void) const { return m_renderFaceOutlines; }
    void RenderFaceOutlinesSet(const bool& inValue) { m_renderFaceOutlines=inValue; }
    const bool& RenderFaceTextures(void) const { return m_renderFaceTextures; }
    void RenderFaceTexturesSet(const bool& inValue) { m_renderFaceTextures=inValue; }
//%classPrototypes } F2TMclDxJ+51bLL6iBr8iQ
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
