//%includeGuardStart {
#ifndef MAURHEENHYPERCUBE_H
#define MAURHEENHYPERCUBE_H
//%includeGuardStart } b6sC03eXI4CBCNiLtDRVIg
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenHypercube.h
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
//%Header } 1R1TMKrSQWzrtOjntkl+zA
/*
 * $Id: MaurheenHypercube.h,v 1.5 2006/06/01 15:39:12 southa Exp $
 * $Log: MaurheenHypercube.h,v $
 * Revision 1.5  2006/06/01 15:39:12  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.3  2005/01/27 21:00:39  southa
 * Division and rendering
 *
 * Revision 1.2  2005/01/26 00:48:46  southa
 * MushMeshGroup and rendering
 *
 * Revision 1.1  2004/10/31 23:34:06  southa
 * Hypercube rendering test
 *
 */

#include "MaurheenStandard.h"

#include "mushMushGL.h"
#include "mushMushMesh.h"

class MaurheenHypercube
{
public:
    typedef Mushware::t4Val tVertex;
    typedef MushMeshGroup tFacetGroup;
    
    MaurheenHypercube() {}
    void Create(Mushware::tVal frame);
    void Render(Mushware::tVal frame);
    
private:
    std::vector<tVertex> m_vertices;
    tFacetGroup m_facetGroup;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
