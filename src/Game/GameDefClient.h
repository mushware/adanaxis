/*
 * $Id: GameDefClient.h,v 1.4 2002/11/28 11:10:29 southa Exp $
 * $Log: GameDefClient.h,v $
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

#include "mushCore.h"

#include "GameDef.h"

#include "mushMedia.h"

class GameDefClient : public GameDef
{
public:
    explicit GameDefClient(const string& inName);
    virtual void Ticker(void);
    virtual void WebPrint(ostream& ioOut) const;

    void JoinGame(const string& inServer, U32 inPort);
    void AddressSet(MediaNetAddress& inAddress) { m_netAddress = inAddress; }
    const MediaNetAddress& AddressGet(void) const { return m_netAddress; }
    void Kill(void);
    bool IsDead(void) const { return m_killed; }
    
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;

protected:
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void NullHandler(CoreXML& inXML);
    void HandleGameDefClientEnd(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef map<string, void (GameDefClient::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    U32 m_baseThreaded;
    
    enum
    {
        kLinkSetupMsec=7000,
        kRegistrationMsec=10000
    };

    U32 m_lastLinkMsec;
    U32 m_lastRegistrationMsec;
    U32 m_currentMsec;
    string m_serverName;
    MediaNetAddress m_netAddress;
    bool m_killed;
    bool m_joined;
};
