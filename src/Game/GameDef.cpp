/*
 * $Id: GameDef.cpp,v 1.3 2002/11/23 15:23:33 southa Exp $
 * $Log: GameDef.cpp,v $
 * Revision 1.3  2002/11/23 15:23:33  southa
 * Fixed network orders for win32
 *
 * Revision 1.2  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.1  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
 */

#include "GameDef.h"

#include "GameApphandler.h"

#include "mushPlatform.h"

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
    m_serverStation.PortSetHostOrder(inPort);
    m_type=kTypeClient;
};

void
GameDef::Ticker(void)
{
    if (m_type == kTypeClient)
    {
        MediaNetLink *netLink=NULL;
        if (MediaNetUtils::FindLinkToStation(netLink, m_serverStation.NameGet(), PlatformNet::HostToNetworkOrderU16(m_serverStation.PortGet())))
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
        MediaNetLog::Instance().NetLog() << "Link creation failed: " << e.what() << endl;
    }
}
