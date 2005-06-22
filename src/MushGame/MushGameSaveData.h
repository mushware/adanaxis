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
 * $Id: MushGameSaveData.h,v 1.4 2005/06/21 15:57:48 southa Exp $
 * $Log: MushGameSaveData.h,v $
 * Revision 1.4  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.3  2005/06/21 13:10:52  southa
 * MushGame work
 *
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 17:25:39  southa
 * Client/server work
 *
 */

#include "MushGameStandard.h"

#include "MushGameJob.h"
#include "MushGameMailbox.h"
#include "MushGamePlayer.h"

#include "MushGameClient.h"

//:generate virtual standard ostream xml1
class MushGameSaveData : public MushcoreVirtualObject
{
public:
    MushGameSaveData();
    virtual void GroupingNameSet(const std::string& inName) { m_clientRef.NameSet(inName); }
    
private:
    MushcoreData<MushGamePlayer> m_players; //:readwrite :wref
    Mushware::U32 m_nextPlayerID; //:readwrite :wref
    Mushware::U32 m_maxPlayersAllowed; //:readwrite
    MushcoreData<MushGameJob> m_jobList; //:readwrite :wref
    MushGameMailbox m_toServerMailbox; //:readwrite :wref
    MushcoreDataRef<MushGameClient> m_clientRef;
    MushcoreDataRef<MushGameAddress> m_serverAddrRef; //:readwrite :wref
    
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
    const MushcoreData<MushGameJob>& JobList(void) const { return m_jobList; }
    void JobListSet(const MushcoreData<MushGameJob>& inValue) { m_jobList=inValue; }
    // Writable reference for m_jobList
    MushcoreData<MushGameJob>& JobListWRef(void) { return m_jobList; }
    const MushGameMailbox& ToServerMailbox(void) const { return m_toServerMailbox; }
    void ToServerMailboxSet(const MushGameMailbox& inValue) { m_toServerMailbox=inValue; }
    // Writable reference for m_toServerMailbox
    MushGameMailbox& ToServerMailboxWRef(void) { return m_toServerMailbox; }
    const MushcoreDataRef<MushGameAddress>& ServerAddrRef(void) const { return m_serverAddrRef; }
    void ServerAddrRefSet(const MushcoreDataRef<MushGameAddress>& inValue) { m_serverAddrRef=inValue; }
    // Writable reference for m_serverAddrRef
    MushcoreDataRef<MushGameAddress>& ServerAddrRefWRef(void) { return m_serverAddrRef; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } EflSsquI6PXkQ40RwhyMQQ
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
