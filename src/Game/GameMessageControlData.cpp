/*
 * $Id$
 * $Log$
 */

#include "GameMessageControlData.h"

#include "GameProtocol.h"

#include "mushMedia.h"

void
GameMessageControlData::DataEntryPush(U32 inFrameOffset, const GameControlFrameDef& inDef)
{
    m_data.push_back(DataEntry());
    m_data.back().frameOffset = static_cast<U8>(inFrameOffset);
    m_data.back().frameDef = inDef;    
}

void
GameMessageControlData::Pack(MediaNetData& ioData) const
{
    MediaNetProtocol::LongAppMessageHeaderCreate(ioData, GameProtocol::kMessageTypeControlData);
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
    MediaNetProtocol::LongAppMessageFinish(ioData);
}

void
GameMessageControlData::Unpack(MediaNetData& ioData)
{
    m_startFrame = ioData.BytePop() << 8;
    m_startFrame |= ioData.BytePop();

    U32 messageSize = ioData.MessageSizeGet();
    U32 numEntries = messageSize / 4;

    if (messageSize % 4 != 0 || numEntries > kEntryLimit)
    {
        MediaNetLog::Instance().NetLog() << "Bad message size for ControlDataMessage (" << messageSize << ")" << endl;
        numEntries=0;
    }

    m_data.resize(numEntries);

    for (U32 i=0; i<numEntries; ++i)
    {
        m_data[i].frameOffset = ioData.BytePop();
        m_data[i].frameDef.mouseDeltaX = ioData.BytePop();
        m_data[i].frameDef.mouseDeltaY = ioData.BytePop();
        m_data[i].frameDef.keyState = ioData.BytePop();
    }
}

