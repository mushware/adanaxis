/*
 * $Id: GameDef.h,v 1.2 2002/11/23 17:23:44 southa Exp $
 * $Log: GameDef.h,v $
 * Revision 1.2  2002/11/23 17:23:44  southa
 * Sleep in setup
 *
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
    virtual ~GameDef() {}
    virtual void Ticker(void) = 0;
    virtual void WebPrint(ostream& ioOut) const = 0;
    
protected:
    void CreateNewLink(const GameStationDef& inStation);
    
private:
};

class GameDefClient : public GameDef
{
public:
    GameDefClient();
    virtual void Ticker(void);
    virtual void WebPrint(ostream& ioOut) const;
    
    void JoinGame(const string& inServer, U32 inPort);

private:
    enum
    {
        kLinkSetupMsec=7000
    };
    U32 m_lastLinkMsec;
    U32 m_currentMsec;
    GameStationDef m_serverStation;
};

class GameDefServer : public GameDef
{
public:
    GameDefServer();
    virtual void Ticker(void);
    virtual void WebPrint(ostream& ioOut) const;
    
    void HostGame(const string& inContract, U32 inPlayerLimit);

private:
    string m_contractName;
    U32 m_playerLimit;
    vector<string> m_clientStation;
};