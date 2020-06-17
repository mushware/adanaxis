//%includeGuardStart {
#ifndef GLARRAY_H
#define GLARRAY_H
//%includeGuardStart } jyHURu4ObwdSMbEdI7GvcA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLArray.h
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
//%Header } dVS15ALTw+du6DwgjRdbpA
/*
 * $Id: GLArray.h,v 1.13 2006/06/01 15:38:50 southa Exp $
 * $Log: GLArray.h,v $
 * Revision 1.13  2006/06/01 15:38:50  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/05/19 13:01:58  southa
 * Mac release work
 *
 * Revision 1.11  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.10  2004/01/02 21:13:04  southa
 * Source conditioning
 *
 * Revision 1.9  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:18  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/12 17:32:49  southa
 * Mushcore work
 *
 * Revision 1.6  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.5  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.3  2002/10/12 17:34:20  southa
 * Wall edges
 *
 * Revision 1.2  2002/10/12 15:24:58  southa
 * Facet renderer
 *
 * Revision 1.1  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
 */

#include "GLVector.h"
#include "mushMushcore.h"

template<class tSrc, class tDest>
class GLArray
{
public:
    GLArray(): m_pArray(NULL) {}
    GLArray(const GLArray& inArray); // Copy constructor
    ~GLArray() { if (m_pArray != NULL) delete[] m_pArray; }

    void Push(const tSrc& inValue) { m_vector.push_back(inValue); }
    void Build(void);
    const tDest *ArrayGet(void) const { MUSHCOREASSERT(m_pArray != NULL); return m_pArray; }
    Mushware::U32 SizeGet(void) const { return m_vector.size(); }
    
private:
    std::vector<tSrc> m_vector;
    tDest *m_pArray;
};

template<class tSrc, class tDest>
GLArray<tSrc, tDest>::GLArray(const GLArray& inArray) :
    m_vector(inArray.m_vector),
    m_pArray(NULL)
{
    if (inArray.m_pArray != NULL)
    {
        throw(MushcoreLogicFail("Cannot copy GLArray once built"));
    }
}

template<class tSrc, class tDest>
inline void
GLArray<tSrc, tDest>::Build(void)
{
    Mushware::U32 size=m_vector.size();
    if (m_pArray != NULL) delete[] m_pArray;
    m_pArray = new tDest[size];
    for (Mushware::U32 i=0; i<size; ++i)
    {
         m_vector[i].ConvertTo(m_pArray[i]);
    }
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
