/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "GameControlFrameDef.h"

class MediaNetData;

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

    void StartFrameSet(U32 inFrame) { m_startFrame = inFrame; }
    void DataEntryPush(U32 inFrameOffset, const GameControlFrameDef& inDef);
    void Pack(MediaNetData& ioData) const;
    void Unpack(MediaNetData& ioData);
    
private:
    U32 m_startFrame;
    vector<DataEntry> m_data;
};

