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
 * $Id: MushMeshConnector.cpp,v 1.1 2003/10/19 12:41:42 southa Exp $
 * $Log: MushMeshConnector.cpp,v $
 * Revision 1.1  2003/10/19 12:41:42  southa
 * Connectors
 *
 */

#include "MushMeshConnector.h"

MushMeshConnector::MushMeshConnector()
{
}

MushMeshConnector::MushMeshConnector(MushMeshPatch& ioPatch0, MushMeshPatch::tEdgeSelector inEdge0,
                                     MushMeshPatch& ioPatch1, MushMeshPatch::tEdgeSelector inEdge1) :
    m_targets(2)
{
    m_targets[0].pPatch = &ioPatch0;
    m_targets[0].edgeSelector = inEdge0;
    m_targets[0].modCounter = 0;
    m_targets[1].pPatch = &ioPatch1;
    m_targets[1].edgeSelector = inEdge1;
    m_targets[1].modCounter = 0;
}
