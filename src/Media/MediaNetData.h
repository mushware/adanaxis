/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class MediaNetData
{
public:
    MediaNetData();
    MediaNetData(const string& inStr);

    U32 ReadPosGet(void) const;
    U32 ReadSizeGet(void) const;
    void ReadPosAdd(U32 inAdd);
    U8 *ReadPtrGet(void);

    U32 WritePosGet(void) const;
    U32 WriteSizeGet(void) const;
    void WritePosAdd(U32 inAdd);
    U8 *WritePtrGet(void);

    U8 BytePop(void);
    void BytePush(U8 inByte);

    void PrepareForWrite(void);

    void Print(ostream& ioOut) const;
    
private:
    enum
    {
        kChunkSize=1024
    };

    U32 m_readPos;
    U32 m_writePos;
    vector<U8> m_data;
};

ostream& operator<<(ostream &inOut, const MediaNetData& inData);

inline
MediaNetData::MediaNetData() :
m_readPos(0),
m_writePos(0),
m_data(kChunkSize)
{
}

inline
MediaNetData::MediaNetData(const string& inStr) :
m_readPos(0),
m_writePos(0),
m_data(kChunkSize)
{
    U32 size=inStr.size();
    for (U32 i=0; i<size; ++i)
    {
        BytePush(inStr[i]);
    }
}

inline U32
MediaNetData::ReadPosGet(void) const
{
    COREASSERT(m_readPos < m_data.size());
    return m_readPos;
}

inline U32
MediaNetData::ReadSizeGet(void) const
{
    COREASSERT(m_readPos <= m_writePos);
    return m_writePos - m_readPos;
}

inline void
MediaNetData::ReadPosAdd(U32 inAdd)
{
    m_readPos += inAdd;
    COREASSERT(m_readPos < m_data.size());
}

inline U8 *
MediaNetData::ReadPtrGet(void)
{
    COREASSERT(m_readPos < m_data.size());
    return &m_data[m_readPos];
}

inline U32
MediaNetData::WritePosGet(void) const
{
    COREASSERT(m_writePos < m_data.size());
    return m_writePos;
}

inline U32
MediaNetData::WriteSizeGet(void) const
{
    COREASSERT(m_writePos <= m_data.size());
    return m_data.size() - m_writePos;
}

inline void
MediaNetData::WritePosAdd(U32 inAdd)
{
    m_writePos += inAdd;
    COREASSERT(m_writePos < m_data.size());
}

inline U8 *
MediaNetData::WritePtrGet(void)
{
    COREASSERT(m_writePos < m_data.size());
    return &m_data[m_writePos];
}

inline U8
MediaNetData::BytePop(void)
{
    COREASSERT(m_readPos < m_data.size());
    return m_data[m_readPos++];
}

inline void
MediaNetData::BytePush(U8 inByte)
{
    PrepareForWrite();

    COREASSERT(m_writePos < m_data.size());
    m_data[m_writePos++]=inByte;
}

inline void
MediaNetData::PrepareForWrite(void)
{
    if (m_writePos + kChunkSize/2 > m_data.size())
    {
        m_data.resize(m_writePos + kChunkSize);
    }
}

