//%includeGuardStart {
#ifndef MUSHGAMELOGIC_H
#define MUSHGAMELOGIC_H
//%includeGuardStart } rFkbHDykZZ7vaIw8O6whkg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLogic.h
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
//%Header } pz9Ij69Gp+RQuOHP0yYqgg
/*
 * $Id: MushGameLogic.h,v 1.22 2006/10/04 13:35:24 southa Exp $
 * $Log: MushGameLogic.h,v $
 * Revision 1.22  2006/10/04 13:35:24  southa
 * Selective targetting
 *
 * Revision 1.21  2006/10/02 20:28:11  southa
 * Object lookup and target selection
 *
 * Revision 1.20  2006/10/02 17:25:05  southa
 * Object lookup and target selection
 *
 * Revision 1.19  2006/07/20 12:22:22  southa
 * Precache display
 *
 * Revision 1.18  2006/07/08 16:05:59  southa
 * Ruby menus and key handling
 *
 * Revision 1.17  2006/07/07 18:13:58  southa
 * Menu start and stop
 *
 * Revision 1.16  2006/07/04 16:55:27  southa
 * Ruby key handling
 *
 * Revision 1.15  2006/06/01 15:39:23  southa
 * DrawArray verification and fixes
 *
 * Revision 1.14  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 * Revision 1.13  2005/07/12 12:18:18  southa
 * Projectile work
 *
 * Revision 1.12  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.11  2005/07/11 14:48:46  southa
 * Uplink work
 *
 * Revision 1.10  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.9  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.8  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 * Revision 1.7  2005/06/24 10:30:12  southa
 * MushGame camera work
 *
 * Revision 1.6  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.5  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameStandard.h"

#include "MushGameData.h"
#include "MushGameHostData.h"
#include "MushGameHostSaveData.h"
#include "MushGameHostVolatileData.h"
#include "MushGameJob.h"
#include "MushGameMailbox.h"
#include "MushGamePiecePlayer.h"
#include "MushGameReceiver.h"
#include "MushGameSaveData.h"
#include "MushGameVolatileData.h"

//:generate virtual standard ostream xml1
class MushGameLogic : public MushGameReceiver, public MushcoreVirtualObject
{
public:
    typedef MushcoreData<MushGameJob> tJobList;
    
    virtual ~MushGameLogic() {}
    virtual void GroupingNameSet(const std::string& inName) { m_dataRef.NameSet(inName); m_hostDataRef.NameSet(inName); }

    virtual void JobListProcess(tJobList& ioList);
    virtual Mushware::U32 GameMsec(void) const;
    virtual Mushware::tMsec FrameMsec(void) const { return ConstVolatileData().FrameMsec(); }
    virtual MushGamePiece& PieceLookup(const std::string& inName) const;
    virtual void TargetPieceSearch(std::string& ioID, Mushware::tVal& ioDistSquared, const Mushware::t4Val& inPos,
                                   const std::string& inObjType,
                                   const std::string& inExcludeID) const;
    virtual std::string TargetPieceSelect(const MushMeshPosticity& inPost, const std::string& inTypes,
                                          const std::string& inExcludeID) const;
    
    virtual void PerFrameProcessing(void);
    virtual void DefaultMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void CollisionMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void JobMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void ServerPlayerMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void ServerAddressSet(const std::string& inName);
    virtual void ClientAddressAdd(const std::string& inName);
    virtual void CopyAndSendToServer(const MushGameMessage& inMessage);
    virtual void AsReplyCopyAndSend(MushGameMessage& ioMessage, const MushGameMessage& inSrcMessage);
    virtual void CopyAndBroadcast(const MushGameMessage& inMessage);
    virtual void QuickPlayerUplinkIsRequired(void) { VolatileData().QuickPlayerUplinkRequiredSet(true); }
    
    virtual void ClientMailboxConsume(MushGameMailbox& inMailbox);
    virtual void ServerMailboxConsume(MushGameMailbox& inMailbox);
    virtual void TimingSequence(void);
    virtual void ClientReceiveSequence(void);
    virtual void ServerReceiveSequence(void);
    virtual void ClientSendSequence(void);
    virtual void ServerSendSequence(void);
    virtual void ReceiveSequence(void);
    virtual void SendSequence(void);
    virtual void PlayerUplink(MushGamePiecePlayer& inPlayer);
    virtual void PlayerUplinkSequence(void);    
    virtual void UplinkSequence(void);
    virtual void PlayerMove(MushGamePiecePlayer& inPlayer);
    virtual void MoveSequence(void);
    virtual void CollideSequence(void);
    virtual void PlayerTicker(MushGamePiecePlayer& inPlayer);
    virtual void TickerSequence(void);
    virtual void CameraMove(MushGameCamera& inCamera);
    virtual void CameraSequence(void);
    virtual void MenuSequence(void);
    virtual void PreCacheSequence(void);
    virtual void RenderSequence(void);
    virtual void MainSequence(void);

    virtual bool IsMenuMode(void) const;
    virtual bool IsPreCacheMode(void) const;
    virtual bool IsGameMode(void) const;
    virtual void MenuModeEnter(void);
    virtual void GameModeEnter(void);
    virtual void QuitModeEnter(void);
    virtual void PreCacheModeEnter(void);
    virtual void PreCacheModeExit(void);
    
    virtual void ClientNewPlayerHandle(Mushware::U32 inPlayerNum);
    
    virtual MushGamePiecePlayer *PlayerNew(const MushGameMessage *inpMessage) { return new MushGamePiecePlayer; }
    
    virtual MushGameSaveData& SaveData(void) const { return m_dataRef.Ref().SaveDataRef().WRef(); }
    virtual const MushGameSaveData& ConstSaveData(void) const { return m_dataRef.Ref().SaveDataRef().Ref();; }
    virtual MushGameVolatileData& VolatileData(void) const { return m_dataRef.Ref().VolatileDataRef().WRef(); }
    virtual const MushGameVolatileData& ConstVolatileData(void) const { return m_dataRef.Ref().VolatileDataRef().Ref(); }
    
    virtual MushGameHostSaveData& HostSaveData(void) const { return m_hostDataRef.Ref().SaveDataRef().WRef(); }
    virtual MushGameHostVolatileData& HostVolatileData(void) const { return m_hostDataRef.Ref().VolatileDataRef().WRef(); }
    
    virtual void ExceptionHandle(std::exception *inpFail, const std::string& inName) const;

    const MushRubyValue& RubyLogic(void);
    
protected:
        
private:
    MushcoreDataRef<MushGameData> m_dataRef; //:readwrite :wref
    MushcoreDataRef<MushGameHostData> m_hostDataRef; //:readwrite :wref
    MushRubyValue m_rubyLogic;
    
    virtual MushRubyValue NewLogic(void);
    
//%classPrototypes {
public:
    const MushcoreDataRef<MushGameData>& DataRef(void) const { return m_dataRef; }
    void DataRefSet(const MushcoreDataRef<MushGameData>& inValue) { m_dataRef=inValue; }
    // Writable reference for m_dataRef
    MushcoreDataRef<MushGameData>& DataRefWRef(void) { return m_dataRef; }
    const MushcoreDataRef<MushGameHostData>& HostDataRef(void) const { return m_hostDataRef; }
    void HostDataRefSet(const MushcoreDataRef<MushGameHostData>& inValue) { m_hostDataRef=inValue; }
    // Writable reference for m_hostDataRef
    MushcoreDataRef<MushGameHostData>& HostDataRefWRef(void) { return m_hostDataRef; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Bfr2pEaavQy7OxUU5VS7Fg
};

inline const MushRubyValue&
MushGameLogic::RubyLogic(void)
{
    if (m_rubyLogic.IsNil())
    {
        m_rubyLogic = NewLogic();
    }
    return m_rubyLogic;
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameLogic& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } u/hXrZd6rqPQvJCDJPITcg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
