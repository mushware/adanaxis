//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatch.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 69gyh6IcUOuLZhwo2Qx59A

#include "MushMeshPatch.h"

MushMeshPatch::MushMeshPatch() :
    m_modCount(1),
    m_moveCount(0)
{
}

void
MushMeshPatch::Touch(void)
{
    ++m_modCount;
    if (m_modCount == 0)
    {
        m_modCount = 1;
    }
}

void
MushMeshPatch::StorageTouch(void)
{
    ++m_moveCount;
    if (m_moveCount == 0)
    {
        m_moveCount = 1;
    }
}
