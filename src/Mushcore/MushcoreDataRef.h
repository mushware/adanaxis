#ifndef MUSHCOREDATAREF_H
#define MUSHCOREDATAREF_H

/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MushcoreDataRef.h,v 1.6 2003/02/05 17:06:37 southa Exp $
 * $Log: MushcoreDataRef.h,v $
 * Revision 1.6  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.5  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.4  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
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
 * Revision 1.8  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.7  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.5  2002/12/05 13:20:10  southa
 * Client link handling
 *
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
 * MushcoreData and MushcoreDatRef
 *
 */

#include "MushcoreData.h"
#include "MushcoreFail.h"
#include "MushcoreStandard.h"

template<class RefType> class MushcoreDataRef
{
public:
    inline MushcoreDataRef();
    inline explicit MushcoreDataRef(MushcoreData<RefType> *inInstance);
    inline explicit MushcoreDataRef(const std::string& inName);
    inline MushcoreDataRef(const std::string& inName, MushcoreData<RefType> *inInstance);
    
    void NameSet(const std::string& inName) { m_name=inName; m_dataPtr=NULL; }
    const std::string& NameGet(void) const { return m_name; }
    inline RefType *Get(void) const;
    inline bool GetIfExists(RefType *& outRef) const;
    inline bool Exists(void) const;

private:
    inline void ReferenceGet(void) const;
    inline void DefaultDataPtrGet(void);
    
    std::string m_name;
    MushcoreData<RefType> *m_dataInstance;
    mutable RefType *m_dataPtr;
    mutable Mushware::U32 m_sequenceNum;
};

template<class RefType>
inline
MushcoreDataRef<RefType>::MushcoreDataRef() :
    m_dataPtr(NULL),
    m_sequenceNum(1)
{
    DefaultDataPtrGet();
}

template<class RefType>
inline
MushcoreDataRef<RefType>::MushcoreDataRef(MushcoreData<RefType> *inInstance) :
    m_dataInstance(inInstance),
    m_dataPtr(NULL),
    m_sequenceNum(1)
{
}

template<class RefType>
inline
MushcoreDataRef<RefType>::MushcoreDataRef(const std::string& inName) :
    m_name(inName),
    m_dataPtr(NULL),
    m_sequenceNum(1)
{
    DefaultDataPtrGet();
}


template<class RefType>
inline
MushcoreDataRef<RefType>::MushcoreDataRef(const std::string& inName, MushcoreData<RefType> *inInstance) :
    m_name(inName),
    m_dataInstance(inInstance),
    m_dataPtr(NULL),
    m_sequenceNum(1)
{
}

template<class RefType>
inline void
MushcoreDataRef<RefType>::DefaultDataPtrGet(void)
{
    m_dataInstance = &MushcoreData<RefType>::Sgl();
}

template<class RefType>
inline void
MushcoreDataRef<RefType>::ReferenceGet(void) const
{
    MUSHCOREASSERT(m_dataInstance != NULL);
    
    m_dataPtr = m_dataInstance->GetOrReturnNull(m_name);
    m_sequenceNum = m_dataInstance->SequenceNumGet();
}

template<class RefType>
inline RefType *
MushcoreDataRef<RefType>::Get(void) const
{
    if (m_dataPtr == NULL || m_sequenceNum != m_dataInstance->SequenceNumGet())
    {
        ReferenceGet();
        if (m_dataPtr == NULL)
        {
            throw(MushcoreReferenceFail("Attempt to access non-existent data '"+m_name+"'"));
        }
    }
    return m_dataPtr;
}

template<class RefType>
inline bool
MushcoreDataRef<RefType>::GetIfExists(RefType *& outRef) const
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
MushcoreDataRef<RefType>::Exists(void) const
{
    if (m_dataPtr != NULL && m_sequenceNum == m_dataInstance->SequenceNumGet()) return true;
    ReferenceGet();
    return (m_dataPtr != NULL);
}

#endif

