//%includeGuardStart {
#ifndef TESSERACTTRAINERPLANESET_H
#define TESSERACTTRAINERPLANESET_H
//%includeGuardStart } +S8nBejwfCKHVd+jl6DCFA
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerPlaneSet.h
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
//%Header } 4nXvb2SB/uUh7QFPcfF3zA
/*
 * $Id: TesseractTrainerPlaneSet.h,v 1.1 2005/02/26 17:53:50 southa Exp $
 * $Log: TesseractTrainerPlaneSet.h,v $
 * Revision 1.1  2005/02/26 17:53:50  southa
 * Plane sets and pairs
 *
 */

#include "TesseractTrainerStandard.h"

#include "mushMushGL.h"
#include "mushMushMesh.h"

class TesseractTrainerPlaneSet
{
public:
    typedef Mushware::t4Val tVertex;
    typedef Mushware::t2Val tTexCoord;
    typedef MushMeshGroup tFacetGroup;
    
    TesseractTrainerPlaneSet() {}
    void Create(Mushware::tVal frame, const std::vector<Mushware::t4GLVal>& inColours);
    void Render(Mushware::tVal frame);
    void OrientationSet(const Mushware::tQValPair& inOrient) { m_orientation = inOrient; }
    
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
