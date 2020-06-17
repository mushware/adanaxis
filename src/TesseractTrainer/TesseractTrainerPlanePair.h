//%includeGuardStart {
#ifndef TESSERACTTRAINERPLANEPAIR_H
#define TESSERACTTRAINERPLANEPAIR_H
//%includeGuardStart } HGeJDDQ9/phPj1jbzqeezg
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerPlanePair.h
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
//%Header } 4qn2gZ8/tVyLqIqxN003zQ
/*
 * $Id: TesseractTrainerPlanePair.h,v 1.3 2006/06/01 15:40:00 southa Exp $
 * $Log: TesseractTrainerPlanePair.h,v $
 * Revision 1.3  2006/06/01 15:40:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/26 17:53:48  southa
 * Plane sets and pairs
 *
 */

#include "TesseractTrainerStandard.h"

#include "mushMushGL.h"
#include "mushMushMesh.h"

class TesseractTrainerPlanePair
{
public:
    typedef Mushware::t4Val tVertex;
    typedef Mushware::t2Val tTexCoord;
    typedef MushMeshGroup tFacetGroup;
    
    TesseractTrainerPlanePair() {}
    void Create(Mushware::tVal frame, const std::vector<Mushware::t4GLVal>& inColours);
    void Render(Mushware::tVal frame);
    void OrientationSet(const Mushware::tQValPair& inOrient) { m_orientation = inOrient; }
    void Rotate(const Mushware::tQValPair& inRotation);
    
private:
    std::vector<tVertex> m_vertices;
    std::vector<Mushware::t4GLVal> m_colours;
    std::vector<tTexCoord> m_texCoords;
    GLTextureRef m_textureRef;
    tFacetGroup m_facetGroup;
    Mushware::tQValPair m_orientation;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
