//%includeGuardStart {
#ifndef GAMEDEFCLIENT_H
#define GAMEDEFCLIENT_H
//%includeGuardStart } UROfZ65pgd/ScBeU8C/Rrw
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameDefClient.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } DM7BwhgUOa9BxJv/mO4rWA
/*
 * $Id: GameDefClient.h,v 1.18 2003/08/21 23:08:42 southa Exp $
 * $Log: GameDefClient.h,v $
 * Revision 1.18  2003/08/21 23:08:42  southa
 * Fixed file headers
 *
 * Revision 1.17  2003/02/05 17:06:36  southa
 * Build fixes
 *
 * Revision 1.16  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.15  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.14  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.13  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.12  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.11  2002/12/09 23:59:58  southa
 * Network control
 *
 * Revision 1.10  2002/12/07 18:32:14  southa
 * Network ID stuff
 *
 * Revision 1.9  2002/12/05 23:52:51  southa
 * Network management and status
 *
 * Revision 1.8  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.7  2002/11/28 16:19:25  southa
 * Fix delete object messaging
 *
 * Revision 1.6  2002/11/28 15:14:14  southa
 * Multiplayer setup timing
 *
 * Revision 1.5  2002/11/28 12:05:45  southa
 * Server name work
 *
 * Revision 1.4  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.3  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.2  2002/11/25 18:02:57  southa
 * Mushware ID work
 *
 * Revision 1.1  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 */

#include "Mushcore.h"

#include "GameDef.h"
#include "GamePiecePlayer.h"

#include "mushMedia.h"

class GameDefClient : public GameDef
{
public:
    explicit GameDefClient(const std::string& inName);
    virtual void Ticker(const std::string& inName);
    virtual void WebPrint(std::ostream& ioOut) const;
    
    void JoinGame(const std::string& inServer, Mushware::U32 inPort);
    void AddressSet(MustlAddress& inAddress) { m_netAddress = inAddress; }
    void PlayerNameSet(const std::string& inPlayerName) { m_playerRef.NameSet(inPlayerName); }
    const MustlAddress& AddressGet(void) const { return m_netAddress; }
    const MushcoreDataRef<GamePiecePlayer>& PlayerRefGet(void) const { return m_playerRef; }
    
    void Kill(void);
    bool IsDead(void) const { return m_killed; }
    void UpdateStatus(void);
    void ReliableSendToServer(MustlData& ioData);
    void FastSendToServer(MustlData& ioData);
    
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
    static void WebHeaderPrint(std::ostream& ioOut);
    
protected:
    void UpdateServer(void);
        
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void NullHandler(MushcoreXML& inXML);
    void HandleGameDefClientEnd(MushcoreXML& inXML);
    void HandleULBytesEnd(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<std::string, void (GameDefClient::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    Mushware::U32 m_baseThreaded;
    
    enum
    {
        kRegistrationMsec=10000,
        kServerTimeoutMsec=5000,
        kNumSetupModeLinks=1,
        kNumGameModeLinks=2,
        kMaxLinks=2
    };

    Mushware::U32 m_lastLinkMsec;
    Mushware::U32 m_lastRegistrationMsec;
    Mushware::U32 m_currentMsec;
    std::string m_serverName;
    MustlAddress m_netAddress;
    std::vector< MushcoreDataRef<MustlLink> > m_netLinks;
    Mushware::U32 m_lastLinkNum;
    Mushware::U32 m_numLinks;
    Mushware::U32 m_uplinkBandwidth;
    MushcoreDataRef<GamePiecePlayer> m_playerRef;
    bool m_killed;
    bool m_joined;
    bool m_linkGood;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
