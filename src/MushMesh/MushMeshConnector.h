//%includeGuardStart {
#ifndef MUSHMESHCONNECTOR_H
#define MUSHMESHCONNECTOR_H
//%includeGuardStart } F4pS4VW4Ro6fi3sDJdy+0Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshConnector.h
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
//%Header } aUx6gQzsqQlNyLUakJfp2g
/*
 * $Id: MushMeshConnector.h,v 1.7 2006/06/01 15:39:29 southa Exp $
 * $Log: MushMeshConnector.h,v $
 * Revision 1.7  2006/06/01 15:39:29  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:10  southa
 * Mac release work
 *
 * Revision 1.5  2004/09/26 19:42:05  southa
 * Added MushMesh, fixed typenames and release target
 *
 * Revision 1.4  2004/01/02 21:13:10  southa
 * Source conditioning
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

#include "MushMeshStandard.h"

#include "MushMeshPatch.h"
#include "MushMeshStitchable.h"

class MushMeshConnector
{
public:
    MushMeshConnector();
    MushMeshConnector(MushMeshPatch& ioPatch0, MushMeshPatch::tEdgeSelector inEdge0,
        MushMeshPatch& ioPatch1, MushMeshPatch::tEdgeSelector inEdge1);

    void StitchingUpdate(void);
    void TargetsUpdate(void);

private:
    struct tTarget
    {
        MushMeshPatch *pPatch;
        MushMeshPatch::tEdgeSelector edgeSelector;
        Mushware::U32 modCount;
        Mushware::U32 moveCount;
        MushMeshStitchable stitchable;
    };
    std::vector<tTarget> m_targets;
    // Not yet: std::vector<MushMeshTransform> m_transform;    
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
