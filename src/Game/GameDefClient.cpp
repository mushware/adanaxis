/*
 * $Id: GameDef.cpp,v 1.6 2002/11/24 23:18:16 southa Exp $
 * $Log: GameDef.cpp,v $
 * Revision 1.6  2002/11/24 23:18:16  southa
 * Added type name accessor to CorePickle
 *
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

#include "GameDefClient.h"

#include "GameAppHandler.h"
#include "GameProtocol.h"

#include "mushPlatform.h"

GameDefClient::GameDefClient() :
m_lastLinkMsec(0),
m_lastRegistrationMsec(0)
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
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
    m_currentMsec=gameAppHandler.MillisecondsGet();

    MediaNetLink *netLink=NULL;
    if (MediaNetUtils::FindLinkToStation(netLink, m_serverStation.NameGet(), PlatformNet::HostToNetworkOrderU16(m_serverStation.PortGet())))
    {
        COREASSERT(netLink != NULL);
        if (m_lastRegistrationMsec + kRegistrationMsec < m_currentMsec)
        {
GameProtocol::SendObject(*netLink, *this, "client-ghost");
            m_lastRegistrationMsec = m_currentMsec;
        }
    }
    else
    {
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

void
GameDefClient::NullHandler(CoreXML& inXML)
{
}

void
GameDefClient::HandleDefClientEnd(CoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameDefClient::Pickle(ostream& inOut, const string& inPrefix="") const
{
    GameDef::Pickle(inOut, inPrefix);
    inOut << inPrefix << "<!-- Incomplete -->" << endl;
}

void
GameDefClient::Unpickle(CoreXML& inXML)
{
    GameDef::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_endTable[kPickleData]["defclient"] = &GameDefClient::HandleDefClientEnd;
    m_pickleState=kPickleData;
    inXML.ParseStream(*this);
}

void
GameDefClient::XMLStartHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        if (m_pickleState == kPickleData)
        {
GameDef::XMLStartHandler(inXML);
            m_pickleState=kPickleWithinBase;
            ++m_baseThreaded;
        }
        else
        {
            ostringstream message;
            message << "Unexpected tag <" << inXML.TopTag() << "> in DefClient.  Potential matches are";
ElementFunctionMap::iterator p = m_startTable[m_pickleState].begin();
            while (p != m_startTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GameDefClient::XMLEndHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        if (m_pickleState == kPickleWithinBase)
        {
GameDef::XMLEndHandler(inXML);
            --m_baseThreaded;
            if (m_baseThreaded == 0)
            {
                m_pickleState=kPickleData;
            }
        }
        else
        {
            ostringstream message;
            message << "Unexpected end of tag </" << inXML.TopTag() << "> in DefClient.  Potential matches are";
ElementFunctionMap::iterator p = m_endTable[m_pickleState].begin();
            while (p != m_endTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GameDefClient::XMLDataHandler(CoreXML& inXML)
{
}

char *
GameDefClient::TypeNameGet(void) const
{
    return "gamedefclient";
}

