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
 * $Id: MaurheenHypersphere.h,v 1.1 2005/01/27 21:00:39 southa Exp $
 * $Log: MaurheenHypersphere.h,v $
 * Revision 1.1  2005/01/27 21:00:39  southa
 * Division and rendering
 *
 */

#include "MaurheenStandard.h"

#include "mushMushGL.h"
#include "mushMushMesh.h"

class MaurheenHypersphere
{
public:
    typedef Mushware::t4Val tVertex;
    typedef MushMeshGroup tFacetGroup;
    
    MaurheenHypersphere();
    void Create(Mushware::tVal frame);
    void Render(Mushware::tVal frame);
    
private:
    enum
    {
        kNumVertices = 100000
    };
    std::vector<tVertex> m_vertices;
    MushGLBuffer<Mushware::t3GLVal> m_vertexBuffer;
    MushGLBuffer<Mushware::t4GLVal> m_colourBuffer;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
