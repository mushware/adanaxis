/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "GameStationDef.h"

class GameDef
{
public:
    GameDef();
    void JoinGame(const string& inServer, U32 inPort);
    void Ticker(void);

protected:
    void CreateNewLink(const GameStationDef& inStation);
    
private:
    enum
    {
        kLinkSetupMsec=2000
    };
    enum tType
    {
        kTypeInvalid,
        kTypeNone,
        kTypeClient,
        kTypeServer
    };

    tType m_type;
    GameStationDef m_serverStation;
    U32 m_lastLinkMsec;
    U32 m_currentMsec;
    vector<string> m_clientStation;
};
