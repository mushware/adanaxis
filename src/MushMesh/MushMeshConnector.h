//%includeGuardStart {
#ifndef MUSHMESHCONNECTOR_H
#define MUSHMESHCONNECTOR_H
//%includeGuardStart } F4pS4VW4Ro6fi3sDJdy+0Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshConnector.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } mLh700cmuKegIzs0wQILoQ
/*
 * $Id: MushMeshConnector.h,v 1.5 2004/09/26 19:42:05 southa Exp $
 * $Log: MushMeshConnector.h,v $
 * Revision 1.5  2004/09/26 19:42:05  southa
 * Added MushMesh, fixed typenames and release target
 *
 * Revision 1.4  2004/01/02 21:13:10  southa
 * Source conditioning
 *
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
    MushMeshConnector(MushMeshPatch& ioPatch0, MushMeshPatch::tEdgeSelector inEdge0,
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
