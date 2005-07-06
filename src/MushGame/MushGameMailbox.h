//%includeGuardStart {
#ifndef MUSHGAMEMAILBOX_H
#define MUSHGAMEMAILBOX_H
//%includeGuardStart } BFwxta+0c2eXNnB5ocfSlA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMailbox.h
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
//%Header } HGOTUFiPB1QROOSnhLbE4Q
/*
 * $Id: MushGameMailbox.h,v 1.5 2005/06/23 11:58:28 southa Exp $
 * $Log: MushGameMailbox.h,v $
 * Revision 1.5  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/20 16:14:31  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:48:59  southa
 * Client/server work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"

//:generate virtual standard ostream xml1
class MushGameMailbox : public MushcoreVirtualObject
{
public:
    MushGameMailbox() : m_messageCount(0), m_messageLimit(1000) {}
    virtual ~MushGameMailbox();
    virtual void Give(MushGameMessage *iopMessage);
    virtual bool TakeIfAvailable(MushGameMessage *& iopMessage);
    virtual bool TakeIfAvailable(std::auto_ptr<MushGameMessage>& ioaMessage);
    virtual bool IsEmpty(void) { return m_deque.empty(); }
    virtual void DiscardAll(void);
    
private:
    MushcoreDataRef<MushGameAddress> m_srcAddrRef; //:xmlignore :readwrite
    std::deque<MushGameMessage *> m_deque;
    Mushware::U32 m_messageCount; //:readwrite
    Mushware::U32 m_messageLimit; //:readwrite
    
//%classPrototypes {
public:
    const MushcoreDataRef<MushGameAddress>& SrcAddrRef(void) const { return m_srcAddrRef; }
    void SrcAddrRefSet(const MushcoreDataRef<MushGameAddress>& inValue) { m_srcAddrRef=inValue; }
    const Mushware::U32& MessageCount(void) const { return m_messageCount; }
    void MessageCountSet(const Mushware::U32& inValue) { m_messageCount=inValue; }
    const Mushware::U32& MessageLimit(void) const { return m_messageLimit; }
    void MessageLimitSet(const Mushware::U32& inValue) { m_messageLimit=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Jl57Dk8ApazrafbogACMNg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMailbox& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } CJpY1w5JjdGfBhBU2h74gg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
