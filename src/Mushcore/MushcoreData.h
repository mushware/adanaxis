#ifndef MUSHCOREDATA_H
#define MUSHCOREDATA_H

/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MushcoreData.h,v 1.5 2003/01/17 13:30:40 southa Exp $
 * $Log: MushcoreData.h,v $
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
#include "MushcoreDestroySingleton.h"

#define MUSHCORE_DATA_INSTANCE(RefType) MUSHCORE_SINGLETON_INSTANCE(MushcoreData< RefType >)
#define MUSHCORE_DESTROY_DATA_INSTANCE(RefType) MUSHCORE_DESTROY_SINGLETON_INSTANCE(MushcoreData< RefType >)

template<class RefType> class MushcoreData : public MushcoreSingleton< MushcoreData<RefType> >
{
public:
    typedef typename std::map<std::string, RefType *> tMap;
    typedef typename tMap::iterator tMapIterator;
    typedef typename tMap::const_iterator tMapConstIterator;

    MUSHCORE_DECLARE_INLINE MushcoreData();
    MUSHCORE_DECLARE_INLINE ~MushcoreData();

    MUSHCORE_DECLARE_INLINE RefType *Give(const std::string& inName, RefType *inData);
    MUSHCORE_DECLARE_INLINE RefType *Get(const std::string& inName) const;
    MUSHCORE_DECLARE_INLINE RefType *GetOrReturnNull(const std::string& inName) const;
    MUSHCORE_DECLARE_INLINE bool GetIfExists(RefType *& outData, const std::string& inName) const;
    MUSHCORE_DECLARE_INLINE void Delete(const std::string& inName);
    MUSHCORE_DECLARE_INLINE void Delete(const tMapIterator& inIterator);
    MUSHCORE_DECLARE_INLINE bool Exists(const std::string& inName) const;
    MUSHCORE_DECLARE_INLINE void Clear(void);
    MUSHCORE_DECLARE_INLINE Mushware::U32 Size(void);
    MUSHCORE_DECLARE_INLINE void Iterate(void (*inFnPtr)(RefType&));
    MUSHCORE_DECLARE_INLINE void Dump(std::ostream& ioOut);
    MUSHCORE_DECLARE_INLINE tMapIterator Begin(void);
    MUSHCORE_DECLARE_INLINE tMapIterator End(void);
    MUSHCORE_DECLARE_INLINE Mushware::U32 SequenceNumGet(void) const;
    
protected:

private:
    tMap m_data;
    Mushware::U32 m_sequenceNum; // Incremented when anything is deleted
};

template<class RefType>
MushcoreData<RefType>::MushcoreData(void) :
    m_sequenceNum(1)
{
}

template<class RefType>
MushcoreData<RefType>::~MushcoreData(void)
{
    for (tMapIterator p = m_data.begin();
         p != m_data.end(); ++p)
    {
        delete p->second;
    }
}

template<class RefType>
inline RefType *
MushcoreData<RefType>::Give(const std::string& inName, RefType *inData)
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

template<class RefType>
inline RefType *
MushcoreData<RefType>::Get(const std::string& inName) const
{
    tMapConstIterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        throw(MushcoreReferenceFail("Access to non-existent data '"+inName+"'"));
    }
    return p->second;
}

template<class RefType>
inline RefType *
MushcoreData<RefType>::GetOrReturnNull(const std::string& inName) const
{
    tMapConstIterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        return NULL;
    }
    return p->second;
}

template<class RefType>
inline bool
MushcoreData<RefType>::GetIfExists(RefType *& outData, const std::string& inName) const
{
    tMapConstIterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        return false;
    }
    outData=p->second;
    return true;
}

template<class RefType>
inline void
MushcoreData<RefType>::Delete(const std::string& inName)
{
    tMapIterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        throw(MushcoreReferenceFail("Delete of non-existent data '"+inName+"'"));
    }
    Delete(p);
}

template<class RefType>
inline void
MushcoreData<RefType>::Delete(const tMapIterator& inIterator)
{
    MUSHCOREASSERT(inIterator->second != NULL);
    ++m_sequenceNum;
    delete inIterator->second;
    m_data.erase(inIterator);
}

template<class RefType>
inline bool
MushcoreData<RefType>::Exists(const std::string& inName) const
{
    tMapConstIterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        return false;
    }
    return true;
}

template<class RefType>
inline void
MushcoreData<RefType>::Clear(void)
{
    ++m_sequenceNum;
    tMapIterator endIter = m_data.end();
    for (tMapIterator p = m_data.begin(); p != endIter; ++p)
    {
        delete p->second;
    }
    m_data.clear();
}

template<class RefType>
inline Mushware::U32
MushcoreData<RefType>::Size(void)
{
    return m_data.size();
}

template<class RefType>
inline void
MushcoreData<RefType>::Iterate(void (*inFnPtr)(RefType&))
{
    tMapIterator endIter = m_data.end();
    for (tMapIterator p = m_data.begin(); p != endIter; ++p)
    {
        inFnPtr(*p->second);
    }
}

template<class RefType>
inline void
MushcoreData<RefType>::Dump(std::ostream& ioOut)
{
    tMapIterator endIter = m_data.end();
    for (tMapIterator p = m_data.begin(); p != endIter; ++p)
    {
        ioOut << p->first << ": " << *p->second << endl;
    }
}

template<class RefType>
inline typename MushcoreData<RefType>::tMapIterator
MushcoreData<RefType>::Begin(void)
{
    return m_data.begin();
}

template<class RefType>
inline typename MushcoreData<RefType>::tMapIterator
MushcoreData<RefType>::End(void)
{
    return m_data.end();
}

template<class RefType>
inline Mushware::U32
MushcoreData<RefType>::SequenceNumGet(void) const
{
    return m_sequenceNum;
}

#endif
