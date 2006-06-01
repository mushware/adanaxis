//%includeGuardStart {
#ifndef MUSHMESHPATCH_H
#define MUSHMESHPATCH_H
//%includeGuardStart } WBwzTC4+Y/UtxsqEMY/TRg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatch.h
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
//%Header } WWpt9AIzliVxzw9m9iD36A

#include "MushMeshStandard.h"

class MushMeshStitchable;

class MushMeshPatch
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
        kPointTopRight,
        kNumEdgeSelectors
    };

    MushMeshPatch();
    virtual ~MushMeshPatch() {}
    // virtual void Render(void /* some render context */) = 0;
    virtual void Subdivide(Mushware::tVal inLevel) = 0;
    virtual void EdgeStitchableGet(MushMeshStitchable& outStitchable, tEdgeSelector inEdge) = 0;
    virtual void NeighbourSet(const MushMeshStitchable& inStitchable, tEdgeSelector inEdge) = 0;

    Mushware::U32 ModCountGet(void) { return m_modCount; }
    Mushware::U32 MoveCountGet(void) { return m_moveCount; }
    void Touch(void);

protected:
    void StorageTouch(void);

private:
    Mushware::U32 m_modCount;
    Mushware::U32 m_moveCount;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
