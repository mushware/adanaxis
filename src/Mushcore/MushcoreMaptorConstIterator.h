//%includeGuardStart {
#ifndef MUSHCOREMAPTORCONSTITERATOR_H
#define MUSHCOREMAPTORCONSTITERATOR_H
//%includeGuardStart } ey8osJ0xmBmS1XM9sP8Uwg
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreMaptorConstIterator.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } Hkd44fiSNTyapd6cYLTkew
/*
 * $Id$
 * $Log$
 */

#include "MushcoreStandard.h"

#include "MushcoreFail.h"

//:generate
template<class T, class K = Mushware::U32, class C = std::map<K, T *> >
class MushcoreMaptorConstIterator
{
public:
    typedef MushcoreMaptorConstIterator tThis;
    
    MushcoreMaptorConstIterator(const typename C::const_iterator& inIter) : m_mapIter(inIter) {}
    MushcoreMaptorConstIterator(const typename C::iterator& inIter) : m_mapIter(inIter) {}
    
    T& operator*() const { return *(m_mapIter->second); }
    T *operator->() const { return m_mapIter->second; }
    
    tThis& operator=(const typename C::const_iterator& inIter) { m_mapIter = inIter; return *this; }
    tThis& operator=(const typename C::iterator& inIter) { m_mapIter = inIter; return *this; }
    tThis& operator++() { ++m_mapIter; return *this; } // prefix
    tThis operator++(int) { tThis retVal(*this); ++m_mapIter; return retVal; } // postfix
    tThis& operator--() { --m_mapIter; return *this; } // prefix
    tThis operator--(int) { tThis retVal(*this); --m_mapIter; return retVal; } // postfix
    
    bool EqualIs(const tThis& inObj) const { return (m_mapIter == inObj.m_mapIter); }
    
private:
    typename C::const_iterator m_mapIter; //:read
//%classPrototypes {
public:
    const typename C::const_iterator& MapIter(void) const { return m_mapIter; }
//%classPrototypes } itWhOnpnVAI20G7mFpSYVQ
};

template<class T, class K, class C>
inline bool
operator!=(const MushcoreMaptorConstIterator<T, K, C>& inA, const MushcoreMaptorConstIterator<T, K, C>& inB)
{
    return !inA.EqualIs(inB);
}

template<class T, class K, class C>
inline bool
operator==(const MushcoreMaptorConstIterator<T, K, C>& inA, const MushcoreMaptorConstIterator<T, K, C>& inB)
{
    return inA.EqualIs(inB);
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
