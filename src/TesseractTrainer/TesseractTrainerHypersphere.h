//%includeGuardStart {
#ifndef TESSERACTTRAINERHYPERSPHERE_H
#define TESSERACTTRAINERHYPERSPHERE_H
//%includeGuardStart } eaEYE21yvxZXOtvQ0J8TYA
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerHypersphere.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } Ifi/A6BA4J5vvDdnjvtr3Q
/*
 * $Id: TesseractTrainerHypersphere.h,v 1.6 2006/06/01 15:39:59 southa Exp $
 * $Log: TesseractTrainerHypersphere.h,v $
 * Revision 1.6  2006/06/01 15:39:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.4  2005/03/13 00:34:48  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.3  2005/02/26 17:53:47  southa
 * Plane sets and pairs
 *
 * Revision 1.2  2005/02/13 22:44:08  southa
 * Tesseract stuff
 *
 * Revision 1.1  2005/02/03 15:46:59  southa
 * Quaternion work
 *
 */

#include "TesseractTrainerStandard.h"

#include "mushMushGL.h"
#include "mushMushMesh.h"

//:generate
class TesseractTrainerHypersphere
{
public:
    typedef Mushware::t4Val tVertex;
    typedef MushMeshGroup tFacetGroup;
    
    TesseractTrainerHypersphere();
    void Create(Mushware::tVal frame, const std::vector<Mushware::t4GLVal>& inColours);
    void Render(Mushware::tVal frame);
    void OrientationSet(const Mushware::tQValPair& inOrient) { m_orientation = inOrient; }
    
private:
    std::vector<tVertex> m_vertices;
    Mushware::U32 m_numVertices;
    
    MushGLVertexBuffer<Mushware::t3GLVal> m_vertexBuffer;
    MushGLVertexBuffer<Mushware::t4GLVal> m_colourBuffer;
    Mushware::tQValPair m_orientation;
    Mushware::U32 m_renderFaces; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& RenderFaces(void) const { return m_renderFaces; }
    void RenderFacesSet(const Mushware::U32& inValue) { m_renderFaces=inValue; }
//%classPrototypes } jBvg2aVYhLSGuBezUhnMaw
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
