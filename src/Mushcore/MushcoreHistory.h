//%includeGuardStart {
#ifndef MUSHCOREHISTORY_H
#define MUSHCOREHISTORY_H
//%includeGuardStart } Qge8Q1pFNOal2L5aZmlWOw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreHistory.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } dbQP5VPhKgJFEOkJOdx7gw
/*
 * $Id: MushcoreHistory.h,v 1.5 2003/09/17 19:40:35 southa Exp $
 * $Log: MushcoreHistory.h,v $
 * Revision 1.5  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:09:13  southa
 * Fixed file headers
 *
 * Revision 1.3  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.4  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/10 20:38:05  southa
 * Server timing
 *
 * Revision 1.2  2002/12/04 15:39:57  southa
 * Multiplayer work
 *
 * Revision 1.1  2002/12/04 12:54:40  southa
 * Network control work
 *
 */

#include "MushcoreStandard.h"

template<class IndexType, class StoreType> class MushcoreHistory;

template<class IndexType, class StoreType>class MushcoreHistoryIterator
{
public:
    MushcoreHistoryIterator() : m_history(NULL), m_valid(false) {}
    MushcoreHistoryIterator(const MushcoreHistory<IndexType, StoreType>& inHistory, Mushware::U32 inIndex);
    void AssertValid(void) const;
    const IndexType& IndexGet(void) const;
    const StoreType& StoreGet(void) const;
    void BackMove(void);
    void ForwardMove(void);
    bool ValidIs(void) const;

private:
    const MushcoreHistory<IndexType, StoreType> *m_history;
    Mushware::U32 m_index;
    bool m_valid;
};

template<class IndexType, class StoreType> class MushcoreHistory
{
public:
    MushcoreHistory(Mushware::U32 inSize, IndexType inInitial);
    
    void Add(const StoreType& inStore, IndexType inIndex);
    bool PreviousGet(const StoreType *& outStore, IndexType inIndex) const;
    MushcoreHistoryIterator<IndexType, StoreType> IteratorPreviousGet(IndexType inIndex) const;
    MushcoreHistoryIterator<IndexType, StoreType> Back(void) const;
    bool IndexValidIs(Mushware::U32 inIndex) const;
    const IndexType& IndexGet(Mushware::U32 inIndex) const;
    const StoreType& StoreGet(Mushware::U32 inIndex) const;
    bool BackMove(Mushware::U32& ioIndex) const; // For use by iterator
    bool ForwardMove(Mushware::U32& ioIndex) const; // For use by iterator
    
protected:

private:
    struct tBuffer
    {
        IndexType index;
        StoreType store;
    };
    
    std::vector<tBuffer> m_buffer;
    Mushware::U32 m_bufferIndex;
    Mushware::U32 m_bufferSize;
    Mushware::U32 m_invalidIndex; // Index of first invalid (never set) entry
};


// ----- MushcoreHistoryIterator -----

template<class IndexType, class StoreType>
inline
MushcoreHistoryIterator<IndexType, StoreType>::MushcoreHistoryIterator(const MushcoreHistory<IndexType, StoreType>& inHistory, Mushware::U32 inIndex) :
    m_history(&inHistory),
    m_index(inIndex)
{
    m_valid = inHistory.IndexValidIs(m_index);
}

template<class IndexType, class StoreType>
inline void
MushcoreHistoryIterator<IndexType, StoreType>::AssertValid(void) const
{
    MUSHCOREASSERT(m_history != NULL);
    if (!m_valid) throw(MushcoreLogicFail("Use of invalid iterator"));
}

template<class IndexType, class StoreType>
inline const IndexType&
MushcoreHistoryIterator<IndexType, StoreType>::IndexGet(void) const
{
    AssertValid();
    return m_history->IndexGet(m_index);
}

template<class IndexType, class StoreType>
inline const StoreType&
MushcoreHistoryIterator<IndexType, StoreType>::StoreGet(void) const
{
    AssertValid();
    return m_history->StoreGet(m_index);
}

template<class IndexType, class StoreType>
inline void
MushcoreHistoryIterator<IndexType, StoreType>::BackMove(void)
{
    AssertValid();
    m_valid = m_history->BackMove(m_index);
}

template<class IndexType, class StoreType>
inline void
MushcoreHistoryIterator<IndexType, StoreType>::ForwardMove(void)
{
    AssertValid();
    m_valid = m_history->ForwardMove(m_index);
}

template<class IndexType, class StoreType>
inline bool
MushcoreHistoryIterator<IndexType, StoreType>::ValidIs(void) const
{
    return m_valid;
}

// ----- MushcoreHistory -----

template<class IndexType, class StoreType>
MushcoreHistory<IndexType, StoreType>::MushcoreHistory(Mushware::U32 inSize, IndexType inInitial) :
    m_buffer(inSize),
    m_bufferIndex(0),
    m_bufferSize(inSize),
    m_invalidIndex(0)
{
    MUSHCOREASSERT(inSize > 0); // Suggests parameters wrong way round
    for (Mushware::U32 i=0; i<m_bufferSize; ++i)
    {
        m_buffer[i].index = inInitial;
    }
}

template<class IndexType, class StoreType>
inline void
MushcoreHistory<IndexType, StoreType>::Add(const StoreType& inStore, IndexType inIndex)
{
    MUSHCOREASSERT(m_bufferIndex < m_buffer.size());
    tBuffer& bufferEntry = m_buffer[m_bufferIndex];
    bufferEntry.index = inIndex;
    bufferEntry.store = inStore;

    ++m_bufferIndex;
    if (m_bufferIndex > m_invalidIndex)
    {
        m_invalidIndex = m_bufferIndex;
    }

    if (m_bufferIndex >= m_bufferSize)
    {
        m_bufferIndex = 0;
    }
}

template<class IndexType, class StoreType>
inline bool
MushcoreHistory<IndexType, StoreType>::PreviousGet(const StoreType *& outStore, IndexType inIndex) const
{
    // Search backwards through the history, starting at the last added entry.  Return the first
    // entry found with an index <= inIndex, or false if no such valid entry exists
    
    Mushware::U32 bufferIndex = m_bufferIndex;
    for (Mushware::U32 i=0; i<m_bufferSize; ++i)
    {
        if (bufferIndex == 0)
        {
            bufferIndex = m_bufferSize;
        }
        --bufferIndex;
        
        MUSHCOREASSERT(bufferIndex < m_buffer.size());

        const tBuffer& bufferEntry = m_buffer[bufferIndex];

        if (bufferEntry.index <= inIndex)
        {
            if (bufferIndex < m_invalidIndex)
            {
                outStore = &bufferEntry.store;
                return true;
            }
            return false;
        }
    }
    return false;
}

template<class IndexType, class StoreType>
inline MushcoreHistoryIterator<IndexType, StoreType>
MushcoreHistory<IndexType, StoreType>::IteratorPreviousGet(IndexType inIndex) const
{
    // Search backwards through the history, starting at the last added entry.  Return the first
    // entry found with an index <= inIndex, or false if no such valid entry exists

    Mushware::U32 bufferIndex = m_bufferIndex;
    for (Mushware::U32 i=0; i<m_bufferSize; ++i)
    {
        if (bufferIndex == 0)
        {
            bufferIndex = m_bufferSize;
        }
        --bufferIndex;

        MUSHCOREASSERT(bufferIndex < m_buffer.size());

        const tBuffer& bufferEntry = m_buffer[bufferIndex];

        if (bufferEntry.index <= inIndex)
        {
            if (bufferIndex < m_invalidIndex)
            {
                return MushcoreHistoryIterator<IndexType, StoreType>(*this, bufferIndex);
            }
            return MushcoreHistoryIterator<IndexType, StoreType>();
        }
    }
    return MushcoreHistoryIterator<IndexType, StoreType>();
}

template<class IndexType, class StoreType>
inline MushcoreHistoryIterator<IndexType, StoreType>
MushcoreHistory<IndexType, StoreType>::Back(void) const
{
    Mushware::U32 bufferIndex = m_bufferIndex;

    if (bufferIndex == 0)
    {
        bufferIndex = m_bufferSize;
    }
    --bufferIndex;
    
    return MushcoreHistoryIterator<IndexType, StoreType>(*this, bufferIndex);
}    

template<class IndexType, class StoreType>
inline bool
MushcoreHistory<IndexType, StoreType>::IndexValidIs(Mushware::U32 inIndex) const
{
    return inIndex < m_invalidIndex;
}

template<class IndexType, class StoreType>
inline const IndexType&
MushcoreHistory<IndexType, StoreType>::IndexGet(Mushware::U32 inIndex) const
{
    MUSHCOREASSERT(inIndex < m_invalidIndex);
    return m_buffer[inIndex].index;
}

template<class IndexType, class StoreType>
inline const StoreType&
MushcoreHistory<IndexType, StoreType>::StoreGet(Mushware::U32 inIndex) const
{
    MUSHCOREASSERT(inIndex < m_invalidIndex);
    return m_buffer[inIndex].store;
}

template<class IndexType, class StoreType>
inline bool
MushcoreHistory<IndexType, StoreType>::BackMove(Mushware::U32& ioIndex) const
{
    if (ioIndex == 0)
    {
        ioIndex = m_bufferSize;
    }
    --ioIndex;
    
    return ioIndex < m_invalidIndex && ioIndex != m_bufferIndex;
}

template<class IndexType, class StoreType>
inline bool
MushcoreHistory<IndexType, StoreType>::ForwardMove(Mushware::U32& ioIndex) const
{
    ++ioIndex;
    if (ioIndex == m_bufferSize)
    {
        ioIndex = 0;
    }
    
    return ioIndex < m_invalidIndex && ioIndex != m_bufferIndex;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
