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
 * $Id$
 * $Log$
 */

#include "TesseractTrainerStandard.h"

#include "mushMushGL.h"
#include "mushMushMesh.h"

class TesseractTrainerHypersphere
{
public:
    typedef Mushware::t4Val tVertex;
    typedef MushMeshGroup tFacetGroup;
    
    TesseractTrainerHypersphere();
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
