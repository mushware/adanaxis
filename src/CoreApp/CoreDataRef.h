#ifndef COREDATAREF_H
#define COREDATAREF_H

/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: CoreDataRef.h,v 1.1 2002/08/15 13:39:30 southa Exp $
 * $Log: CoreDataRef.h,v $
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

