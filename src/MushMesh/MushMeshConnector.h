//%includeGuardStart {
#ifndef MUSHMESHCONNECTOR_H
#define MUSHMESHCONNECTOR_H
//%includeGuardStart } F4pS4VW4Ro6fi3sDJdy+0Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshConnector.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } rkr6AHzeP46l9zTid8JO0g
/*
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"

#include "MushMeshPatch.h"
#include "MushMeshStitchable.h"

class MushMeshConnector
{
public:
    enum tEdgeSelector
    {
        kEdgeLeft,
        kEdgeRight,
        kEdgeBottom,
        kEdgeTop,
        kPointBottomLeft,
        kPointBottomRight,
        kPointTopLeft,
        kPointTopRight
    };
    MushMeshConnector();
    MushMeshConnector(MushMeshPatch& ioPatch1, tEdgeSelector inEdge1, MushMeshPatch& ioPatch1, tEdgeSelector inEdge1);
    
private:
    struct tTarget
    {
        MushMeshPatch *pPatch;
        tEdgeSelector edgeSelector;
        Mushware::U32 modCounter;
        MushMeshStitchable stitchable;
    };
    std::vector<tTarget> m_targets;
    // Not yet: std::vector<MushMeshTransform> m_transform;    
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
