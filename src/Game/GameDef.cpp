/*
 * $Id: GameDef.cpp,v 1.4 2002/11/23 17:23:44 southa Exp $
 * $Log: GameDef.cpp,v $
 * Revision 1.4  2002/11/23 17:23:44  southa
 * Sleep in setup
 *
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

GameDef::GameDef()
{
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

// -----

GameDefClient::GameDefClient() :
    m_lastLinkMsec(0)
{
}

void
GameDefClient::JoinGame(const string& inServer, U32 inPort)
{
    m_serverStation=GameStationDef();
    m_serverStation.NameSet(inServer);
    m_serverStation.PortSetHostOrder(inPort);
}

void
GameDefClient::Ticker(void)
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

void
GameDefClient::WebPrint(ostream& ioOut) const
{
    ioOut << "<table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;
    ioOut << "<tr>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Server</font></td>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Port</font></td>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Status</font></td>";
    ioOut << "</tr><tr>";
    ioOut << "<td>" << MediaNetUtils::MakeWebSafe(m_serverStation.NameGet()) << "</td>";
    ioOut << "<td>" << m_serverStation.PortGet() << "</td>";
    ioOut << "<td><font class=\"bggreen\">" << "GO" << "</font></td>";
    ioOut << "</tr></table>" << endl;
}

// -----

GameDefServer::GameDefServer()
{
}

void
GameDefServer::HostGame(const string& inContract, U32 inPlayerLimit)
{
    m_contractName = inContract;
    m_playerLimit = inPlayerLimit;
}

void
GameDefServer::Ticker(void)
{
}

void
GameDefServer::WebPrint(ostream& ioOut) const
{
    ioOut << "<table width=\"100%\" class=\"bglightred\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\">" << endl;
    ioOut << "<tr>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Contract Name</font></td>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Player Limit</font></td>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Status</font></td>";
    ioOut << "</tr><tr>";
    ioOut << "<td>" << MediaNetUtils::MakeWebSafe(m_contractName) << "</td>";
    ioOut << "<td>" << m_playerLimit << "</td>";
    ioOut << "<td><font class=\"bggreen\">" << "GO" << "</font></td>";
    ioOut << "</tr></table>" << endl;

}

