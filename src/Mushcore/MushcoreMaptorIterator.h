//%includeGuardStart {
#ifndef MUSHCOREMAPTORITERATOR_H
#define MUSHCOREMAPTORITERATOR_H
//%includeGuardStart } 7/8SICrVNYFpeJqHW/R8kA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreMaptorIterator.h
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
//%Header } Ms6nZjXPOopQSUVFHeLa5w
/*
 * $Id: MushcoreMaptorIterator.h,v 1.2 2005/08/01 13:09:58 southa Exp $
 * $Log: MushcoreMaptorIterator.h,v $
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
