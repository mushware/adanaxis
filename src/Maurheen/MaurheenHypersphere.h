//%includeGuardStart {
#ifndef MAURHEENHYPERSPHERE_H
#define MAURHEENHYPERSPHERE_H
//%includeGuardStart } qUVaaJM6O/D2oxciTypL4A
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenHypersphere.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } slFPFhapfdncvvpyGmZQIQ
/*
 * $Id: MaurheenHypersphere.h,v 1.2 2005/01/26 00:48:46 southa Exp $
 * $Log: MaurheenHypersphere.h,v $
 */

#include "MaurheenStandard.h"

#include "mushMushGL.h"
#include "mushMushMesh.h"

class MaurheenHypersphere
{
public:
    typedef Mushware::t4Val tVertex;
    typedef MushMeshGroup tFacetGroup;
    
    MaurheenHypersphere() {}
    void Create(Mushware::tVal frame);
    void Render(Mushware::tVal frame);
    
private:
    std::vector<tVertex> m_vertices;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
