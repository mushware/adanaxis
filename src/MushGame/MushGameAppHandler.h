//%includeGuardStart {
#ifndef MUSHGAMEAPPHANDLER_H
#define MUSHGAMEAPPHANDLER_H
//%includeGuardStart } 7ZwYn7TuuYmYE/eLrNwCTw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAppHandler.h
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
//%Header } JEoS3kjwIi/5WzNfzKQqBA
/*
 * $Id: MushGameAppHandler.h,v 1.3 2005/07/11 16:37:46 southa Exp $
 * $Log: MushGameAppHandler.h,v $
 * Revision 1.3  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.2  2005/07/08 12:07:07  southa
 * MushGaem control work
 *
 * Revision 1.1  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 */

#include "MushGameStandard.h"

#include "MushGameAxisDef.h"
#include "MushGameKeyDef.h"
#include "MushGameMailbox.h"

#include "API/mushGame.h"

//:generate
class MushGameAppHandler : public GameAppHandler
{
public:
    MushGameAppHandler(const std::string& inName = "");
    
    virtual void GroupingNameSet(const std::string& inName);
    virtual void AxisDefSet(const MushGameAxisDef& inAxisDef, Mushware::U32 inAxisNum);
    virtual void KeyDefSet(const MushGameKeyDef& inKeyDef, Mushware::U32 inKeyNum);
    virtual void Idle(void);
    
protected:
    virtual void AxisFromDeviceUpdate(MushGameAxisDef& ioAxisDef, Mushware::tVal inAmount);
    virtual void AxisTicker(Mushware::tMsec inTimeslice);    
    virtual void KeyTicker(Mushware::tMsec inTimeslice);    
    virtual void FillControlPipe(void);
    
private:
    std::string m_groupingName;
    std::vector<MushGameAxisDef> m_axisDefs;
    std::vector<MushGameKeyDef> m_keyDefs;
    Mushware::tMsec m_lastTickerMsec;
    MushcoreDataRef<MushGameMailbox> m_controlMailboxRef; //:read
    bool m_lastAxesValid;
    std::string m_axisNames; //:read
//%classPrototypes {
public:
    const MushcoreDataRef<MushGameMailbox>& ControlMailboxRef(void) const { return m_controlMailboxRef; }
    const std::string& AxisNames(void) const { return m_axisNames; }
//%classPrototypes } qagyUqz+a66MkXxr8gLlQA
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
