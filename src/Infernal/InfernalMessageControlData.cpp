//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalMessageControlData.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /j60vOF10q7Or/NWVnZRsA
/*
 * $Id: InfernalMessageControlData.cpp,v 1.3 2003/10/04 15:32:11 southa Exp $
 * $Log: InfernalMessageControlData.cpp,v $
 * Revision 1.3  2003/10/04 15:32:11  southa
 * Module split
 *
 * Revision 1.2  2003/10/04 12:44:35  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:06  southa
 * File renaming
 *
 * Revision 1.10  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:08:48  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/20 10:45:26  southa
 * Singleton tidying
 *
 * Revision 1.7  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.6  2003/01/12 17:32:55  southa
 * Mushcore work
 *
 * Revision 1.5  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.4  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.2  2002/12/09 23:59:58  southa
 * Network control
 *
 * Revision 1.1  2002/12/06 17:38:00  southa
 * ControlData message unpacking
 *
 */

#include "InfernalMessageControlData.h"

#include "InfernalSTL.h"

#include "mushGame.h"
#include "mushMedia.h"

using namespace Mushware;
using namespace std;

const InfernalMessageControlData::DataEntry&
InfernalMessageControlData::DataEntryGet(U32 inEntryNum) const
{
    MUSHCOREASSERT(inEntryNum < m_data.size());
    return m_data[inEntryNum];
}

void
InfernalMessageControlData::DataEntryPush(U32 inFrameOffset, const GameControlFrameDef& inDef)
{
    m_data.push_back(DataEntry());
    m_data.back().frameOffset = static_cast<U8>(inFrameOffset);
    m_data.back().frameDef = inDef;    
}

void
InfernalMessageControlData::Pack(MustlData& ioData) const
{
    MustlProtocol::LongAppMessageHeaderCreate(ioData, GameProtocol::kMessageTypeControlData);
    ioData.PrepareForWrite();
    ioData.BytePush(m_startFrame >> 8);
    ioData.BytePush(m_startFrame);
    U32 size = m_data.size();
    MUSHCOREASSERT(size <= kEntryLimit);
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
InfernalMessageControlData::Unpack(MustlData& ioData)
{
    m_startFrame = ioData.MessageBytePop() << 8;
    m_startFrame |= ioData.MessageBytePop();

    U32 messageSize = ioData.MessageSizeGet();
    U32 numEntries = messageSize / 4;

    if (messageSize % 4 != 0 || numEntries > kEntryLimit)
    {
        MustlLog::Sgl().NetLog() << "Bad message size for ControlDataMessage (" << messageSize << ")" << endl;
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

