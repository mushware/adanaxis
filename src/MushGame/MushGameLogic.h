//%includeGuardStart {
#ifndef MUSHGAMELOGIC_H
#define MUSHGAMELOGIC_H
//%includeGuardStart } rFkbHDykZZ7vaIw8O6whkg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLogic.h
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
//%Header } VWSLWDpWLWDN8N9AhLEiHQ
/*
 * $Id: MushGameLogic.h,v 1.7 2005/06/24 10:30:12 southa Exp $
 * $Log: MushGameLogic.h,v $
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
    virtual void PerFrameProcessing(void);
    virtual void DefaultMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void JobMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void PieceMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void ServerAddressSet(const std::string& inName);
    virtual void ClientAddressAdd(const std::string& inName);
    virtual void CopyAndSendToServer(const MushGameMessage& inMessage);
    virtual void AsReplyCopyAndSend(MushGameMessage& ioMessage, const MushGameMessage& inSrcMessage);
    
    virtual void ClientMailboxConsume(MushGameMailbox& inMailbox);
    virtual void ServerMailboxConsume(MushGameMailbox& inMailbox);
    virtual void ClientReceiveSequence(void);
    virtual void ServerReceiveSequence(void);
    virtual void ClientSendSequence(void);
    virtual void ServerSendSequence(void);
    virtual void ReceiveSequence(void);
    virtual void SendSequence(void);
    virtual void RenderSequence(void);
    virtual void MainSequence(void);

    virtual void ClientNewPlayerHandle(const std::string& inPlayerName);
    
    virtual MushGamePlayer *PlayerNew(const MushGameMessage *inpMessage) { return new MushGamePlayer; }
    
    virtual MushGameSaveData& SaveData(void) { return m_dataRef.Ref().SaveDataRef().WRef(); }
    virtual MushGameVolatileData& VolatileData(void) { return m_dataRef.Ref().VolatileDataRef().WRef(); }
    
    virtual MushGameHostSaveData& HostSaveData(void) { return m_hostDataRef.Ref().SaveDataRef().WRef(); }
    virtual MushGameHostVolatileData& HostVolatileData(void) { return m_hostDataRef.Ref().VolatileDataRef().WRef(); }
    
protected:

private:
    MushcoreDataRef<MushGameData> m_dataRef; //:readwrite :wref
    MushcoreDataRef<MushGameHostData> m_hostDataRef; //:readwrite :wref
    
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
