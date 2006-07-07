//%includeGuardStart {
#ifndef MUSHGAMEVOLATILEDATA_H
#define MUSHGAMEVOLATILEDATA_H
//%includeGuardStart } L/56G+fBB2mnO8ucZ4yhVQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameVolatileData.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } zS6MRI08vU38Tp9aNbV8RQ
/*
 * $Id: MushGameVolatileData.h,v 1.6 2006/07/04 16:55:28 southa Exp $
 * $Log: MushGameVolatileData.h,v $
 * Revision 1.6  2006/07/04 16:55:28  southa
 * Ruby key handling
 *
 * Revision 1.5  2006/06/01 15:39:27  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/07/11 16:37:46  southa
 * Uplink control work
 *
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

#include "API/mushMushRuby.h"

//:generate virtual standard ostream xml1
class MushGameVolatileData : public MushcoreVirtualObject
{
public:
    enum tGameMode
    {
        kGameModeInvalid,
        kGameModeNone,
        kGameModeMenu,
        kGameModeGame,
        kGameModeNext
    };
    
    MushGameVolatileData();
    virtual ~MushGameVolatileData() {}
    virtual void GroupingNameSet(const std::string& inName) {}

protected:

    
private:
    Mushware::U32 m_playerUplinkPeriodMsec; //:readwrite
    Mushware::U32 m_lastPlayerUplinkMsec; //:readwrite
    bool m_quickPlayerUplinkRequired; //:readwrite
    Mushware::tMsec m_gameMsec; //:readwrite
    Mushware::tMsec m_lastGameMsec; //:readwrite
    Mushware::tMsec m_frameMsec; //:readwrite
    Mushware::tRubyValue m_rubyGame; //:readwrite
    Mushware::U32 m_gameMode; //:readwrite

//%classPrototypes {
public:
    const Mushware::U32& PlayerUplinkPeriodMsec(void) const { return m_playerUplinkPeriodMsec; }
    void PlayerUplinkPeriodMsecSet(const Mushware::U32& inValue) { m_playerUplinkPeriodMsec=inValue; }
    const Mushware::U32& LastPlayerUplinkMsec(void) const { return m_lastPlayerUplinkMsec; }
    void LastPlayerUplinkMsecSet(const Mushware::U32& inValue) { m_lastPlayerUplinkMsec=inValue; }
    const bool& QuickPlayerUplinkRequired(void) const { return m_quickPlayerUplinkRequired; }
    void QuickPlayerUplinkRequiredSet(const bool& inValue) { m_quickPlayerUplinkRequired=inValue; }
    const Mushware::tMsec& GameMsec(void) const { return m_gameMsec; }
    void GameMsecSet(const Mushware::tMsec& inValue) { m_gameMsec=inValue; }
    const Mushware::tMsec& LastGameMsec(void) const { return m_lastGameMsec; }
    void LastGameMsecSet(const Mushware::tMsec& inValue) { m_lastGameMsec=inValue; }
    const Mushware::tMsec& FrameMsec(void) const { return m_frameMsec; }
    void FrameMsecSet(const Mushware::tMsec& inValue) { m_frameMsec=inValue; }
    const Mushware::tRubyValue& RubyGame(void) const { return m_rubyGame; }
    void RubyGameSet(const Mushware::tRubyValue& inValue) { m_rubyGame=inValue; }
    const Mushware::U32& GameMode(void) const { return m_gameMode; }
    void GameModeSet(const Mushware::U32& inValue) { m_gameMode=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Vr1DmM/6WPvuORMLDORJVA
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
