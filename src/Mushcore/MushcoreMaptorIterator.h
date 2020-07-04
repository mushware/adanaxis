//%includeGuardStart {
#ifndef MUSHCOREMAPTORITERATOR_H
#define MUSHCOREMAPTORITERATOR_H
//%includeGuardStart } 7/8SICrVNYFpeJqHW/R8kA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreMaptorIterator.h
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
//%Header } P1WFMu4eLFLhgSA3cohw5A
/*
 * $Id: MushcoreMaptorIterator.h,v 1.3 2006/06/01 15:39:45 southa Exp $
 * $Log: MushcoreMaptorIterator.h,v $
 * Revision 1.3  2006/06/01 15:39:45  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 * Revision 1.1  2005/07/29 14:59:50  southa
 * Maptor access
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreFail.h"

//:generate
template<class T, class K = Mushware::U32, class C = std::map<K, T *> >
class MushcoreMaptorIterator
{
public:
    typedef MushcoreMaptorIterator tThis;
    
    MushcoreMaptorIterator(const typename C::iterator& inIter) : m_mapIter(inIter) {}
    
    T& operator*() const { return *(m_mapIter->second); }
    T *operator->() const { return m_mapIter->second; }
    
    tThis& operator=(const typename C::iterator& inIter) { m_mapIter = inIter; return *this; }
    tThis& operator++() { ++m_mapIter; return *this; } // prefix
    tThis operator++(int) { tThis retVal(*this); ++m_mapIter; return retVal; } // postfix
    tThis& operator--() { --m_mapIter; return *this; } // prefix
    tThis operator--(int) { tThis retVal(*this); --m_mapIter; return retVal; } // postfix

    const K& Key(void) const { return m_mapIter->first; }
    bool EqualIs(const tThis& inObj) const { return (m_mapIter == inObj.m_mapIter); }
    
private:
    typename C::iterator m_mapIter; //:read
//%classPrototypes {
public:
    const typename C::iterator& MapIter(void) const { return m_mapIter; }
//%classPrototypes } HwIXcKbX68//YtLDimT7jA
};

template<class T, class K, class C>
inline bool
operator!=(const MushcoreMaptorIterator<T, K, C>& inA, const MushcoreMaptorIterator<T, K, C>& inB)
{
    return !inA.EqualIs(inB);
}

template<class T, class K, class C>
inline bool
operator==(const MushcoreMaptorIterator<T, K, C>& inA, const MushcoreMaptorIterator<T, K, C>& inB)
{
    return inA.EqualIs(inB);
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
