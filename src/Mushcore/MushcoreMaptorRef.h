//%includeGuardStart {
#ifndef MUSHCOREMAPTORREF_H
#define MUSHCOREMAPTORREF_H
//%includeGuardStart } JE2qNwXEbB71mTuGGE11LA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreMaptorRef.h
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
//%Header } oYaclGAzf6mPo2JW/S6SXA
/*
 * $Id: MushcoreMaptorRef.h,v 1.4 2006/06/21 12:17:59 southa Exp $
 * $Log: MushcoreMaptorRef.h,v $
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
