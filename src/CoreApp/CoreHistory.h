/*
 * $Id$
 * $Log$
 */

#include "CoreStandard.h"

template<class IndexType, class StoreType> class CoreHistory
{
public:
    CoreHistory(U32 inSize, IndexType inInitial);
    
    void Add(const StoreType& inStore, IndexType inIndex);
    bool PreviousGet(const StoreType *& outStore, IndexType inIndex);
    bool NextEntryGet(const IndexType *& outIndex, const StoreType *& outStore);
    
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
    U32 m_lastBufferIndex;
    bool m_lastBufferIndexValid;
};

template<class IndexType, class StoreType>
CoreHistory<IndexType, StoreType>::CoreHistory(U32 inSize, IndexType inInitial) :
    m_buffer(inSize),
    m_bufferIndex(0),
    m_bufferSize(inSize),
    m_invalidIndex(0),
    m_lastBufferIndexValid(false)
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
CoreHistory<IndexType, StoreType>::PreviousGet(const StoreType *& outStore, IndexType inIndex)
{
    // Search backwards through the history, starting at the last added entry.  Return the first
    // entry found with an index <= inIndex, or false if no such valid entry exists
    m_lastBufferIndexValid = false;
    
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
                m_lastBufferIndex = bufferIndex;
                m_lastBufferIndexValid = true;
                break;
            }
        }
    }
    return m_lastBufferIndexValid;
}

template<class IndexType, class StoreType>
inline bool
CoreHistory<IndexType, StoreType>::NextEntryGet(const IndexType *& outIndex, const StoreType *& outStore)
{
    COREASSERT(m_lastBufferIndexValid);

    ++m_lastBufferIndex;

    if (m_lastBufferIndex >= m_bufferSize) m_lastBufferIndex = 0;
    
    if (m_lastBufferIndex >= m_invalidIndex ||
        m_lastBufferIndex == m_bufferIndex)
    {
        m_lastBufferIndexValid = false;
    }
    else
    {
        COREASSERT(m_lastBufferIndex < m_buffer.size());
        const tBuffer& bufferEntry = m_buffer[bufferIndex];
        outIndex = &bufferEntry.index;
        outStore = &bufferEntry.store;
    }
    return m_lastBufferIndexValid;
}
