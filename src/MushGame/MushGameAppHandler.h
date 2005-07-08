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
 * $Id: MushGameAppHandler.h,v 1.1 2005/07/06 19:08:27 southa Exp $
 * $Log: MushGameAppHandler.h,v $
 * Revision 1.1  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 */

#include "MushGameStandard.h"

#include "MushGameAxisDef.h"
#include "MushGameMailbox.h"

#include "API/mushGame.h"

class MushGameAppHandler : public GameAppHandler
{
public:
    MushGameAppHandler(const std::string& inName = "");
    
    virtual void GroupingNameSet(const std::string& inName);
    virtual void AxisDefSet(const MushGameAxisDef& inAxisDef, Mushware::U32 inAxisNum);
    virtual void Idle(void);
    
protected:
    virtual void AxisFromDeviceUpdate(MushGameAxisDef& ioAxisDef, Mushware::tVal inAmount);
    virtual void AxisTicker(Mushware::tMsec inTimeslice);    
    virtual void FillAxisPipe(void);
    
private:
    std::string m_groupingName;
    std::vector<MushGameAxisDef> m_axisDefs;
    Mushware::tMsec m_lastTickerMsec;
    MushcoreDataRef<MushGameMailbox> m_controlMailboxRef; //:read
    bool m_lastAxesValid;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
