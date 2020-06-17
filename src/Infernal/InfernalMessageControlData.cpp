//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalMessageControlData.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } vyUd/q4edcBYeSqIIcZGMw
/*
 * $Id: InfernalMessageControlData.cpp,v 1.7 2006/06/01 20:12:58 southa Exp $
 * $Log: InfernalMessageControlData.cpp,v $
 * Revision 1.7  2006/06/01 20:12:58  southa
 * Initial texture caching
 *
 * Revision 1.6  2006/06/01 15:39:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/02 21:13:08  southa
 * Source conditioning
 *
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
#include "mushMustl.h"

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

