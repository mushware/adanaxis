//%includeGuardStart {
#ifndef MUSHCOREDATAREF_H
#define MUSHCOREDATAREF_H
//%includeGuardStart } RXj/skHy669y6ziUMpPDWA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreDataRef.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } PnzbnMrxb1qHtbgCO/gBtw

/*
 * $Id: MushcoreDataRef.h,v 1.12 2004/01/08 16:06:11 southa Exp $
 * $Log: MushcoreDataRef.h,v $
 * Revision 1.12  2004/01/08 16:06:11  southa
 * XML fixes
 *
 * Revision 1.11  2004/01/06 10:08:51  southa
 * MushcoreData and MushPieForm work
 *
 * Revision 1.10  2004/01/05 14:27:41  southa
 * MushPie work and build fixes
 *
 * Revision 1.9  2004/01/02 17:31:48  southa
 * MushPie work and XML fixes
 *
 * Revision 1.8  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:10  southa
 * Fixed file headers
 *
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
#include "MushcoreXMLIStream.h"
#include "MushcoreXMLOStream.h"

template<class RefType, class KeyType = std::string>
class MushcoreDataRef
{
public:
    inline MushcoreDataRef();
    inline explicit MushcoreDataRef(MushcoreData<RefType, KeyType>& inInstance);
    inline explicit MushcoreDataRef(const KeyType& inName);
    inline MushcoreDataRef(const KeyType& inName, MushcoreData<RefType, KeyType>& inInstance);
    
    void NameSet(const KeyType& inName) { m_name=inName; m_dataPtr=NULL; }
    const KeyType& NameGet(void) const { return m_name; }
    inline RefType *Get(void) const;
    inline RefType& RefGet(void) const;
    inline bool GetIfExists(RefType *& outRef) const;
    inline bool Exists(void) const;
    bool Equals(const MushcoreDataRef& inObj) const;

private:
    inline void ReferenceGet(void) const;
    inline void DefaultDataPtrGet(void);
    
    KeyType m_name;
    MushcoreData<RefType, KeyType> *m_dataInstance;
    mutable RefType *m_dataPtr;
    mutable Mushware::U32 m_sequenceNum;
// classPrototypes { Modified
public:
    void AutoPrint(std::ostream& ioOut) const;
// classPrototypes }
};

template<class RefType, class KeyType>
inline
MushcoreDataRef<RefType, KeyType>::MushcoreDataRef() :
    m_dataPtr(NULL),
    m_sequenceNum(1)
{
    DefaultDataPtrGet();
}

template<class RefType, class KeyType>
inline
MushcoreDataRef<RefType, KeyType>::MushcoreDataRef(MushcoreData<RefType, KeyType>& inInstance) :
    m_dataInstance(&inInstance),
    m_dataPtr(NULL),
    m_sequenceNum(1)
{
}

template<class RefType, class KeyType>
inline
MushcoreDataRef<RefType, KeyType>::MushcoreDataRef(const KeyType& inName) :
    m_name(inName),
    m_dataPtr(NULL),
    m_sequenceNum(1)
{
    DefaultDataPtrGet();
}


template<class RefType, class KeyType>
inline
MushcoreDataRef<RefType, KeyType>::MushcoreDataRef(const KeyType& inName, MushcoreData<RefType, KeyType> &inInstance) :
    m_name(inName),
    m_dataInstance(&inInstance),
    m_dataPtr(NULL),
    m_sequenceNum(1)
{
}

template<class RefType, class KeyType>
inline void
MushcoreDataRef<RefType, KeyType>::DefaultDataPtrGet(void)
{
    m_dataInstance = &MushcoreData<RefType, KeyType>::Sgl();
}

template<class RefType, class KeyType>
inline void
MushcoreDataRef<RefType, KeyType>::ReferenceGet(void) const
{
    MUSHCOREASSERT(m_dataInstance != NULL);
    
    m_dataPtr = m_dataInstance->GetOrReturnNull(m_name);
    m_sequenceNum = m_dataInstance->SequenceNumGet();
}

template<class RefType, class KeyType>
inline RefType *
MushcoreDataRef<RefType, KeyType>::Get(void) const
{
    if (m_dataPtr == NULL || m_sequenceNum != m_dataInstance->SequenceNumGet())
    {
        ReferenceGet();
        if (m_dataPtr == NULL)
        {
            std::ostringstream message;
            message << "Attempt to access non-existent data '" << m_name << "'";
            throw MushcoreReferenceFail(message.str());
        }
    }
    return m_dataPtr;
}

template<class RefType, class KeyType>
inline RefType&
MushcoreDataRef<RefType, KeyType>::RefGet(void) const
{
    if (m_dataPtr == NULL || m_sequenceNum != m_dataInstance->SequenceNumGet())
    {
        ReferenceGet();
        if (m_dataPtr == NULL)
        {
            std::ostringstream message;
            message << "Attempt to access non-existent data '" << m_name << "'";
            throw MushcoreReferenceFail(message.str());
        }
    }
    return *m_dataPtr;
}

template<class RefType, class KeyType>
inline bool
MushcoreDataRef<RefType, KeyType>::GetIfExists(RefType *& outRef) const
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

template<class RefType, class KeyType>
inline bool
MushcoreDataRef<RefType, KeyType>::Exists(void) const
{
    if (m_dataPtr != NULL && m_sequenceNum == m_dataInstance->SequenceNumGet()) return true;
    ReferenceGet();
    return (m_dataPtr != NULL);
}

// inlineHeader { Modified
template<class RefType, class KeyType>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushcoreDataRef<RefType, KeyType>& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
// inlineHeader }

// outOfLineFunctions { Modified
template<class RefType, class KeyType>
inline void
MushcoreDataRef<RefType, KeyType>::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "name=" << m_name << ", ";
    if (m_dataInstance == NULL)
    {
        ioOut << "dataInstance=NULL" ;
    }
    else
    {
        ioOut << "dataInstance=" << m_dataInstance; // Modified not to print the entire dataset
    }
    ioOut << "]";
}
//%outOfLineFunctions }

// XML operators treat this object as a single string
template<class RefType, class KeyType>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushcoreDataRef<RefType, KeyType>& inObj)
{
    ioOut << inObj.NameGet();
    return ioOut;
}

template<class RefType, class KeyType>
inline void
operator>>(MushcoreXMLIStream& ioIn, MushcoreDataRef<RefType, KeyType>& outObj)
{
    KeyType keyValue;
    ioIn >> keyValue;
    outObj.NameSet(keyValue);
}

template<class RefType, class KeyType>
inline bool
operator==(const MushcoreDataRef<RefType, KeyType>& inA, const MushcoreDataRef<RefType, KeyType>& inB)
{
    return inA.Equals(inB);
}

template<class RefType, class KeyType>
inline bool
operator!=(const MushcoreDataRef<RefType, KeyType>& inA, const MushcoreDataRef<RefType, KeyType>& inB)
{
    return !inA.Equals(inB);
}

template<class RefType, class KeyType>
inline bool
MushcoreDataRef<RefType, KeyType>::Equals(const MushcoreDataRef<RefType, KeyType>& inObj) const
{
    return 1
        && (m_name == inObj.m_name)
        && (m_dataInstance == inObj.m_dataInstance)
    ;
}


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
