//%includeGuardStart {
#ifndef MUSHCOREDATA_H
#define MUSHCOREDATA_H
//%includeGuardStart } 5xx3QcLnHc7l0jqnvH7Hiw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreData.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 9n1OY34YpOaTjZkf4akFng

/*
 * $Id: MushcoreData.h,v 1.13 2004/01/02 21:13:12 southa Exp $
 * $Log: MushcoreData.h,v $
 * Revision 1.13  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.12  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.11  2003/08/21 23:09:09  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.9  2003/02/03 23:15:49  southa
 * Build work for Visual C++
 *
 * Revision 1.8  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.7  2003/01/18 17:05:47  southa
 * Singleton work
 *
 * Revision 1.6  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
 *
 * Revision 1.5  2003/01/17 13:30:40  southa
 * Source conditioning and build fixes
 *
 * Revision 1.4  2003/01/17 12:20:40  southa
 * Fixed std::auto_ptr duplication
 *
 * Revision 1.3  2003/01/12 17:32:59  southa
 * Mushcore work
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.17  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.16  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.15  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.14  2002/12/09 23:59:57  southa
 * Network control
 *
 * Revision 1.13  2002/12/05 13:20:10  southa
 * Client link handling
 *
 * Revision 1.12  2002/12/03 20:28:14  southa
 * Network, player and control work
 *
 * Revision 1.11  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.10  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
 * Revision 1.9  2002/11/18 18:55:56  southa
 * Game resume and quit
 *
 * Revision 1.8  2002/11/14 17:29:07  southa
 * Config database
 *
 * Revision 1.7  2002/11/04 19:34:46  southa
 * Network link maintenance
 *
 * Revision 1.6  2002/11/04 01:02:37  southa
 * Link checks
 *
 * Revision 1.5  2002/11/01 16:15:26  southa
 * Network send and receive
 *
 * Revision 1.4  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/16 19:46:06  southa
 * MediaSound work
 *
 * Revision 1.1  2002/08/15 13:39:30  southa
 * MushcoreData and MushcoreDatRef
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreFail.h"
#include "MushcoreSingleton.h"

#define MUSHCORE_DATA_INSTANCE(RefType) MUSHCORE_SINGLETON_INSTANCE(MushcoreData< RefType >)
#define MUSHCORE_DESTROY_DATA_INSTANCE(RefType) MUSHCORE_DESTROY_SINGLETON_INSTANCE(MushcoreData< RefType >)

template<class RefType, class KeyType = std::string>
class MushcoreData : public MushcoreSingleton< MushcoreData<RefType, KeyType> >
{
public:
    typedef MUSHCORE_TYPENAME std::map<KeyType, RefType *> tMap;
    typedef MUSHCORE_TYPENAME tMap::iterator tMapIterator;
    typedef MUSHCORE_TYPENAME tMap::const_iterator tMapConstIterator;

    inline MushcoreData();
    inline ~MushcoreData();

    inline RefType *Give(const KeyType& inName, RefType *inData);
    inline RefType *Get(const KeyType& inName) const;
    inline RefType *GetOrReturnNull(const KeyType& inName) const;
    inline bool GetIfExists(RefType *& outData, const KeyType& inName) const;
    inline void Delete(const KeyType& inName);
    inline void Delete(const tMapIterator& inIterator);
    inline bool Exists(const KeyType& inName) const;
    inline void Clear(void);
    inline Mushware::U32 Size(void);
    inline void Iterate(void (*inFnPtr)(RefType&));
    inline void Dump(std::ostream& ioOut);
    inline tMapIterator Begin(void);
    inline tMapIterator End(void);
    inline Mushware::U32 SequenceNumGet(void) const;
    
protected:

private:
    tMap m_data;
    Mushware::U32 m_sequenceNum; // Incremented when anything is deleted
};

template<class RefType, class KeyType>
MushcoreData<RefType, KeyType>::MushcoreData(void) :
    m_sequenceNum(1)
{
}

template<class RefType, class KeyType>
MushcoreData<RefType, KeyType>::~MushcoreData(void)
{
    for (tMapIterator p = m_data.begin();
         p != m_data.end(); ++p)
    {
        delete p->second;
    }
}

template<class RefType, class KeyType>
inline RefType *
MushcoreData<RefType, KeyType>::Give(const KeyType& inName, RefType *inData)
{
    tMapIterator p = m_data.find(inName);
    if (p != m_data.end())
    {
        ++m_sequenceNum;
        delete p->second;
        p->second=inData;
    }
    else
    {
        m_data[inName]=inData;
    }
    return inData;
}

template<class RefType, class KeyType>
inline RefType *
MushcoreData<RefType, KeyType>::Get(const KeyType& inName) const
{
    tMapConstIterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        throw(MushcoreReferenceFail("Access to non-existent data '"+inName+"'"));
    }
    return p->second;
}

template<class RefType, class KeyType>
inline RefType *
MushcoreData<RefType, KeyType>::GetOrReturnNull(const KeyType& inName) const
{
    tMapConstIterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        return NULL;
    }
    return p->second;
}

template<class RefType, class KeyType>
inline bool
MushcoreData<RefType, KeyType>::GetIfExists(RefType *& outData, const KeyType& inName) const
{
    tMapConstIterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        return false;
    }
    outData=p->second;
    return true;
}

template<class RefType, class KeyType>
inline void
MushcoreData<RefType, KeyType>::Delete(const KeyType& inName)
{
    tMapIterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        throw(MushcoreReferenceFail("Delete of non-existent data '"+inName+"'"));
    }
    Delete(p);
}

template<class RefType, class KeyType>
inline void
MushcoreData<RefType, KeyType>::Delete(const tMapIterator& inIterator)
{
    MUSHCOREASSERT(inIterator->second != NULL);
    ++m_sequenceNum;
    delete inIterator->second;
    m_data.erase(inIterator);
}

template<class RefType, class KeyType>
inline bool
MushcoreData<RefType, KeyType>::Exists(const KeyType& inName) const
{
    tMapConstIterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        return false;
    }
    return true;
}

template<class RefType, class KeyType>
inline void
MushcoreData<RefType, KeyType>::Clear(void)
{
    ++m_sequenceNum;
    tMapIterator endIter = m_data.end();
    for (tMapIterator p = m_data.begin(); p != endIter; ++p)
    {
        delete p->second;
    }
    m_data.clear();
}

template<class RefType, class KeyType>
inline Mushware::U32
MushcoreData<RefType, KeyType>::Size(void)
{
    return m_data.size();
}

template<class RefType, class KeyType>
inline void
MushcoreData<RefType, KeyType>::Iterate(void (*inFnPtr)(RefType&))
{
    tMapIterator endIter = m_data.end();
    for (tMapIterator p = m_data.begin(); p != endIter; ++p)
    {
        inFnPtr(*p->second);
    }
}

template<class RefType, class KeyType>
inline void
MushcoreData<RefType, KeyType>::Dump(std::ostream& ioOut)
{
    tMapIterator endIter = m_data.end();
    for (tMapIterator p = m_data.begin(); p != endIter; ++p)
    {
        ioOut << p->first << ": " << *p->second << endl;
    }
}

template<class RefType, class KeyType>
inline MUSHCORE_TYPENAME MushcoreData<RefType, KeyType>::tMapIterator
MushcoreData<RefType, KeyType>::Begin(void)
{
    return m_data.begin();
}

template<class RefType, class KeyType>
inline MUSHCORE_TYPENAME MushcoreData<RefType, KeyType>::tMapIterator
MushcoreData<RefType, KeyType>::End(void)
{
    return m_data.end();
}

template<class RefType, class KeyType>
inline Mushware::U32
MushcoreData<RefType, KeyType>::SequenceNumGet(void) const
{
    return m_sequenceNum;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
