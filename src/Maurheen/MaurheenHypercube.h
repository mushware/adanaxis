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
 * $Id: MaurheenWorm.h,v 1.2 2004/03/07 20:33:54 southa Exp $
 * $Log: MaurheenWorm.h,v $
 */

#include "MaurheenStandard.h"

#include "mushMushGL.h"

class MaurheenHypercube
{
public:
    MaurheenHypercube() {}
    void Create(Mushware::tVal frame);
    void Render(Mushware::tVal frame);
    
private:
    std::vector<Mushware::t4GLVal> m_vertices;
    std::vector<Mushware::t4U32> m_definition;
    std::vector<Mushware::t3GLVal> m_normals;
    std::vector<Mushware::t2GLVal> m_texCoords;
    Mushware::U32 m_length;
    Mushware::U32 m_order;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
