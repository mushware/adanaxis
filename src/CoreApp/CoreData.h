#ifndef COREDATA_H
#define COREDATA_H

/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: CoreData.h,v 1.13 2002/12/05 13:20:10 southa Exp $
 * $Log: CoreData.h,v $
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
 * CoreData and CoreDatRef
 *
 */

#include "CoreStandard.h"
#include "CoreException.h"

template<class RefType> class CoreData
{
public:
    typedef map<string, RefType *> tMap;
    typedef map<string, RefType *>::iterator tMapIterator;
    typedef map<string, RefType *>::const_iterator tMapConstIterator;

    ~CoreData();
    static CoreData& Instance(void);
    static CoreData *PrivateInstanceCreate(void);

    RefType *Give(const string& inName, RefType *inData);
    RefType *Get(const string& inName) const;
    RefType *GetOrReturnNull(const string& inName) const;
    void Delete(const string& inName);
    void Delete(const map<string, RefType *>::iterator& inIterator);
    bool Exists(const string& inName) const;
    bool GetIfExists(RefType *& outData, const string& inName) const;
    void Clear(void);
    U32 Size(void);
    void Iterate(void (*inFnPtr)(RefType&));
    void Dump(ostream& ioOut);
    tMapIterator Begin(void);
    tMapIterator End(void);
    U32 SequenceNumGet(void) const;
    
protected:
    CoreData();

private:
    tMap m_data;
    U32 m_sequenceNum; // Incremented when anything is deleted
    static auto_ptr< CoreData<RefType> > m_instance;
};

template<class RefType>
CoreData<RefType>::CoreData(void) :
    m_sequenceNum(1)
{
}

template<class RefType>
CoreData<RefType>::~CoreData(void)
{
    for (map<string, RefType *>::iterator p = m_data.begin();
         p != m_data.end(); ++p)
    {
        delete p->second;
    }
}

template<class RefType>
inline class CoreData<RefType>&
CoreData<RefType>::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new CoreData);
    return *m_instance;
}

template<class RefType>
inline class CoreData<RefType> *
CoreData<RefType>::PrivateInstanceCreate(void)
{
    return new CoreData;
}

template<class RefType>
inline RefType *
CoreData<RefType>::Give(const string& inName, RefType *inData)
{
    map<string, RefType *>::iterator p = m_data.find(inName);
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
CoreData<RefType>::Get(const string& inName) const
{
    map<string, RefType *>::const_iterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        throw(ReferenceFail("Access to non-existent data '"+inName+"'"));
    }
    return p->second;
}

template<class RefType>
inline RefType *
CoreData<RefType>::GetOrReturnNull(const string& inName) const
{
    map<string, RefType *>::const_iterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        return NULL;
    }
    return p->second;
}

template<class RefType>
inline void
CoreData<RefType>::Delete(const string& inName)
{
    map<string, RefType *>::iterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        throw(ReferenceFail("Delete of non-existent data '"+inName+"'"));
    }
    ++m_sequenceNum;
    delete p->second;
    m_data.erase(p);
}

template<class RefType>
inline void
CoreData<RefType>::Delete(const map<string, RefType *>::iterator& inIterator)
{
    COREASSERT(inIterator->second != NULL);
    ++m_sequenceNum;
    delete inIterator->second;
    m_data.erase(inIterator);
}

template<class RefType>
inline bool
CoreData<RefType>::Exists(const string& inName) const
{
    map<string, RefType *>::const_iterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        return false;
    }
    return true;
}

template<class RefType>
inline bool
CoreData<RefType>::GetIfExists(RefType *& outData, const string& inName) const
{
    map<string, RefType *>::const_iterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        return false;
    }
    outData=p->second;
    return true;
}

template<class RefType>
inline void
CoreData<RefType>::Clear(void)
{
    ++m_sequenceNum;
    for (map<string, RefType *>::iterator p = m_data.begin();
         p != m_data.end(); ++p)
    {
        delete p->second;
    }
    m_data.clear();
}

template<class RefType>
inline U32
CoreData<RefType>::Size(void)
{
    return m_data.size();
}

template<class RefType>
inline void
CoreData<RefType>::Iterate(void (*inFnPtr)(RefType&))
{
    for (map<string, RefType *>::iterator p = m_data.begin();
         p != m_data.end(); ++p)
    {
        inFnPtr(*p->second);
    }
}

template<class RefType>
inline void
CoreData<RefType>::Dump(ostream& ioOut)
{
    ioOut << "Dumping data for CoreData<" << typeid(RefType).name() << ">" << endl;
    for (map<string, RefType *>::iterator p = m_data.begin();
         p != m_data.end(); ++p)
    {
        ioOut << p->first << ": " << *p->second << endl;
    }
}

template<class RefType>
inline CoreData<RefType>::tMapIterator
CoreData<RefType>::Begin(void)
{
    return m_data.begin();
}

template<class RefType>
inline CoreData<RefType>::tMapIterator
CoreData<RefType>::End(void)
{
    return m_data.end();
}

template<class RefType>
inline U32
CoreData<RefType>::SequenceNumGet(void) const
{
    return m_sequenceNum;
}

#endif
