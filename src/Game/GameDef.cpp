/*
 * $Id$
 * $Log$
 */

#include "GameDef.h"

#include "GameApphandler.h"

auto_ptr< CoreData<GameDef> > CoreData<GameDef>::m_instance;

GameDef::GameDef() :
    m_type(kTypeNone),
    m_lastLinkMsec(0)
{
}

void
GameDef::JoinGame(const string& inServer, U32 inPort)
{
    m_serverStation=GameStationDef();
    m_serverStation.NameSet(inServer);
    m_serverStation.PortSet(inPort);
    m_type=kTypeClient;
};

void
GameDef::Ticker(void)
{
    if (m_type=kTypeClient)
    {
        MediaNetLink *netLink=NULL;
        if (MediaNetUtils::FindLinkToStation(netLink, m_serverStation.NameGet(), m_serverStation.PortGet()))
        {
            COREASSERT(netLink != NULL);
        }
        else
        {
            GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
            m_currentMsec=gameAppHandler.MillisecondsGet();

            if (m_lastLinkMsec + kLinkSetupMsec < m_currentMsec)
            {
                CreateNewLink(m_serverStation);
                m_lastLinkMsec = m_currentMsec;
            }
        }
    }
}

void
GameDef::CreateNewLink(const GameStationDef& inStation)
{
    try
    {
        CoreData<MediaNetLink>::Instance().DataGive(inStation.NameGet()+"client", new MediaNetLink(inStation.NameGet(), inStation.PortGet()));
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().Log() << "Link creation failed: " << e.what() << endl;
    }
}
