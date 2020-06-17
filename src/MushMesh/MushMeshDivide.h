//%includeGuardStart {
#ifndef MUSHMESHDIVIDE_H
#define MUSHMESHDIVIDE_H
//%includeGuardStart } t4U0jmRZwzEi3M9sk++ONw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshDivide.h
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
//%Header } lvEPmGijQ1XDWyZTR8Yfqg
/*
 * $Id: MushMeshDivide.h,v 1.5 2006/12/14 00:33:50 southa Exp $
 * $Log: MushMeshDivide.h,v $
 * Revision 1.5  2006/12/14 00:33:50  southa
 * Control fix and audio pacing
 *
 * Revision 1.4  2006/06/01 15:39:29  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/05/19 13:02:10  southa
 * Mac release work
 *
 * Revision 1.2  2005/03/30 23:33:57  southa
 * win32 and gcc 2.95 fixes
 *
 * Revision 1.1  2005/01/27 21:00:39  southa
 * Division and rendering
 *
 */

#include "MushMeshStandard.h"
#include "MushMeshMushcoreIO.h"

#include "MushMeshGroup.h"

class MushMeshDivide
{
public:
    template <class V>
    static void
    Divide(std::vector<V>& outVert, MushMeshGroup& outGroup,
           const std::vector<V>& inVert, const MushMeshGroup& inGroup,
           const Mushware::tVal inScale);
};

template <class V>
inline void
MushMeshDivide::Divide(std::vector<V>& outVert, MushMeshGroup& outGroup,
                       const std::vector<V>& inVert, const MushMeshGroup& inGroup,
                       const Mushware::tVal inScale)
{
    outGroup.OrderResize(2);
    
    Mushware::U32 destFace1 = 0;
    Mushware::U32 destFacet1 = 0;
    Mushware::U32 destFacet0 = 0;
    Mushware::U32 destVertex0 = 0;
    Mushware::U32 destVertIndex = 0;
    
    Mushware::tSize vertSize = inVert.size();
    
    outVert.resize(4*vertSize);
    
    for (Mushware::U32 srcFace1=0; srcFace1 < inGroup.SuperGroupSize(1); ++srcFace1)
    {        
        for (Mushware::U32 srcFacet1=0; srcFacet1 < inGroup.GroupSize(1, srcFace1); ++srcFacet1)
        {
            Mushware::U32 srcFacet0 = inGroup.Value(1, srcFace1, srcFacet1);

            for (Mushware::U32 srcVertex0=0; srcVertex0 < inGroup.GroupSize(0, srcFacet0); ++srcVertex0)
            {
                Mushware::U32 srcVertIndex = inGroup.Value(0, srcFacet0, srcVertex0);

                for (Mushware::U32 i=0; i < inGroup.GroupSize(0, srcFacet0); ++i)
                {
                    Mushware::U32 iVertIndex = inGroup.Value(0, srcFacet0, i);

                    MUSHCOREASSERT(srcVertIndex < inVert.size());
                    MUSHCOREASSERT(destVertIndex < outVert.size());
                    
                    // Create vertex
                    outVert[destVertIndex] = (inVert[srcVertIndex] + inVert[iVertIndex])/2;
                    
                    // Add vertex to facet definition
                    outGroup.ValueAdd(destVertIndex, 0, destFacet0, destVertex0);

                    ++destVertIndex;
                    ++destVertex0;
                }
                
                // Add facet to face definition
                outGroup.ValueAdd(destFacet0, 1, destFace1, destFacet1);
                ++destFacet1;
                
                ++destFacet0;
                destVertex0 = 0;
            }
        }
        ++destFace1;
        destFacet1=0;
    }
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
