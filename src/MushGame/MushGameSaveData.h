//%includeGuardStart {
#ifndef MUSHGAMESAVEDATA_H
#define MUSHGAMESAVEDATA_H
//%includeGuardStart } 7yiKGTLNms/OxctrFNygVg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameSaveData.h
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
//%Header } yr0bn8Zl2vbNp5TNb5qaQQ
/*
 * $Id: MushGameSaveData.h,v 1.1 2005/06/16 17:25:39 southa Exp $
 * $Log: MushGameSaveData.h,v $
 * Revision 1.1  2005/06/16 17:25:39  southa
 * Client/server work
 *
 */

#include "MushGameStandard.h"

#include "MushGamePlayer.h"

//:generate virtual standard ostream xml1
class MushGameSaveData : public MushcoreVirtualObject
{
public:
    MushGameSaveData();
    
private:
    MushcoreData<MushGamePlayer> m_players; //:readwrite :wref
    Mushware::U32 m_nextPlayerID; //:readwrite :wref
    Mushware::U32 m_maxPlayersAllowed; //:readwrite
    
//%classPrototypes {
public:
    const MushcoreData<MushGamePlayer>& Players(void) const { return m_players; }
    void PlayersSet(const MushcoreData<MushGamePlayer>& inValue) { m_players=inValue; }
    // Writable reference for m_players
    MushcoreData<MushGamePlayer>& PlayersWRef(void) { return m_players; }
    const Mushware::U32& NextPlayerID(void) const { return m_nextPlayerID; }
    void NextPlayerIDSet(const Mushware::U32& inValue) { m_nextPlayerID=inValue; }
    // Writable reference for m_nextPlayerID
    Mushware::U32& NextPlayerIDWRef(void) { return m_nextPlayerID; }
    const Mushware::U32& MaxPlayersAllowed(void) const { return m_maxPlayersAllowed; }
    void MaxPlayersAllowedSet(const Mushware::U32& inValue) { m_maxPlayersAllowed=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 6LQKcu5oEU2B4jNaA6mYkA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameSaveData& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } t1GJfU09zSXc2hekGD1d9A
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
