#ifndef COREDATAREF_H
#define COREDATAREF_H

/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "CoreStandard.h"
#include "CoreData.h"
#include "CoreException.h"

template<class RefType> class CoreDataRef
{
public:
    CoreDataRef(): m_dataPtr(NULL) {}
    explicit CoreDataRef(const string& inName): m_name(inName), m_dataPtr(NULL) {}
    void NameSet(const string& inName) {m_name=inName; m_dataPtr=NULL;}
    const string& NameGet(void) const {return m_name;}
    inline RefType *DataGet(void) const;
    inline bool Exists(void) const;

private:
    inline void GetReference(void) const;
    string m_name;
    mutable RefType *m_dataPtr;
};

template<class RefType>
inline RefType *
CoreDataRef<RefType>::DataGet(void) const
{
    if (m_dataPtr == NULL)
    {
        GetReference();
    }
    return m_dataPtr;
}

template<class RefType>
inline void
CoreDataRef<RefType>::GetReference(void) const
{
    m_dataPtr=CoreData<RefType>::Instance().DataGet(m_name);
    if (m_dataPtr == NULL)
    {
        throw(ReferenceFail("Attempt to access non-existent data '"+m_name+"'"));
    }
}

template<class RefType>
inline bool
CoreDataRef<RefType>::Exists(void) const
{
    if (m_dataPtr != NULL) return true;
    m_dataPtr=CoreData<RefType>::Instance().DataGet(m_name);
    return (m_dataPtr != NULL);
}

#endif

