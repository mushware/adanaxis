//%includeGuardStart {
#ifndef MUSHCOREMAPTORREF_H
#define MUSHCOREMAPTORREF_H
//%includeGuardStart } JE2qNwXEbB71mTuGGE11LA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreMaptorRef.h
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
//%Header } fy9+wuXNjO6Rc2nH6LSdsg
/*
 * $Id: MushcoreMaptorRef.h,v 1.5 2006/10/02 17:25:06 southa Exp $
 * $Log: MushcoreMaptorRef.h,v $
 * Revision 1.5  2006/10/02 17:25:06  southa
 * Object lookup and target selection
 *
 * Revision 1.4  2006/06/21 12:17:59  southa
 * Ruby object generation
 *
 * Revision 1.3  2006/06/20 19:06:55  southa
 * Object creation
 *
 * Revision 1.2  2006/05/11 10:43:18  southa
 * Project updates
 *
 * Revision 1.1  2005/07/29 14:59:50  southa
 * Maptor access
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreFail.h"
#include "MushcoreMaptor.h"
#include "MushcoreUtil.h"
#include "MushcoreXMLIStream.h"
#include "MushcoreXMLOStream.h"

//:generate nonvirtual inline ostream
template<class T, class K = Mushware::U32, class C = MushcoreMaptor<T, K> >
class MushcoreMaptorRef
{
public:
    MushcoreMaptorRef() :
        m_pContainer(NULL),
        m_sequenceNum(0),
        m_ptr(NULL)
    {}
    explicit MushcoreMaptorRef(C& inContainer, const K& inKey = K()) :
        m_key(inKey),
        m_pContainer(&inContainer),
        m_sequenceNum(0),
        m_ptr(NULL)
    {}
    
    T& operator*() const { return *Dereference(); }
    T *operator->() const { return Dereference(); }

	void MaptorSet(C& inMaptor) { m_pContainer = &inMaptor; }
	T *GetOrCreate(void) const;
    const T& Ref(void) const { return *Dereference(); }
    T& WRef(void) const { return *Dereference(); }

protected:
    T *Dereference(void) const;

private:
    K m_key; //:readwrite
    C *m_pContainer;
    mutable K m_sequenceNum;
    mutable T *m_ptr;
    
//%classPrototypes {
public:
    const K& Key(void) const { return m_key; }
    void KeySet(const K& inValue) { m_key=inValue; }
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } oT5CcgdwKy07OfZ37Sh+8Q
};

template<class T, class K, class C>
inline T *
MushcoreMaptorRef<T, K, C>::Dereference(void) const
{
    if (dynamic_cast<C *>(m_pContainer) == NULL)
    {
        if (m_pContainer == NULL)
        {
            throw MushcoreDataFail("Cannot dereference MaptorRef whilst container is NULL");
        }
        throw MushcoreLogicFail("Container for MaptorRef deleted or wrong type");
    }
    if (m_ptr == NULL || m_sequenceNum != m_pContainer->SequenceNum())
    {
        m_ptr = &m_pContainer->Get(m_key);
        m_sequenceNum = m_pContainer->SequenceNum();
    }
    return m_ptr;
}

template<class T, class K, class C>
inline T *
MushcoreMaptorRef<T, K, C>::GetOrCreate(void) const
{
	if (dynamic_cast<C *>(m_pContainer) == NULL)
    {
        if (m_pContainer == NULL)
        {
            throw MushcoreDataFail("Cannot dereference MaptorRef whilst container is NULL");
        }
        throw MushcoreLogicFail("Container for MaptorRef deleted or wrong type");
    }
    if (m_ptr == NULL || m_sequenceNum != m_pContainer->SequenceNum())
    {
        m_ptr = &m_pContainer->GetOrCreate(m_key);
        m_sequenceNum = m_pContainer->SequenceNum();
    }
    return m_ptr;
}	

// XML operators treat this object as a single string
template<class T, class K, class C>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushcoreMaptorRef<T, K, C>& inObj)
{
    ioOut << inObj.Key();
    return ioOut;
}

template<class T, class K, class C>
inline void
operator>>(MushcoreXMLIStream& ioIn, MushcoreMaptorRef<T, K, C>& outObj)
{
    K keyValue;
    ioIn >> keyValue;
    outObj.KeySet(keyValue);
}

//%inlineHeader {
template<class T, class K, class C>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushcoreMaptorRef<T, K, C>& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
template<class T, class K, class C>
inline void
MushcoreMaptorRef<T, K, C>::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "key=" << m_key << ", ";
    if (m_pContainer == NULL)
    {
        ioOut << "pContainer=NULL"  << ", ";
    }
    else
    {
        ioOut << "pContainer=" << *m_pContainer << ", ";
    }
    ioOut << "sequenceNum=" << m_sequenceNum << ", ";
    if (m_ptr == NULL)
    {
        ioOut << "ptr=NULL" ;
    }
    else
    {
        ioOut << "ptr=" << *m_ptr;
    }
    ioOut << "]";
}
//%inlineHeader } 7tFZ/RMJ6tQPebrrCvxPWw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
