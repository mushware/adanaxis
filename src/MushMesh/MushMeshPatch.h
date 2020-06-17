//%includeGuardStart {
#ifndef MUSHMESHPATCH_H
#define MUSHMESHPATCH_H
//%includeGuardStart } WBwzTC4+Y/UtxsqEMY/TRg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatch.h
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
//%Header } Xtp0EMb6U/tCysIWs/tdGg

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
