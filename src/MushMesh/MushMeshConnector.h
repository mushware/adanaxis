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
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } cZY3DRAbHGzPb8Rixe5igw
/*
 * $Id: MushMeshConnector.h,v 1.3 2003/10/20 13:02:53 southa Exp $
 * $Log: MushMeshConnector.h,v $
 * Revision 1.3  2003/10/20 13:02:53  southa
 * Patch fixes and testing
 *
 * Revision 1.2  2003/10/19 15:59:33  southa
 * Edge manipulation
 *
 * Revision 1.1  2003/10/19 12:41:42  southa
 * Connectors
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshPatch.h"
#include "MushMeshStitchable.h"

class MushMeshConnector
{
public:
    MushMeshConnector();
    MushMeshConnector(MushMeshPatch& ioPatch1, MushMeshPatch::tEdgeSelector inEdge1,
        MushMeshPatch& ioPatch1, MushMeshPatch::tEdgeSelector inEdge1);

    void StitchingUpdate(void);
    void TargetsUpdate(void);

private:
    struct tTarget
    {
        MushMeshPatch *pPatch;
        MushMeshPatch::tEdgeSelector edgeSelector;
        Mushware::U32 modCount;
        Mushware::U32 moveCount;
        MushMeshStitchable stitchable;
    };
    std::vector<tTarget> m_targets;
    // Not yet: std::vector<MushMeshTransform> m_transform;    
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
