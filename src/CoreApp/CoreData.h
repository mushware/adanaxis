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
 * $Id: CoreData.h,v 1.6 2002/11/04 01:02:37 southa Exp $
 * $Log: CoreData.h,v $
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

    inline RefType *DataGive(const string& inName, RefType *inData);
    inline RefType *DataGet(const string& inName) const;
    inline void DataDelete(const string& inName);
    inline void Clear(void);
    inline void Iterate(void (*inFnPtr)(RefType&));
    inline void Dump(ostream& ioOut);
    inline tMapIterator Begin(void);
    inline tMapIterator End(void);
    
protected:
    CoreData() {}

private:
    tMap m_data;
    static auto_ptr< CoreData<RefType> > m_instance;
};

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
inline RefType *
CoreData<RefType>::DataGive(const string& inName, RefType *inData)
{
    map<string, RefType *>::iterator p = m_data.find(inName);
    if (p != m_data.end())
    {
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
CoreData<RefType>::DataGet(const string& inName) const
{
    map<string, RefType *>::const_iterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        throw(ReferenceFail("Access to non-existent data '"+inName+"'"));
    }
    return p->second;
}

template<class RefType>
inline void
CoreData<RefType>::DataDelete(const string& inName)
{
    map<string, RefType *>::iterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        throw(ReferenceFail("Delete of non-existent data '"+inName+"'"));
    }
    delete p->second;
    m_data.erase(p);
}

template<class RefType>
inline void
CoreData<RefType>::Clear(void)
{
    for (map<string, RefType *>::iterator p = m_data.begin();
         p != m_data.end(); ++p)
    {
        delete p->second;
    }
    m_data.clear();
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


#endif
