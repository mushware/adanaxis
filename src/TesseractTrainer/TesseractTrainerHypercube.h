//%includeGuardStart {
#ifndef TESSERACTTRAINERHYPERCUBE_H
#define TESSERACTTRAINERHYPERCUBE_H
//%includeGuardStart } N2+eFZbi2SVio7k4AGYf3Q
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerHypercube.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } iZEF1yPrVbDw+vHpY5jCpw
/*
 * $Id: TesseractTrainerHypercube.h,v 1.1 2005/02/03 15:46:58 southa Exp $
 * $Log: TesseractTrainerHypercube.h,v $
 * Revision 1.1  2005/02/03 15:46:58  southa
 * Quaternion work
 *
 */

#include "TesseractTrainerStandard.h"

#include "mushMushGL.h"
#include "mushMushMesh.h"

class TesseractTrainerHypercube
{
public:
    typedef Mushware::t4Val tVertex;
    typedef Mushware::t2Val tTexCoord;
    typedef MushMeshGroup tFacetGroup;
    
    TesseractTrainerHypercube() {}
    void Create(Mushware::tVal frame, const std::vector<Mushware::t4GLVal>& inColours);
    void Render(Mushware::tVal frame);
    
private:
    std::vector<tVertex> m_vertices;
    std::vector<Mushware::t4GLVal> m_colours;
    std::vector<tTexCoord> m_texCoords;
    MushcoreDataRef<GLTexture> m_textureRef;
    tFacetGroup m_facetGroup;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
