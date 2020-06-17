//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshConnector.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 3hwcvGhtLd2ID9tyytkeNw
/*
 * $Id: MushMeshConnector.cpp,v 1.7 2006/06/01 15:39:29 southa Exp $
 * $Log: MushMeshConnector.cpp,v $
 * Revision 1.7  2006/06/01 15:39:29  southa
 * DrawArray verification and fixes
 *
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
