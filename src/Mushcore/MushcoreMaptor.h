//%includeGuardStart {
#ifndef MUSHCOREMAPTOR_H
#define MUSHCOREMAPTOR_H
//%includeGuardStart } sgC6Fg2ig+cctgMAe9F1mQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreMaptor.h
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
//%Header } 1+xBZKC0ADJmMoP0vONLyQ
/*
 * $Id$
 * $Log$
 */

#include "MushcoreStandard.h"

#include "MushcoreFail.h"
#include "MushcoreUtil.h"
#include "MushcoreXMLIStream.h"
#include "MushcoreXMLOStream.h"

//:generate nonvirtual inline ostream xml1
template<class T, class K = Mushware::U32, class C = std::map<K, T *> >
class MushcoreMaptor
{
public:
    typedef typename std::pair<const K, T *> value_type;
    typedef typename C::size_type size_type;
    typedef typename C::difference_type difference_type;
    typedef C container_type;
    typedef K key_type;
    typedef T *mapped_type;
    typedef typename C::reference reference;
    typedef typename C::const_reference const_reference;
    typedef typename C::iterator iterator;
    typedef typename C::const_iterator const_iterator;
    typedef typename C::reverse_iterator reverse_iterator;
    typedef typename C::const_reverse_iterator const_reverse_iterator;
    
    MushcoreMaptor();
    ~MushcoreMaptor();
    
    
    // Standrd container interface
    bool empty(void) const { return m_data.empty(); }
    size_type size(void) const { return m_data.size(); }
    iterator begin(void) { return m_data.begin(); }
    iterator end(void) { return m_data.end(); }
    const_iterator begin(void) const { return m_data.begin(); }
    const_iterator end(void) const { return m_data.end(); }
    reverse_iterator rbegin(void) { return m_data.rbegin(); }
    reverse_iterator rend(void) { return m_data.rend(); }
    const_reverse_iterator rbegin(void) const { return m_data.rbegin(); }
    const_reverse_iterator rend(void) const { return m_data.rend(); }
    mapped_type& operator[](const key_type& k) { return m_data[k]; }
    void erase(iterator pos)
    {
        delete pos->second;
        m_data.erase(pos);
        ++m_sequenceNum;
    }
    size_type erase(const key_type& key)
    {
        iterator p = m_data.find(key);
        bool retVal = (p != end());
        if (retVal)
        {
            erase(p);
        }
        return retVal;
    }
    void clear(void)
    {
        std::for_each(begin(), end(), MushcoreUtil::DeleteSecond<T, K>);
        m_data.clear();
    }
    
    T& back()
    {
        if (empty())
        {
            throw MushcoreDataFail("Access to back() of empty maptor");
        }
        return (--end())->second;
    }
    const T& back() const
    {
        if (empty())
        {
            throw MushcoreDataFail("Access to back() of empty maptor");
        }
        return (--end())->second;
    }    
    void push_back(const T& inObj)
    {
        Mushware::U32 keyValue;
        if (empty())
        {
            keyValue = 0;
        }
        else
        {
            keyValue = (--end())->first + 1;
        }
        Give(new T(inObj), keyValue);
    }
    void pop_back()
    {
        if (empty())
        {
            throw MushcoreDataFail("pop_back() on empty maptor");
        }
        erase(--end());
    }
    
#if 0
    // These would work if key value was S32
    T& front();
    const T& front() const;
    void push_front(const T& inObj);
    void pop_front();
#endif
    
    // Give/Get/Delete interface
    void Give(T *inpObj, const K& inKey);
    T *Get(const K& inKey) const;
    bool GetIfExists(T *& outpObj, const K& inKey) const;
    void Delete(const K& inKey);
    bool DeleteIfExists(const K& inKey) { return (erase(inKey) != 0); }
    void Clear(void) { clear(); }
    
protected:
    MushcoreMaptor(const MushcoreMaptor& inMaptor);
    MushcoreMaptor& operator=(const MushcoreMaptor& inMaptor);

private:
    C m_data; //:readwrite
    Mushware::U32 m_sequenceNum; //:read Incremented when anything is deleted
    
//%classPrototypes {
public:
    const C& Data(void) const { return m_data; }
    void DataSet(const C& inValue) { m_data=inValue; }
    const Mushware::U32& SequenceNum(void) const { return m_sequenceNum; }
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } uhzUwIvDj+qpJZgx3bbwjQ
};

template<class T, class K, class C>
inline
MushcoreMaptor<T, K, C>::MushcoreMaptor() :
    m_sequenceNum(0)
{
}

template<class T, class K, class C>
inline
MushcoreMaptor<T, K, C>::MushcoreMaptor(const MushcoreMaptor<T, K, C>& inMaptor)
{
    throw MushcoreLogicFail("Cannot copy construct MushcoreMaptor yet");
}

template<class T, class K, class C>
inline
MushcoreMaptor<T, K, C>::~MushcoreMaptor()
{
    std::for_each(begin(), end(), MushcoreUtil::DeleteSecond<T, K>);
}

template<class T, class K, class C>
inline MushcoreMaptor<T, K, C>&
MushcoreMaptor<T, K, C>::operator=(const MushcoreMaptor<T, K, C>& inMaptor)
{
    throw MushcoreLogicFail("Cannot assign MushcoreMaptor yet");
    return *this;
}

template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::Give(T *inpObj, const K& inKey)
{
    iterator p = m_data.find(inKey);
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
}

template<class T, class K, class C>
inline T *
MushcoreMaptor<T, K, C>::Get(const K& inKey) const
{
    const_iterator p = m_data.find(inKey);
    if (p == m_data.end())
    {
        std::ostringstream message;
        message << "No element '" << inKey << "' in MushcoreMaptor";
        throw MushcoreDataFail(message.str());
    }
    return p->second;
}

template<class T, class K, class C>
inline bool
MushcoreMaptor<T, K, C>::GetIfExists(T *& outpObj, const K& inKey) const
{
    const_iterator p = m_data.find(inKey);
    if (p == m_data.end())
    {
        return false;
    }
    outpObj = p->second;
    return true;
}

template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::Delete(const K& inKey)
{
    iterator p = m_data.find(inKey);
    if (p == m_data.end())
    {
        std::ostringstream message;
        message << "No element '" << inKey << "' in MushcoreMaptor";
        throw MushcoreDataFail(message.str());
    }
    else
    {
        erase(p);
    }
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
inline MushcoreXMLIStream&
operator>>(MushcoreXMLIStream& ioIn, MushcoreMaptor<T, K, C>& outObj)
{
    throw MushcoreDataFail("Cannot read XML object type 'MushcoreMaptor'");
    return ioIn;
}
template<class T, class K, class C>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushcoreMaptor<T, K, C>& inObj)
{
    inObj.AutoXMLPrint(ioOut);
    return ioOut;
}
template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "retVal=" << retVal << ", ";
    ioOut << "keyValue=" << keyValue << ", ";
    ioOut << "data=" << m_data << ", ";
    ioOut << "sequenceNum=" << m_sequenceNum;
    ioOut << "]";
}
template<class T, class K, class C>
inline bool
MushcoreMaptor<T, K, C>::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "retVal")
    {
        ioIn >> retVal;
    }
    else if (inTagStr == "keyValue")
    {
        ioIn >> keyValue;
    }
    else if (inTagStr == "data")
    {
        ioIn >> m_data;
    }
    else if (inTagStr == "sequenceNum")
    {
        ioIn >> m_sequenceNum;
    }
    else 
    {
        return false;
    }
    return true;
}
template<class T, class K, class C>
inline void
MushcoreMaptor<T, K, C>::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("retVal");
    ioOut << retVal;
    ioOut.TagSet("keyValue");
    ioOut << keyValue;
    ioOut.TagSet("data");
    ioOut << m_data;
    ioOut.TagSet("sequenceNum");
    ioOut << m_sequenceNum;
}
//%inlineHeader } EkZlMaWRoB5OIxYVu5m0QQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
