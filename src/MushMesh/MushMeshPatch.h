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
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } zOjScA/10RD7ybR0LwcvFw

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
    virtual void EdgeGet(MushMeshStitchable& outStitchable, tEdgeSelector inEdge) = 0;
    virtual void NeighbourSet(const MushMeshStitchable& inStitchable, tEdgeSelector inEdge) = 0;

    Mushware::U32 ModCountGet(void) { return m_modCount; }
    void Touch(void);

private:
    Mushware::U32 m_modCount;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
