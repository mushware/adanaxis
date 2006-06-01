//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatch.cpp
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
//%Header } 1AKZnDR+IDKqSlk6Rz2mAg

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
