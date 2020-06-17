//%includeGuardStart {
#ifndef MUSHRENDERUTIL_H
#define MUSHRENDERUTIL_H
//%includeGuardStart } g/RC6XSRPyl9Augpd+6sCw
//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderUtil.h
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
//%Header } izufKCD0KZ6SR+ywSoLA0w
/*
 * $Id: MushRenderUtil.h,v 1.2 2006/06/01 15:39:39 southa Exp $
 * $Log: MushRenderUtil.h,v $
 * Revision 1.2  2006/06/01 15:39:39  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/04 15:59:01  southa
 * Adanaxis work
 *
 */

#include "MushRenderStandard.h"

class MushRenderUtil
{
public:
    template <class T, Mushware::U32 D> static void Transform(std::vector< MushMeshVector<T, D> >& ioDest, const std::vector< MushMeshVector<T, D> >& inSrc, const MushMeshMattress<T, D>& inTransform);
private:
};

template <class T, Mushware::U32 D>
inline void
MushRenderUtil::Transform(std::vector< MushMeshVector<T, D> >& ioDest, const std::vector< MushMeshVector<T, D> >& inSrc, const MushMeshMattress<T, D>& inTransform)
{
    Mushware::tSize srcSize = inSrc.size();
    if (ioDest.size() < srcSize)
    {
        ioDest.resize(srcSize);
    }
    
    for (Mushware::U32 i=0; i<srcSize; ++i)
    {
        ioDest[i] = inTransform * inSrc[i];
    }
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
