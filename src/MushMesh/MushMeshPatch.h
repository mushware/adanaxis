//%includeGuardStart {
#ifndef MUSHMESHPATCH_H
#define MUSHMESHPATCH_H
//%includeGuardStart } WBwzTC4+Y/UtxsqEMY/TRg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatch.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } zGWLmg7tcsv3Aqgc/Cqz/A

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
