//%includeGuardStart {
#ifndef MAURHEENHYPERCUBE_H
#define MAURHEENHYPERCUBE_H
//%includeGuardStart } b6sC03eXI4CBCNiLtDRVIg
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenHypercube.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } FU79ttZJMqjIVWpj0CtP6A
/*
 * $Id: MaurheenHypercube.h,v 1.1 2004/10/31 23:34:06 southa Exp $
 * $Log: MaurheenHypercube.h,v $
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
    Mushware::U32 m_length;
    Mushware::U32 m_order;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
