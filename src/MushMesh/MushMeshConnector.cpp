//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshConnector.cpp
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
//%Header } pmICmPgICS81C/nJZDG8jQ
/*
 * $Id: MushMeshConnector.cpp,v 1.6 2005/05/19 13:02:10 southa Exp $
 * $Log: MushMeshConnector.cpp,v $
 * Revision 1.6  2005/05/19 13:02:10  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.4  2003/10/25 18:26:02  southa
 * Patch connection rework
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

#include "MushMeshConnector.h"

using namespace Mushware;
using namespace std;

MushMeshConnector::MushMeshConnector()
{
}

MushMeshConnector::MushMeshConnector(MushMeshPatch& ioPatch0, MushMeshPatch::tEdgeSelector inEdge0,
                                     MushMeshPatch& ioPatch1, MushMeshPatch::tEdgeSelector inEdge1) :
    m_targets(2)
{
    m_targets[0].pPatch = &ioPatch0;
    m_targets[0].edgeSelector = inEdge0;
    m_targets[0].modCount = 0;
    m_targets[0].moveCount = 0;
    m_targets[1].pPatch = &ioPatch1;
    m_targets[1].edgeSelector = inEdge1;
    m_targets[1].modCount = 0;
    m_targets[1].moveCount = 0;
}

void
MushMeshConnector::StitchingUpdate(void)
{
    for (U32 i=0; i<2; ++i)
    {
        m_targets[i].pPatch->EdgeStitchableGet(m_targets[i].stitchable, m_targets[i].edgeSelector);
        m_targets[i].moveCount = m_targets[i].pPatch->MoveCountGet();
    }
}

void
MushMeshConnector::TargetsUpdate(void)
{
    U32 target0ModCount = m_targets[0].pPatch->ModCountGet();
    if (m_targets[0].modCount != target0ModCount)
    {
        if (m_targets[0].moveCount != m_targets[0].pPatch->MoveCountGet())
        {
            StitchingUpdate();
        }

        /* Target 0 has been modified, so copy the edge from target 0 to neighbours
         * on target 1.  Our stored target 0 stitchable contains a complete definition
         * of the edge on target 0
         */
        m_targets[1].pPatch->NeighbourSet(m_targets[0].stitchable, m_targets[1].edgeSelector);   
        m_targets[0].modCount = target0ModCount;
    }

    U32 target1ModCount = m_targets[1].pPatch->ModCountGet();
    if (m_targets[1].modCount != target1ModCount)
    {
        if (m_targets[1].moveCount != m_targets[1].pPatch->MoveCountGet())
        {
            StitchingUpdate();
        }
        m_targets[0].pPatch->NeighbourSet(m_targets[1].stitchable, m_targets[0].edgeSelector);   
        m_targets[1].modCount = target0ModCount;
    }
}
