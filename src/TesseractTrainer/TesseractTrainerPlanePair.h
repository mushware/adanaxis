//%includeGuardStart {
#ifndef TESSERACTTRAINERPLANEPAIR_H
#define TESSERACTTRAINERPLANEPAIR_H
//%includeGuardStart } HGeJDDQ9/phPj1jbzqeezg
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerPlanePair.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } mFb1UyK87fUcL2FimdU9hg
/*
 * $Id: TesseractTrainerPlanePair.h,v 1.2 2005/02/13 22:44:08 southa Exp $
 * $Log: TesseractTrainerPlanePair.h,v $
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
