/*
 * $Id: GameDefClient.h,v 1.1 2002/11/24 23:54:36 southa Exp $
 * $Log: GameDefClient.h,v $
 * Revision 1.1  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 */

#include "mushCore.h"

#include "GameDef.h"
#include "GameStationDef.h"

class GameDefClient : public GameDef
{
public:
    GameDefClient();
    virtual void Ticker(void);
    virtual void WebPrint(ostream& ioOut) const;

    void JoinGame(const string& inServer, U32 inPort);

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
    GameStationDef m_serverStation;
};
