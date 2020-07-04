//%includeGuardStart {
#ifndef INFERNALMESSAGECONTROLDATA_H
#define INFERNALMESSAGECONTROLDATA_H
//%includeGuardStart } zgrdchKj1fYEx/yB5zWTtQ
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalMessageControlData.h
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
//%Header } rpx4BQ7IeKsUiNiBTiuiyg
/*
 * $Id: InfernalMessageControlData.h,v 1.7 2006/06/01 15:39:04 southa Exp $
 * $Log: InfernalMessageControlData.h,v $
 * Revision 1.7  2006/06/01 15:39:04  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/06 20:46:50  southa
 * Build fixes
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
 * Revision 1.7  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:08:48  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/11 13:03:14  southa
 * Use Mushcore header
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

#include "mushMushcore.h"

#include "mushGame.h"

class MustlData;

class InfernalMessageControlData
{
public:
    enum
    {
        kEntryLimit=32
    };

    struct DataEntry
    {
        GameControlFrameDef frameDef;
        Mushware::U8 frameOffset;
    };

    Mushware::U32 StartFrameGet(void) const { return m_startFrame; }
    void StartFrameSet(Mushware::U32 inFrame) { m_startFrame = inFrame; }
    const DataEntry& DataEntryGet(Mushware::U32 inEntryNum) const;
    Mushware::U32 DataSizeGet(void) const { return m_data.size(); }
    void DataEntryPush(Mushware::U32 inFrameOffset, const GameControlFrameDef& inDef);
    void Pack(MustlData& ioData) const;
    void Unpack(MustlData& ioData);
    
private:
    Mushware::U32 m_startFrame;
    std::vector<DataEntry> m_data;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
