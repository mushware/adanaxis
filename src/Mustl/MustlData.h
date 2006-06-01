//%includeGuardStart {
#ifndef MUSTLDATA_H
#define MUSTLDATA_H
//%includeGuardStart } +GO4zwxU9dZUymS9AaNtWQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlData.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 83+M1VT+DpKS+uPoTsK9xA
/*
 * $Id: MustlData.h,v 1.13 2005/05/19 13:02:18 southa Exp $
 * $Log: MustlData.h,v $
 * Revision 1.13  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.12  2004/09/28 23:05:55  southa
 * MSVC build of ic2
 *
 * Revision 1.11  2004/09/27 22:42:10  southa
 * MSVC compilation fixes
 *
 * Revision 1.10  2004/09/26 21:07:15  southa
 * Mustl compilation fixes
 *
 * Revision 1.9  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:24  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/07 17:13:44  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.5  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/13 19:03:05  southa
 * Mustl interface cleanup
 *
 * Revision 1.2  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.8  2002/11/25 15:44:03  southa
 * CreateObject message decoding
 *
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

#include "MustlAddress.h"
#include "MustlAssert.h"
#include "MustlStandard.h"

class MustlData
{
public:
    MustlData();
    explicit MustlData(const std::string& inStr);

    std::size_t ReadPosGet(void) const;
    std::size_t ReadSizeGet(void) const;
    void ReadPosAdd(std::size_t inAdd);
    Mustl::U8 *ReadPtrGet(void);

    std::size_t WritePosGet(void) const;
	std::size_t WriteSizeGet(void) const;
	void WritePosAdd(std::size_t inAdd);
    Mustl::U8 *WritePtrGet(void);
    void Write(const std::string& inStr);
    
    std::size_t MessagePosGet(void) const;
    void MessagePosSet(std::size_t inPos);
    std::size_t MessageSizeGet(void) const;
    Mustl::U8 *MessagePtrGet(void);

    void LengthPosSet(std::size_t inPos);

    Mustl::U32 UnpackStateGet(void) const;
    void UnpackStateSet(Mustl::U32 inState);

    const MustlAddress& SourceGet(void) const;
    void SourceSet(const MustlAddress& inAddress);
    
    bool IsEmptyForRead(void) const;

    Mustl::U8 BytePop(void);
    Mustl::U8 MessageBytePop(void);
    void BytePush(Mustl::U8 inByte); // Slow operation
    void LengthBytePush(Mustl::U8 inByte);

    void PrepareForWrite(void);
	void PrepareForWrite(std::size_t inSize);

    void Print(std::ostream& ioOut) const;
    
private:
    enum
    {
        kChunkSize=1024
    };

	std::size_t m_readPos;
	std::size_t m_writePos;
    std::size_t m_messagePos;
    std::size_t m_lengthPos;
    Mustl::U32 m_unpackState;
    MustlAddress m_sourceAddress;
    bool m_sourceValid;
    std::vector<Mustl::U8> m_data;
};

std::ostream& operator<<(std::ostream &inOut, const MustlData& inData);

inline
MustlData::MustlData() :
    m_readPos(0),
    m_writePos(0),
    m_messagePos(0),
    m_lengthPos(0),
    m_unpackState(0),
    m_sourceValid(false)
{
}

inline
MustlData::MustlData(const std::string& inStr) :
    m_readPos(0),
    m_writePos(0),
    m_messagePos(0),
    m_lengthPos(0),
    m_unpackState(0),
    m_sourceValid(false)
{
    Write(inStr);
}

inline std::size_t
MustlData::ReadPosGet(void) const
{
    MUSTLASSERT(m_readPos <= m_data.size());
    return m_readPos;
}

inline std::size_t
MustlData::ReadSizeGet(void) const
{
    MUSTLASSERT(m_readPos <= m_writePos);
    return m_writePos - m_readPos;
}

inline void
MustlData::ReadPosAdd(std::size_t inAdd)
{
    m_readPos += inAdd;
    MUSTLASSERT(m_readPos <= m_data.size());
}

inline Mustl::U8 *
MustlData::ReadPtrGet(void)
{
    MUSTLASSERT(m_readPos < m_data.size());
    return &m_data[m_readPos];
}

inline std::size_t
MustlData::WritePosGet(void) const
{
    MUSTLASSERT(m_writePos <= m_data.size());
    return m_writePos;
}

inline std::size_t
MustlData::WriteSizeGet(void) const
{
    MUSTLASSERT(m_writePos <= m_data.size());
    return m_data.size() - m_writePos;
}

inline void
MustlData::WritePosAdd(std::size_t inAdd)
{
    m_writePos += inAdd;
    MUSTLASSERT(m_writePos <= m_data.size());
}

inline Mustl::U8 *
MustlData::WritePtrGet(void)
{
    MUSTLASSERT(m_writePos < m_data.size());
    return &m_data[m_writePos];
}

inline void
MustlData::Write(const std::string& inStr)
{
	std::size_t size=inStr.size();
    PrepareForWrite(size);
    memcpy(WritePtrGet(), inStr.c_str(), size);
    WritePosAdd(size);
}

inline std::size_t
MustlData::MessagePosGet(void) const
{
    MUSTLASSERT(m_messagePos <= m_data.size());
    return m_messagePos;
}

inline void
MustlData::MessagePosSet(std::size_t inPos)
{
    MUSTLASSERT(inPos <= m_data.size());
    m_messagePos=inPos;
}

inline std::size_t
MustlData::MessageSizeGet(void) const
{
    MUSTLASSERT(m_messagePos <= m_writePos);
    return m_writePos - m_messagePos;

}

inline Mustl::U8 *
MustlData::MessagePtrGet(void)
{
    MUSTLASSERT(m_messagePos < m_data.size());
    return &m_data[m_messagePos];
}

inline void
MustlData::LengthPosSet(std::size_t inPos)
{
    MUSTLASSERT(inPos <= m_data.size());
    m_lengthPos=inPos;
}

inline Mustl::U32
MustlData::UnpackStateGet(void) const
{
    return m_unpackState;
}

inline void
MustlData::UnpackStateSet(Mustl::U32 inState)
{
    m_unpackState=inState;
}

inline const MustlAddress&
MustlData::SourceGet(void) const
{
    MUSTLASSERT(m_sourceValid);
    return m_sourceAddress;
}

inline void
MustlData::SourceSet(const MustlAddress& inAddress)
{
    m_sourceAddress=inAddress;
    m_sourceValid=true;
}

inline bool
MustlData::IsEmptyForRead(void) const
{
    return m_readPos >= m_writePos;
}

inline Mustl::U8
MustlData::BytePop(void)
{
    MUSTLASSERT(m_readPos < m_data.size());
    return m_data[m_readPos++];
}

inline Mustl::U8
MustlData::MessageBytePop(void)
{
    MUSTLASSERT(m_messagePos < m_data.size());
    return m_data[m_messagePos++];
}

inline void
MustlData::BytePush(Mustl::U8 inByte)
{
    PrepareForWrite();

    MUSTLASSERT(m_writePos < m_data.size());
    m_data[m_writePos++]=inByte;
}

inline void
MustlData::LengthBytePush(Mustl::U8 inByte)
{
    PrepareForWrite(m_lengthPos+3);

    MUSTLASSERT(m_lengthPos < m_data.size());
    m_data[m_lengthPos++]=inByte;
}

inline void
MustlData::PrepareForWrite(void)
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
MustlData::PrepareForWrite(std::size_t inSize)
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

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
