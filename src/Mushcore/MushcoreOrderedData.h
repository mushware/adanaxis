//%includeGuardStart {
#ifndef MUSHCOREORDEREDDATA_H
#define MUSHCOREORDEREDDATA_H
//%includeGuardStart } GgzjlIubd5y7x6M385laCw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreOrderedData.h
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
//%Header } Nca7ypJt/nlvaIKyA57iYA
/*
 * $Id: MushcoreOrderedData.h,v 1.2 2006/06/01 15:39:46 southa Exp $
 * $Log: MushcoreOrderedData.h,v $
 * Revision 1.2  2006/06/01 15:39:46  southa
 * DrawArray verification and fixes
 *
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
