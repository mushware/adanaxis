/*
 * $Id: CoreHistory.h,v 1.2 2002/12/04 15:39:57 southa Exp $
 * $Log: CoreHistory.h,v $
 * Revision 1.2  2002/12/04 15:39:57  southa
 * Multiplayer work
 *
 * Revision 1.1  2002/12/04 12:54:40  southa
 * Network control work
 *
 */

#include "CoreStandard.h"

template<class IndexType, class StoreType> class CoreHistory;

template<class IndexType, class StoreType>class CoreHistoryIterator
{
public:
    CoreHistoryIterator() : m_history(NULL), m_valid(false) {}
    CoreHistoryIterator(const CoreHistory<IndexType, StoreType>& inHistory, U32 inIndex);
    void AssertValid(void) const;
    const IndexType& IndexGet(void) const;
    const StoreType& StoreGet(void) const;
    void BackMove(void);
    void ForwardMove(void);
    bool ValidIs(void) const;

private:
    const CoreHistory<IndexType, StoreType> *m_history;
    U32 m_index;
    bool m_valid;
};

template<class IndexType, class StoreType> class CoreHistory
{
public:
    CoreHistory(U32 inSize, IndexType inInitial);
    
    void Add(const StoreType& inStore, IndexType inIndex);
    bool PreviousGet(const StoreType *& outStore, IndexType inIndex) const;
    CoreHistoryIterator<IndexType, StoreType> IteratorPreviousGet(IndexType inIndex) const;
    CoreHistoryIterator<IndexType, StoreType> Back(void) const;
    bool IndexValidIs(U32 inIndex) const;
    const IndexType& IndexGet(U32 inIndex) const;
    const StoreType& StoreGet(U32 inIndex) const;
    bool BackMove(U32& ioIndex) const; // For use by iterator
    bool ForwardMove(U32& ioIndex) const; // For use by iterator
    
protected:

private:
    struct tBuffer
    {
        IndexType index;
        StoreType store;
    };
    
    vector<tBuffer> m_buffer;
    U32 m_bufferIndex;
    U32 m_bufferSize;
    U32 m_invalidIndex; // Index of first invalid (never set) entry
};


// ----- CoreHistoryIterator -----

template<class IndexType, class StoreType>
inline
CoreHistoryIterator<IndexType, StoreType>::CoreHistoryIterator(const CoreHistory<IndexType, StoreType>& inHistory, U32 inIndex) :
    m_history(&inHistory),
    m_index(inIndex)
{
    m_valid = inHistory.IndexValidIs(m_index);
}

template<class IndexType, class StoreType>
inline void
CoreHistoryIterator<IndexType, StoreType>::AssertValid(void) const
{
    COREASSERT(m_history != NULL);
    if (!m_valid) throw(LogicFail("Use of invalid iterator"));
}

template<class IndexType, class StoreType>
inline const IndexType&
CoreHistoryIterator<IndexType, StoreType>::IndexGet(void) const
{
    AssertValid();
    return m_history->IndexGet(m_index);
}

template<class IndexType, class StoreType>
inline const StoreType&
CoreHistoryIterator<IndexType, StoreType>::StoreGet(void) const
{
    AssertValid();
    return m_history->StoreGet(m_index);
}

template<class IndexType, class StoreType>
inline void
CoreHistoryIterator<IndexType, StoreType>::BackMove(void)
{
    AssertValid();
    m_valid = m_history->BackMove(m_index);
}

template<class IndexType, class StoreType>
inline void
CoreHistoryIterator<IndexType, StoreType>::ForwardMove(void)
{
    AssertValid();
    m_valid = m_history->ForwardMove(m_index);
}

template<class IndexType, class StoreType>
inline bool
CoreHistoryIterator<IndexType, StoreType>::ValidIs(void) const
{
    return m_valid;
}

// ----- CoreHistory -----

template<class IndexType, class StoreType>
CoreHistory<IndexType, StoreType>::CoreHistory(U32 inSize, IndexType inInitial) :
    m_buffer(inSize),
    m_bufferIndex(0),
    m_bufferSize(inSize),
    m_invalidIndex(0)
{
    COREASSERT(inSize > 0); // Suggests parameters wrong way round
    for (U32 i=0; i<m_bufferSize; ++i)
    {
        m_buffer[i].index = inInitial;
    }
}

template<class IndexType, class StoreType>
inline void
CoreHistory<IndexType, StoreType>::Add(const StoreType& inStore, IndexType inIndex)
{
    COREASSERT(m_bufferIndex < m_buffer.size());
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
CoreHistory<IndexType, StoreType>::PreviousGet(const StoreType *& outStore, IndexType inIndex) const
{
    // Search backwards through the history, starting at the last added entry.  Return the first
    // entry found with an index <= inIndex, or false if no such valid entry exists
    
    U32 bufferIndex = m_bufferIndex;
    for (U32 i=0; i<m_bufferSize; ++i)
    {
        if (bufferIndex == 0)
        {
            bufferIndex = m_bufferSize;
        }
        --bufferIndex;
        
        COREASSERT(bufferIndex < m_buffer.size());

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
inline CoreHistoryIterator<IndexType, StoreType>
CoreHistory<IndexType, StoreType>::IteratorPreviousGet(IndexType inIndex) const
{
    // Search backwards through the history, starting at the last added entry.  Return the first
    // entry found with an index <= inIndex, or false if no such valid entry exists

    U32 bufferIndex = m_bufferIndex;
    for (U32 i=0; i<m_bufferSize; ++i)
    {
        if (bufferIndex == 0)
        {
            bufferIndex = m_bufferSize;
        }
        --bufferIndex;

        COREASSERT(bufferIndex < m_buffer.size());

        const tBuffer& bufferEntry = m_buffer[bufferIndex];

        if (bufferEntry.index <= inIndex)
        {
            if (bufferIndex < m_invalidIndex)
            {
                return CoreHistoryIterator<IndexType, StoreType>(*this, bufferIndex);
            }
            return CoreHistoryIterator<IndexType, StoreType>();
        }
    }
    return CoreHistoryIterator<IndexType, StoreType>();
}

template<class IndexType, class StoreType>
inline CoreHistoryIterator<IndexType, StoreType>
CoreHistory<IndexType, StoreType>::Back(void) const
{
    U32 bufferIndex = m_bufferIndex;

    if (bufferIndex == 0)
    {
        bufferIndex = m_bufferSize;
    }
    --bufferIndex;
    
    return CoreHistoryIterator<IndexType, StoreType>(*this, bufferIndex);
}    

template<class IndexType, class StoreType>
inline bool
CoreHistory<IndexType, StoreType>::IndexValidIs(U32 inIndex) const
{
    return inIndex < m_invalidIndex;
}

template<class IndexType, class StoreType>
inline const IndexType&
CoreHistory<IndexType, StoreType>::IndexGet(U32 inIndex) const
{
    COREASSERT(inIndex < m_invalidIndex);
    return m_buffer[inIndex].index;
}

template<class IndexType, class StoreType>
inline const StoreType&
CoreHistory<IndexType, StoreType>::StoreGet(U32 inIndex) const
{
    COREASSERT(inIndex < m_invalidIndex);
    return m_buffer[inIndex].store;
}

template<class IndexType, class StoreType>
inline bool
CoreHistory<IndexType, StoreType>::BackMove(U32& ioIndex) const
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
CoreHistory<IndexType, StoreType>::ForwardMove(U32& ioIndex) const
{
    ++ioIndex;
    if (ioIndex == m_bufferSize)
    {
        ioIndex = 0;
    }
    
    return ioIndex < m_invalidIndex && ioIndex != m_bufferIndex;
}
