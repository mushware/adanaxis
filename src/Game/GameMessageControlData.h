/*
 * $Id: GameMessageControlData.h,v 1.2 2002/12/09 23:59:58 southa Exp $
 * $Log: GameMessageControlData.h,v $
 * Revision 1.2  2002/12/09 23:59:58  southa
 * Network control
 *
 * Revision 1.1  2002/12/06 17:38:00  southa
 * ControlData message unpacking
 *
 */

#include "mushCore.h"

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
        U8 frameOffset;
    };

    U32 StartFrameGet(void) const { return m_startFrame; }
    void StartFrameSet(U32 inFrame) { m_startFrame = inFrame; }
    const DataEntry& DataEntryGet(U32 inEntryNum) const;
    U32 DataSizeGet(void) const { return m_data.size(); }
    void DataEntryPush(U32 inFrameOffset, const GameControlFrameDef& inDef);
    void Pack(MustlData& ioData) const;
    void Unpack(MustlData& ioData);
    
private:
    U32 m_startFrame;
    vector<DataEntry> m_data;
};
