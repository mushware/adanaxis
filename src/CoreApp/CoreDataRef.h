#ifndef COREDATAREF_H
#define COREDATAREF_H

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
 * $Id: CoreDataRef.h,v 1.4 2002/12/03 20:28:14 southa Exp $
 * $Log: CoreDataRef.h,v $
 * Revision 1.4  2002/12/03 20:28:14  southa
 * Network, player and control work
 *
 * Revision 1.3  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.1  2002/08/15 13:39:30  southa
 * CoreData and CoreDatRef
 *
 */

#include "mushCore.h"

#include "CoreStandard.h"
#include "CoreData.h"
#include "CoreException.h"

template<class RefType> class CoreDataRef
{
public:
    CoreDataRef();
    explicit CoreDataRef(CoreData<RefType> *inInstance);
    explicit CoreDataRef(const string& inName);
    CoreDataRef(const string& inName, CoreData<RefType> *inInstance);
    
    void NameSet(const string& inName) { m_name=inName; m_dataPtr=NULL; }
    const string& NameGet(void) const { return m_name; }
    RefType *Get(void) const;
    bool GetIfExists(RefType *& outRef) const;
    bool Exists(void) const;

private:
    void ReferenceGet(void) const;
    void DefaultDataPtrGet(void);
    
    string m_name;
    CoreData<RefType> *m_dataInstance;
    mutable RefType *m_dataPtr;
    mutable U32 m_sequenceNum;
};

template<class RefType>
inline
CoreDataRef<RefType>::CoreDataRef() :
    m_dataPtr(NULL),
    m_sequenceNum(1)
{
    DefaultDataPtrGet();
}

template<class RefType>
inline
CoreDataRef<RefType>::CoreDataRef(CoreData<RefType> *inInstance) :
    m_dataInstance(inInstance),
    m_dataPtr(NULL),
    m_sequenceNum(1)
{
}

template<class RefType>
inline
CoreDataRef<RefType>::CoreDataRef(const string& inName) :
    m_name(inName),
    m_dataPtr(NULL),
    m_sequenceNum(1)
{
    DefaultDataPtrGet();
}


template<class RefType>
inline
CoreDataRef<RefType>::CoreDataRef(const string& inName, CoreData<RefType> *inInstance) :
    m_name(inName),
    m_dataInstance(inInstance),
    m_dataPtr(NULL),
    m_sequenceNum(1)
{
}

template<class RefType>
inline void
CoreDataRef<RefType>::DefaultDataPtrGet(void)
{
    m_dataInstance = &CoreData<RefType>::Instance();
}

template<class RefType>
inline void
CoreDataRef<RefType>::ReferenceGet(void) const
{
    COREASSERT(m_dataInstance != NULL);
    
    m_dataPtr = m_dataInstance->GetOrReturnNull(m_name);
    m_sequenceNum = m_dataInstance->SequenceNumGet();
}

template<class RefType>
inline RefType *
CoreDataRef<RefType>::Get(void) const
{
    if (m_dataPtr == NULL || m_sequenceNum != m_dataInstance->SequenceNumGet())
    {
        ReferenceGet();
        if (m_dataPtr == NULL)
        {
            throw(ReferenceFail("Attempt to access non-existent data '"+m_name+"'"));
        }
    }
    return m_dataPtr;
}

template<class RefType>
inline bool
CoreDataRef<RefType>::GetIfExists(RefType *& outRef) const
{
    if (m_dataPtr == NULL || m_sequenceNum != m_dataInstance->SequenceNumGet())
    {
        ReferenceGet();
        if (m_dataPtr == NULL)
        {
            return false;
        }
    }
    outRef = m_dataPtr;
    return true;
}

template<class RefType>
inline bool
CoreDataRef<RefType>::Exists(void) const
{
    if (m_dataPtr != NULL && m_sequenceNum == m_dataInstance->SequenceNumGet()) return true;
    ReferenceGet();
    return (m_dataPtr != NULL);
}

#endif

