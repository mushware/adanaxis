#ifndef GAMEDEFSERVER_H
#define GAMEDEFSERVER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameDefServer.h,v 1.8 2002/12/12 14:00:39 southa Exp $
 * $Log: GameDefServer.h,v $
 * Revision 1.8  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.7  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.6  2002/11/28 18:05:35  southa
 * Print link ages
 *
 * Revision 1.5  2002/11/28 15:14:14  southa
 * Multiplayer setup timing
 *
 * Revision 1.4  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.3  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.2  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.1  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 */

#include "mushCore.h"

#include "GameDef.h"

#include "mushMedia.h"

class GameDefClient;

class GameDefServer : public GameDef
{
public:
    GameDefServer(const string& inName);
    virtual void Ticker(const string& inName);
    virtual void WebPrint(std::ostream& ioOut) const;

    void HostGame(const string& inContract, Mushware::U32 inPlayerLimit);
    void Kill(void);
    bool IsDead(void) const { return m_killed; }
    
    virtual void Pickle(std::ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;

    const string& ServerMessageGet(void) const { return m_serverMessage; }
    void ServerMessageSet(const string& inMessage) { m_serverMessage = inMessage; }
    void AddressSet(MustlAddress& inAddress) { m_netAddress = inAddress; }
    const MustlAddress& AddressGet(void) const { return m_netAddress; }

    void UpdateClient(GameDefClient& inClient);
    
protected:
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void NullHandler(CoreXML& inXML);
    void HandleDefServerEnd(CoreXML& inXML);
    void HandleMessageEnd(CoreXML& inXML);
    void HandleContractEnd(CoreXML& inXML);
    void HandlePlayerCountEnd(CoreXML& inXML);
    void HandlePlayerLimitEnd(CoreXML& inXML);
    
    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<string, void (GameDefServer::*)(CoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    Mushware::U32 m_baseThreaded;

    enum
    {
        kUpdateMsec=5000
    };

    void UpdateClients(void);
    
    string m_serverMessage;
    string m_contractName;
    Mushware::U32 m_playerCount;
    Mushware::U32 m_playerLimit;
    Mushware::U32 m_lastUpdateMsec;
    Mushware::U32 m_currentMsec;
    MustlAddress m_netAddress;
    bool m_killed;
};
#endif
