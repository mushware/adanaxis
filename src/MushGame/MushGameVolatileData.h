//%includeGuardStart {
#ifndef MUSHGAMEVOLATILEDATA_H
#define MUSHGAMEVOLATILEDATA_H
//%includeGuardStart } L/56G+fBB2mnO8ucZ4yhVQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameVolatileData.h
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
//%Header } ciSqgHK3xIZ+HlSfS3hpnA
/*
 * $Id: MushGameVolatileData.h,v 1.3 2005/07/11 14:48:46 southa Exp $
 * $Log: MushGameVolatileData.h,v $
 * Revision 1.3  2005/07/11 14:48:46  southa
 * Uplink work
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:52  southa
 * MushGame work
 *
 */

#include "MushGameStandard.h"

//:generate virtual standard ostream xml1
class MushGameVolatileData : public MushcoreVirtualObject
{
public:
    MushGameVolatileData();
    virtual ~MushGameVolatileData() {}
    virtual void GroupingNameSet(const std::string& inName) {}

private:
    Mushware::U32 m_playerUplinkPeriodMsec; //:readwrite
    Mushware::U32 m_lastPlayerUplinkMsec; //:readwrite
    bool m_quickPlayerUplinkRequired; //:readwrite
    Mushware::tMsec m_frameMsec; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::U32& PlayerUplinkPeriodMsec(void) const { return m_playerUplinkPeriodMsec; }
    void PlayerUplinkPeriodMsecSet(const Mushware::U32& inValue) { m_playerUplinkPeriodMsec=inValue; }
    const Mushware::U32& LastPlayerUplinkMsec(void) const { return m_lastPlayerUplinkMsec; }
    void LastPlayerUplinkMsecSet(const Mushware::U32& inValue) { m_lastPlayerUplinkMsec=inValue; }
    const bool& QuickPlayerUplinkRequired(void) const { return m_quickPlayerUplinkRequired; }
    void QuickPlayerUplinkRequiredSet(const bool& inValue) { m_quickPlayerUplinkRequired=inValue; }
    const Mushware::tMsec& FrameMsec(void) const { return m_frameMsec; }
    void FrameMsecSet(const Mushware::tMsec& inValue) { m_frameMsec=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 8bjioYlBxf7LekBf2t2TlA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameVolatileData& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } lBPzFyiUXK878tvfmNudfg

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
