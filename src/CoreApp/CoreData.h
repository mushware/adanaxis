#ifndef COREDATA_H
#define COREDATA_H

/*
 * $Id$
 * $Log$
 */

#include "CoreStandard.h"
#include "CoreException.h"

template<class RefType> class CoreData
{
public:
    ~CoreData();
    static CoreData& Instance(void);

    inline RefType *DataGive(const string& inName, RefType *inData);
    inline RefType *DataGet(const string& inName) const;

protected:
    CoreData() {}

private:
    map<string, RefType *> m_data;
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

#endif
