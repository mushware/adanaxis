//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshUtils.cpp
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
//%Header } Oii056D7WrKz2v3NohYOZg
/*
 * $Id: MushMeshUtils.cpp,v 1.12 2006/06/01 15:39:33 southa Exp $
 * $Log: MushMeshUtils.cpp,v $
 * Revision 1.12  2006/06/01 15:39:33  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.10  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.9  2005/02/10 12:34:07  southa
 * Template fixes
 *
 * Revision 1.8  2005/01/27 21:00:39  southa
 * Division and rendering
 *
 * Revision 1.7  2004/12/13 11:09:11  southa
 * Quaternion and vector tweaks
 *
 * Revision 1.6  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.5  2003/10/24 12:39:09  southa
 * Triangular mesh work
 *
 * Revision 1.4  2003/10/23 20:03:58  southa
 * End mesh work
 *
 * Revision 1.3  2003/10/15 12:26:59  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.2  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 * Revision 1.1  2003/10/14 13:07:25  southa
 * MushMesh vector creation
 *
 */

#include "MushMeshUtils.h"

#include "MushMeshBox.h"
#include "MushMeshGroup.h"
#include "MushMeshSTL.h"

using namespace Mushware;
using namespace std;

const tVal MushMeshUtils::m_alphaTable[kMaxValence] =
{
    0,
    3.26667,
    1.28205,
    2.33333,
    4.25806,
    6.89157,
    10,
    13.3978
};

tVal
MushMeshUtils::SubdivisionAlphaCalculate(Mushware::U32 inN)
{
    MUSHCOREASSERT(inN > 0);

    tVal a;
    a = 3.0 + 2.0 * cos((2*M_PI) / inN);
    a = 0.625 - a*a/64.0;

    return inN * (1.0 - a) / a;
}

void
MushMeshUtils::SimpleDivide4Mesh(MushMeshGroup& outGroup, const MushMeshGroup& inGroup, const tVal inScale)
{
    outGroup.OrderResize(2);
    
    for (U32 i=0; i < inGroup.SuperGroupSize(1); ++i)
    {
        
        for (U32 j=0; j < inGroup.GroupSize(1, i); ++j)
        {
            MushMeshGroup::tValue value;
            
            value = inGroup.Value(1, i, j);
            
            outGroup.ValueAdd(value, 1, i, j);
        }
    }
    
    for (U32 i=0; i < inGroup.SuperGroupSize(0); ++i)
    {
        for (U32 j=0; j < inGroup.GroupSize(0, i); ++j)
        {
            MushMeshGroup::tValue value;
            
            value = inGroup.Value(0, i, j);
            
            outGroup.ValueAdd(value, 0, i, j);
        }
    }
    
}

