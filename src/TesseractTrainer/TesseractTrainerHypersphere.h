//%includeGuardStart {
#ifndef TESSERACTTRAINERHYPERSPHERE_H
#define TESSERACTTRAINERHYPERSPHERE_H
//%includeGuardStart } eaEYE21yvxZXOtvQ0J8TYA
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerHypersphere.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } oFI4VexFfs/tkyGLE4giFw
/*
 * $Id: TesseractTrainerHypersphere.h,v 1.3 2005/02/26 17:53:47 southa Exp $
 * $Log: TesseractTrainerHypersphere.h,v $
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
