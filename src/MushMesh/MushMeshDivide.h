//%includeGuardStart {
#ifndef MUSHMESHDIVIDE_H
#define MUSHMESHDIVIDE_H
//%includeGuardStart } t4U0jmRZwzEi3M9sk++ONw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshDivide.h
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
//%Header } JEl8u3tSeBwn5gc+6YHOmQ
/*
 * $Id: MushMeshDivide.h,v 1.3 2005/05/19 13:02:10 southa Exp $
 * $Log: MushMeshDivide.h,v $
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
    //std::cout << "inGroup= " << inGroup << endl;
    //std::cout << "outGroup= " << outGroup << endl;
    //throw "die";
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
