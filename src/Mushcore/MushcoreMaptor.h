//%includeGuardStart {
#ifndef MUSHCOREMAPTOR_H
#define MUSHCOREMAPTOR_H
//%includeGuardStart } sgC6Fg2ig+cctgMAe9F1mQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreMaptor.h
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
//%Header } ChL6aTElKIc1rPHNw0/j3A
/*
 * $Id: MushcoreMaptor.h,v 1.7 2006/06/21 12:17:59 southa Exp $
 * $Log: MushcoreMaptor.h,v $
 * Revision 1.7  2006/06/21 12:17:59  southa
 * Ruby object generation
 *
 * Revision 1.6  2006/06/20 19:06:55  southa
 * Object creation
 *
 * Revision 1.5  2006/06/01 15:39:45  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 * Revision 1.3  2005/07/29 18:50:12  southa
 * Maptor tweaks
 *
 * Revision 1.2  2005/07/29 14:59:50  southa
 * Maptor access
 *
 * Revision 1.1  2005/07/29 11:53:41  southa
 * MushcoreMaptor created
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreFail.h"
#include "MushcoreMaptorConstIterator.h"
#include "MushcoreMaptorIterator.h"
#include "MushcoreUtil.h"
#include "MushcoreXMLIStream.h"
#include "MushcoreXMLOStream.h"

template<class T, class K, class C> class MushcoreMaptorRef;

//:generate nonvirtual inline ostream
template<class T, class K = Mushware::U32, class C = std::map<K, T *> >
class MushcoreMaptor
{
public:
    typedef T *value_type;
    typedef typename C::size_type size_type;
    typedef typename C::difference_type difference_type;
    typedef C container_type;
    typedef K key_type;
    typedef T *mapped_type;
    typedef typename C::reference reference;
    typedef typename C::const_reference const_reference;
    typedef MushcoreMaptorIterator<T, K, C> iterator;
    typedef MushcoreMaptorConstIterator<T, K, C> const_iterator;
    
    
    typedef typename C::iterator tMapIter;
    typedef typename C::const_iterator tMapConstIter;
    
    typedef MushcoreMaptorRef<T, K, MushcoreMaptor> tRef;
    
    MushcoreMaptor();
    ~MushcoreMaptor();
    
    // Standard container interface
    bool empty(void) const { return m_data.empty(); }
    K size(void) const; // Returns the highest key value +1
    void resize(const K& inSize); // Ensures that size returns inSize
    iterator begin(void) { return iterator(m_data.begin()); }
    iterator end(void) { return iterator(m_data.end()); }
    const_iterator begin(void) const { return const_iterator(m_data.begin()); }
    const_iterator end(void) const { return const_iterator(m_data.end()); }
    mapped_type& operator[](const key_type& k) { return m_data[k]; }
    void erase(iterator pos) { erase(pos.MapIter()); }
    size_type erase(const key_type& key);
    void clear(void);
    T& back(void);
    const T& back(void) const; 
    void push_back(const T& inObj);
    void pop_back(void);
    
    // Give/Get/Delete/Clear interface
    T *Give(T *inpObj, const K& inKey);
    T& Get(const K& inKey) const;
    T& GetOrCreate(const K& inKey);
    bool Exists(const K& inKey) const;
    bool GetIfExists(T *& outpObj, const K& inKey) const;
    void Delete(const iterator& inIter) { erase(inIter.MapIter()); }
    void Delete(const K& inKey);
    bool DeleteIfExists(const K& inKey) { return (erase(inKey) != 0); }
    void Clear(void) { clear(); }
	
	// Key helper
	K NextKey(void) { return m_nextKey++; } // If used, K must have ++ operator
	
    // XML operations
    void XMLRead(MushcoreXMLIStream& ioIn);
    void XMLPrint(MushcoreXMLOStream& ioOut) const;
    
protected:
    MushcoreMaptor(const MushcoreMaptor& inMaptor);
    MushcoreMaptor& operator=(const MushcoreMaptor& inMaptor);
    void erase(tMapIter pos);
    void erase(tMapIter first, tMapIter last);

private:
    C m_data; //:readwrite
    Mushware::U32 m_sequenceNum; //:read Incremented when anything is deleted
    K m_nextKey;
	
//%classPrototypes {
public:
    const C& Data(void) const { return m_data; }
    void DataSet(const C& inValue) { m_data=inValue; }
    const Mushware::U32& SequenceNum(void) const { return m_sequenceNum; }
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } OBcmHLdwqGT/h6MK+bElEw
};

template<class T, class K, class C>
inline
MushcoreMaptor<T, K, C>::MushcoreMaptor() :
    m_sequenceNum(0),
    m_nextKey(K())
{
}

template<class T, class K, class C>
inline
MushcoreMaptor<T, K, C>::MushcoreMaptor(const MushcoreMaptor<T, K, C>& inMaptor)
{
    // Not able to clone the contents of m_data
    throw MushcoreLogicFail("Cannot copy construct MushcoreMaptor");
}

template<class T, class K, class C>
inline
MushcoreMaptor<T, K, C>::~MushcoreMaptor()
{
    std::for_each(m_data.begin(), m_data.end(), MushcoreUtil::DeleteSecond<T, K>);
}

template<class T, class K, class C>
inline MushcoreMaptor<T, K, C>&
MushcoreMaptor<T, K, C>::operator=(const MushcoreMaptor<T, K, C>& inMaptor)
{
    // Not able to clone the contents of m_data
    throw MushcoreLogicFail("Cannot assign MushcoreMaptor");
    return *this;
}

template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::erase(tMapIter pos)
{
    delete pos->second;
    m_data.erase(pos);
    ++m_sequenceNum;
}

template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::erase(tMapIter first, tMapIter last)
{
    // This one doesn't erase 'last'
    tMapIter p = first;
    while (p != last)
    {
        erase(p++);
    }
}

template<class T, class K, class C>
inline typename MushcoreMaptor<T, K, C>::size_type
MushcoreMaptor<T, K, C>::erase(const key_type& key)
{
    tMapIter p = m_data.find(key);
    bool retVal = (p != m_data.end());
    if (retVal)
    {
        erase(p);
    }
    return retVal;
}

template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::clear(void)
{
    std::for_each(m_data.begin(), m_data.end(), MushcoreUtil::DeleteSecond<T, K>);
    m_data.clear();
    ++m_sequenceNum;
}

template<class T, class K, class C>
inline K
MushcoreMaptor<T, K, C>::size(void) const
{
    if (m_data.empty())
    {
        return K();
    }
    return (--m_data.end())->first + 1;
}

template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::resize(const K& inSize)
{
    if (inSize <= 0)
    {
        m_data.clear();
    }
    else
    {
        // erase everything with key value >= size
        erase(m_data.lower_bound(inSize), m_data.end());
        if (m_data.find(inSize - 1) == m_data.end())
        {
            m_data[inSize - 1] = NULL;
        }
    }
}

template<class T, class K, class C>
inline T&
MushcoreMaptor<T, K, C>::back(void)
{
    if (m_data.empty())
    {
        throw MushcoreDataFail("Access to back() of empty maptor");
    }
    T *retPtr = (--m_data.end())->second;
    if (retPtr == NULL)
    {
        throw MushcoreDataFail("Access to NULL at back() of maptor");
    }
    return *retPtr;
}

template<class T, class K, class C>
inline const T&
MushcoreMaptor<T, K, C>::back(void) const
{
    if (m_data.empty())
    {
        throw MushcoreDataFail("Access to back() of empty maptor");
    }
    const T *retPtr = (--m_data.end())->second;
    if (retPtr == NULL)
    {
        throw MushcoreDataFail("Access to NULL at back() of maptor");
    }
    return *retPtr;
}

template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::push_back(const T& inObj)
{
    K keyValue;
    if (m_data.empty())
    {
        keyValue = K();
    }
    else
    {
        keyValue = (--m_data.end())->first + 1;
    }
    Give(new T(inObj), keyValue);
}

template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::pop_back(void)
{
    if (m_data.empty())
    {
        throw MushcoreDataFail("pop_back() on empty maptor");
    }
    erase(--m_data.end());
}

template<class T, class K, class C>
inline T *
MushcoreMaptor<T, K, C>::Give(T *inpObj, const K& inKey)
{
    tMapIter p = m_data.find(inKey);
    if (p != m_data.end())
    {
        // Already exists, so replace
        delete p->second;
        p->second = inpObj;
    }
    else
    {
        // Not there, so assign
        m_data[inKey] = inpObj;
    }
    return inpObj;
}

template<class T, class K, class C>
inline T&
MushcoreMaptor<T, K, C>::Get(const K& inKey) const
{
    tMapConstIter p = m_data.find(inKey);
    if (p == m_data.end())
    {
        std::ostringstream message;
        message << "No element '" << inKey << "' in MushcoreMaptor";
        throw MushcoreDataFail(message.str());
    }
    if (p->second == NULL)
    {
        throw MushcoreDataFail("MushcoreMaptor::Get() called on NULL object");
    }
    return *(p->second);
}

template<class T, class K, class C>
inline T&
MushcoreMaptor<T, K, C>::GetOrCreate(const K& inKey)
{
	T *retPtr = NULL;
    tMapIter p = m_data.find(inKey);
    if (p == m_data.end())
    {
		retPtr = new T;
        m_data[inKey] = retPtr;
    }
	else if (p->second == NULL)
    {
		retPtr = new T;
		p->second = retPtr;
    }
	else
	{
		retPtr = p->second;	
	}
	MUSHCOREASSERT(retPtr != NULL);
    return *retPtr;
}

template<class T, class K, class C>
inline bool
MushcoreMaptor<T, K, C>::GetIfExists(T *& outpObj, const K& inKey) const
{
    tMapConstIter p = m_data.find(inKey);
    if (p == m_data.end())
    {
        return false;
    }
    outpObj = p->second;
    return true;
}

template<class T, class K, class C>
inline bool
MushcoreMaptor<T, K, C>::Exists(const K& inKey) const
{
    T *pObj;  // Discarded value
    return GetIfExists(pObj, inKey);
}

template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::Delete(const K& inKey)
{
    tMapIter p = m_data.find(inKey);
    if (p == m_data.end())
    {
        std::ostringstream message;
        message << "No element '" << inKey << "' to delete in MushcoreMaptor";
        throw MushcoreDataFail(message.str());
    }
    else
    {
        erase(p);
    }
}

// XML operators
template<class T, class K, class C>
inline MushcoreXMLIStream&
operator>>(MushcoreXMLIStream& ioIn, MushcoreMaptor<T, K, C>& outObj)
{
    outObj.XMLRead(ioIn);
    return ioIn;
}

template<class T, class K, class C>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushcoreMaptor<T, K, C>& inObj)
{
    inObj.XMLPrint(ioOut);
    return ioOut;
}

template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::XMLRead(MushcoreXMLIStream& ioIn)
{
    ioIn >> m_data;
}

template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::XMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut << m_data;
}

//%inlineHeader {
template<class T, class K, class C>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushcoreMaptor<T, K, C>& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "data=" << m_data << ", ";
    ioOut << "sequenceNum=" << m_sequenceNum << ", ";
    ioOut << "nextKey=" << m_nextKey;
    ioOut << "]";
}
//%inlineHeader } T8DNonMs0TjvuKI67DPdAw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
