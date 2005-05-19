//%includeGuardStart {
#ifndef INFERNALMESSAGECONTROLDATA_H
#define INFERNALMESSAGECONTROLDATA_H
//%includeGuardStart } zgrdchKj1fYEx/yB5zWTtQ
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalMessageControlData.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } EkMJ3hEpF9oxr46d8+wo/w
/*
 * $Id: InfernalMessageControlData.h,v 1.5 2004/01/06 20:46:50 southa Exp $
 * $Log: InfernalMessageControlData.h,v $
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
