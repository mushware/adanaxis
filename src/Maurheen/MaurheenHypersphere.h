//%includeGuardStart {
#ifndef MAURHEENHYPERSPHERE_H
#define MAURHEENHYPERSPHERE_H
//%includeGuardStart } qUVaaJM6O/D2oxciTypL4A
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenHypersphere.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } HSvTrskFzA7tL4+8tAx4FQ
/*
 * $Id: MaurheenHypersphere.h,v 1.4 2005/05/19 13:02:07 southa Exp $
 * $Log: MaurheenHypersphere.h,v $
 * Revision 1.4  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/01 13:40:37  southa
 * Rotating spheres and hypercube
 *
 * Revision 1.2  2005/01/29 14:06:12  southa
 * OpenGL buffers and extensions
 *
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
        kNumVertices = 30000
    };
    std::vector<tVertex> m_vertices;
    MushGLVertexBuffer<Mushware::t3GLVal> m_vertexBuffer;
    MushGLVertexBuffer<Mushware::t4GLVal> m_colourBuffer;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
