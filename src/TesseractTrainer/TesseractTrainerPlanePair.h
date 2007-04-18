//%includeGuardStart {
#ifndef TESSERACTTRAINERPLANEPAIR_H
#define TESSERACTTRAINERPLANEPAIR_H
//%includeGuardStart } HGeJDDQ9/phPj1jbzqeezg
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerPlanePair.h
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
//%Header } cuYvRxIHdKagLJx7Q2znbw
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
