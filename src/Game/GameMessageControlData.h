#ifndef GAMEMESSAGECONTROLDATA_H
#define GAMEMESSAGECONTROLDATA_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameMessageControlData.h,v 1.5 2003/01/11 13:03:14 southa Exp $
 * $Log: GameMessageControlData.h,v $
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

#include "Mushcore.h"

#include "GameControlFrameDef.h"

class MustlData;

class GameMessageControlData
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
#endif
