//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshConnector.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } EpwjGbLj/pwQ7yhTL0oI3w
/*
 * $Id: MushMeshConnector.cpp,v 1.3 2003/10/20 13:02:53 southa Exp $
 * $Log: MushMeshConnector.cpp,v $
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
