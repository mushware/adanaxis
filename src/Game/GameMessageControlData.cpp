/*
 * $Id: GameMessageControlData.cpp,v 1.2 2002/12/09 23:59:58 southa Exp $
 * $Log: GameMessageControlData.cpp,v $
 * Revision 1.2  2002/12/09 23:59:58  southa
 * Network control
 *
 * Revision 1.1  2002/12/06 17:38:00  southa
 * ControlData message unpacking
 *
 */

#include "GameMessageControlData.h"

#include "GameProtocol.h"

#include "mushMedia.h"

const GameMessageControlData::DataEntry&
GameMessageControlData::DataEntryGet(U32 inEntryNum) const
{
    COREASSERT(inEntryNum < m_data.size());
    return m_data[inEntryNum];
}

void
GameMessageControlData::DataEntryPush(U32 inFrameOffset, const GameControlFrameDef& inDef)
{
    m_data.push_back(DataEntry());
    m_data.back().frameOffset = static_cast<U8>(inFrameOffset);
    m_data.back().frameDef = inDef;    
}

void
GameMessageControlData::Pack(MustlData& ioData) const
{
    MustlProtocol::LongAppMessageHeaderCreate(ioData, GameProtocol::kMessageTypeControlData);
    ioData.PrepareForWrite();
    ioData.BytePush(m_startFrame >> 8);
    ioData.BytePush(m_startFrame);
    U32 size = m_data.size();
    COREASSERT(size <= kEntryLimit);
    for (U32 i=0; i<size; ++i)
    {
        ioData.BytePush(m_data[i].frameOffset);
        ioData.BytePush(m_data[i].frameDef.mouseDeltaX);
        ioData.BytePush(m_data[i].frameDef.mouseDeltaY);
        ioData.BytePush(m_data[i].frameDef.keyState);
    }
    MustlProtocol::LongAppMessageFinish(ioData);
}

void
GameMessageControlData::Unpack(MustlData& ioData)
{
    m_startFrame = ioData.MessageBytePop() << 8;
    m_startFrame |= ioData.MessageBytePop();

    U32 messageSize = ioData.MessageSizeGet();
    U32 numEntries = messageSize / 4;

    if (messageSize % 4 != 0 || numEntries > kEntryLimit)
    {
        MustlLog::Instance().NetLog() << "Bad message size for ControlDataMessage (" << messageSize << ")" << endl;
        numEntries=0;
    }

    m_data.resize(numEntries);

    for (U32 i=0; i<numEntries; ++i)
    {
        m_data[i].frameOffset = ioData.MessageBytePop();
        m_data[i].frameDef.mouseDeltaX = ioData.MessageBytePop();
        m_data[i].frameDef.mouseDeltaY = ioData.MessageBytePop();
        m_data[i].frameDef.keyState = ioData.MessageBytePop();
    }
}

