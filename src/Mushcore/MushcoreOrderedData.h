//%includeGuardStart {
#ifndef MUSHCOREORDEREDDATA_H
#define MUSHCOREORDEREDDATA_H
//%includeGuardStart } GgzjlIubd5y7x6M385laCw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreOrderedData.h
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
//%Header } zwo3y3/muk7TnIAOxfnhAg
/*
 * $Id: MushcoreOrderedData.h,v 1.1 2005/06/13 14:25:46 southa Exp $
 * $Log: MushcoreOrderedData.h,v $
 * Revision 1.1  2005/06/13 14:25:46  southa
 * Pipe and ordered data work
 *
 */

#include "MushcoreData.h"

#define MUSHCORE_ORDERED_DATA_INSTANCE(RefType) MUSHCORE_SINGLETON_INSTANCE(MushcoreOrderedData< RefType >)
#define MUSHCORE_DESTROY_ORDERED_DATA_INSTANCE(RefType) MUSHCORE_DESTROY_SINGLETON_INSTANCE(MushcoreOrderedData< RefType >)

#define MUSHCORE_KEYED_ORDERED_DATA_INSTANCE(RefType, KeyType) MUSHCORE_SINGLETON_INSTANCE2(MushcoreOrderedData< RefType, KeyType >)
#define MUSHCORE_DESTROY_KEYED_ORDERED_DATA_INSTANCE(RefType, KeyType) MUSHCORE_DESTROY_SINGLETON_INSTANCE((MushcoreOrderedData< RefType, KeyType >))

template<class RefType, class KeyType = std::string>
class MushcoreOrderedData : public MushcoreData<RefType, KeyType>
{
public:
    inline MushcoreOrderedData();
    inline ~MushcoreOrderedData();
};

template<class RefType, class KeyType>
MushcoreOrderedData<RefType, KeyType>::MushcoreOrderedData(void) :
    MushcoreData<RefType, KeyType>()
{
}

template<class RefType, class KeyType>
MushcoreOrderedData<RefType, KeyType>::~MushcoreOrderedData(void)
{
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
