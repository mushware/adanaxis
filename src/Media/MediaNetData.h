#ifndef MEDIANETDATA_H
#define MEDIANETDATA_H
/*
 * $Id: MediaNetData.h,v 1.7 2002/11/25 10:43:28 southa Exp $
 * $Log: MediaNetData.h,v $
 * Revision 1.7  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.6  2002/11/22 15:00:32  southa
 * Network connection handling
 *
 * Revision 1.5  2002/11/12 17:05:01  southa
 * Tidied localweb server
 *
 * Revision 1.4  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.3  2002/11/03 20:10:00  southa
 * Initial message unpacking
 *
 * Revision 1.2  2002/11/01 18:46:25  southa
 * UDP Links
 *
 * Revision 1.1  2002/11/01 16:15:27  southa
 * Network send and receive
 *
 */

#include "mushCore.h"

class MediaNetData
{
public:
    MediaNetData();
    explicit MediaNetData(const string& inStr);

    U32 ReadPosGet(void) const;
    U32 ReadSizeGet(void) const;
    void ReadPosAdd(U32 inAdd);
    U8 *ReadPtrGet(void);

    U32 WritePosGet(void) const;
    U32 WriteSizeGet(void) const;
    void WritePosAdd(U32 inAdd);
    U8 *WritePtrGet(void);
    void Write(const string& inStr);
    
    U32 MessagePosGet(void) const;
    void MessagePosSet(U32 inPos);
    U32 MessageSizeGet(void) const;
    U8 *MessagePtrGet(void);

    void LengthPosSet(U32 inPos);

    U32 UnpackStateGet(void) const;
    void UnpackStateSet(U32 inState);

    U32 SourceHostGet(void);
    U32 SourcePortGet(void);
    void SourceSet(U32 inHost, U32 inPort);
    
    bool IsEmptyForRead(void) const;

    U8 BytePop(void);
    U8 MessageBytePop(void);
    void BytePush(U8 inByte); // Slow operation
    void LengthBytePush(U8 inByte);

    void PrepareForWrite(void);
    void PrepareForWrite(U32 inSize);

    void Print(ostream& ioOut) const;
    
private:
    enum
    {
        kChunkSize=1024
    };

    U32 m_readPos;
    U32 m_writePos;
    U32 m_messagePos;
    U32 m_lengthPos;
    U32 m_unpackState;
    U32 m_sourceHost;
    U32 m_sourcePort;
    bool m_sourceValid;
    vector<U8> m_data;
};

ostream& operator<<(ostream &inOut, const MediaNetData& inData);

inline
MediaNetData::MediaNetData() :
    m_readPos(0),
    m_writePos(0),
    m_messagePos(0),
    m_lengthPos(0),
    m_unpackState(0),
    m_sourceValid(false)
{
}

inline
MediaNetData::MediaNetData(const string& inStr) :
    m_readPos(0),
    m_writePos(0),
    m_messagePos(0),
    m_lengthPos(0),
    m_unpackState(0),
    m_sourceValid(false)
{
    Write(inStr);
}

inline U32
MediaNetData::ReadPosGet(void) const
{
    COREASSERT(m_readPos <= m_data.size());
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
    COREASSERT(m_readPos <= m_data.size());
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
    COREASSERT(m_writePos <= m_data.size());
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
    COREASSERT(m_writePos <= m_data.size());
}

inline U8 *
MediaNetData::WritePtrGet(void)
{
    COREASSERT(m_writePos < m_data.size());
    return &m_data[m_writePos];
}

inline void
MediaNetData::Write(const string& inStr)
{
    U32 size=inStr.size();
    PrepareForWrite(size);
    memcpy(WritePtrGet(), inStr.c_str(), size);
    WritePosAdd(size);
}

inline U32
MediaNetData::MessagePosGet(void) const
{
    COREASSERT(m_messagePos <= m_data.size());
    return m_messagePos;
}

inline void
MediaNetData::MessagePosSet(U32 inPos)
{
    COREASSERT(inPos <= m_data.size());
    m_messagePos=inPos;
}

inline U32
MediaNetData::MessageSizeGet(void) const
{
    COREASSERT(m_messagePos <= m_writePos);
    return m_writePos - m_messagePos;

}

inline U8 *
MediaNetData::MessagePtrGet(void)
{
    COREASSERT(m_messagePos < m_data.size());
    return &m_data[m_messagePos];
}

inline void
MediaNetData::LengthPosSet(U32 inPos)
{
    COREASSERT(inPos <= m_data.size());
    m_lengthPos=inPos;
}

inline U32
MediaNetData::UnpackStateGet(void) const
{
    return m_unpackState;
}

inline void
MediaNetData::UnpackStateSet(U32 inState)
{
    m_unpackState=inState;
}

inline U32
MediaNetData::SourceHostGet(void)
{
    COREASSERT(m_sourceValid);
    return m_sourceHost;
}

inline U32
MediaNetData::SourcePortGet(void)
{
    COREASSERT(m_sourceValid);
    return m_sourcePort;
}

inline void
MediaNetData::SourceSet(U32 inHost, U32 inPort)
{
    m_sourceHost=inHost;
    m_sourcePort=inPort;
    m_sourceValid=true;
}

inline bool
MediaNetData::IsEmptyForRead(void) const
{
    return m_readPos >= m_writePos;
}

inline U8
MediaNetData::BytePop(void)
{
    COREASSERT(m_readPos < m_data.size());
    return m_data[m_readPos++];
}

inline U8
MediaNetData::MessageBytePop(void)
{
    COREASSERT(m_messagePos < m_data.size());
    return m_data[m_messagePos++];
}

inline void
MediaNetData::BytePush(U8 inByte)
{
    PrepareForWrite();

    COREASSERT(m_writePos < m_data.size());
    m_data[m_writePos++]=inByte;
}

inline void
MediaNetData::LengthBytePush(U8 inByte)
{
    PrepareForWrite(m_lengthPos+3);

    COREASSERT(m_lengthPos < m_data.size());
    m_data[m_lengthPos++]=inByte;
}

inline void
MediaNetData::PrepareForWrite(void)
{
    if (m_writePos == m_readPos)
    {
        m_writePos=0;
        m_readPos=0;
    }
    // Always leave at least kChunkSize/2 writable bytes
    if (m_writePos + kChunkSize/2 > m_data.size())
    {
        m_data.resize(m_writePos + kChunkSize);
    }
}

inline void
MediaNetData::PrepareForWrite(U32 inSize)
{
    if (m_writePos == m_readPos)
    {
        m_writePos=0;
        m_readPos=0;
    }
    if (m_writePos+inSize >= m_data.size())
    {
        m_data.resize(m_writePos+inSize+1);
    }
}

#endif
