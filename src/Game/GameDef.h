/*
 * $Id: GameDef.h,v 1.1 2002/11/21 18:06:17 southa Exp $
 * $Log: GameDef.h,v $
 * Revision 1.1  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
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
        kLinkSetupMsec=7000
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
