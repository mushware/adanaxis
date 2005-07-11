//%includeGuardStart {
#ifndef MUSHGAMEMESSAGECONTROLINFO_H
#define MUSHGAMEMESSAGECONTROLINFO_H
//%includeGuardStart } gCGkj9mJmJXi0VgLnk9jXQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageControlInfo.h
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
//%Header } 5Ugw6aV4AgXqjsY6ZzybrA
/*
 * $Id: MushGameMessageControlInfo.h,v 1.1 2005/07/06 19:08:27 southa Exp $
 * $Log: MushGameMessageControlInfo.h,v $
 * Revision 1.1  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"

//:xml1base MushGameMessage
//:generate virtual standard ostream xml1
class MushGameMessageControlInfo : public MushGameMessage
{
public:
    typedef std::pair<Mushware::U32, Mushware::tVal> tAxisEvent;
    typedef std::pair<Mushware::U32, bool> tKeyEvent;
    
    explicit MushGameMessageControlInfo(const std::string& inID = "") : MushGameMessage(inID) {}
    virtual ~MushGameMessageControlInfo() {}
    
private:
    Mushware::tMsec m_timestamp; //:readwrite
    std::vector<tAxisEvent> m_axisEvents; //:read :wref
    std::vector<tKeyEvent> m_keyEvents; //:read :wref
//%classPrototypes {
public:
    const Mushware::tMsec& Timestamp(void) const { return m_timestamp; }
    void TimestampSet(const Mushware::tMsec& inValue) { m_timestamp=inValue; }
    const std::vector<tAxisEvent>& AxisEvents(void) const { return m_axisEvents; }
    // Writable reference for m_axisEvents
    std::vector<tAxisEvent>& AxisEventsWRef(void) { return m_axisEvents; }
    const std::vector<tKeyEvent>& KeyEvents(void) const { return m_keyEvents; }
    // Writable reference for m_keyEvents
    std::vector<tKeyEvent>& KeyEventsWRef(void) { return m_keyEvents; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } PkvSklsOzytLUcmkPGKkJA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessageControlInfo& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } mMVFEAYvgk8lbOhsC+U+2g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
