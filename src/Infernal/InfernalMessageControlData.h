//%includeGuardStart {
#ifndef INFERNALMESSAGECONTROLDATA_H
#define INFERNALMESSAGECONTROLDATA_H
//%includeGuardStart } zgrdchKj1fYEx/yB5zWTtQ
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalMessageControlData.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } jT+U9xWDEpq/Hjy+c8gl5g
/*
 * $Id: InfernalMessageControlData.h,v 1.3 2003/10/04 15:32:11 southa Exp $
 * $Log: InfernalMessageControlData.h,v $
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

#include "Mushcore.h"

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
