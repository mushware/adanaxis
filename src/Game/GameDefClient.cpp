/*
 * $Id: GameDefClient.cpp,v 1.12 2002/11/28 18:05:35 southa Exp $
 * $Log: GameDefClient.cpp,v $
 * Revision 1.12  2002/11/28 18:05:35  southa
 * Print link ages
 *
 * Revision 1.11  2002/11/28 16:19:25  southa
 * Fix delete object messaging
 *
 * Revision 1.10  2002/11/28 15:33:31  southa
 * Pass GameDef status over link
 *
 * Revision 1.9  2002/11/28 15:14:14  southa
 * Multiplayer setup timing
 *
 * Revision 1.8  2002/11/28 12:05:45  southa
 * Server name work
 *
 * Revision 1.7  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.6  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.5  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.4  2002/11/25 18:02:56  southa
 * Mushware ID work
 *
 * Revision 1.3  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 * Revision 1.2  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.1  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
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
#include "GameDefServer.h"
#include "GameProtocol.h"

#include "mushPlatform.h"

auto_ptr< CoreData<GameDefClient> > CoreData<GameDefClient>::m_instance;

GameDefClient::GameDefClient(const string& inName) :
    GameDef(inName),
    m_lastLinkMsec(0),
    m_lastRegistrationMsec(0),
    m_killed(false),
    m_joined(false)
{
    StatusSet(GameDef::kStatusInvalid); // Change this
}

void
GameDefClient::JoinGame(const string& inServer, U32 inPort)
{
    StatusSet(GameDef::kStatusNoServer);
    m_netAddress.ResolveFrom(inServer, inPort); // throws NetworkFail
    StatusSet(GameDef::kStatusTesting);
    m_joined=true;
    m_lastRegistrationMsec=0; // Schedule immediate registration
}

void
GameDefClient::Ticker(void)
{
    if (!m_joined) return;
    
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
    m_currentMsec=gameAppHandler.MillisecondsGet();

    MediaNetLink *netLink=NULL;
    if (MediaNetUtils::FindLinkToStation(netLink, m_netAddress))
    {
        COREASSERT(netLink != NULL);
        if (m_currentMsec > m_lastRegistrationMsec + kRegistrationMsec &&
            m_currentMsec > netLink->CreationMsecGet() + kLinkSetupWaitMsec)
        {
            UpdateServer(*netLink);
            m_lastRegistrationMsec = m_currentMsec;
        }
    }
    else
    {
        if (m_lastLinkMsec + kLinkSetupIntervalMsec < m_currentMsec)
        {
            CreateNewLink(m_netAddress);
            m_lastLinkMsec = m_currentMsec;
        }
    }
    UpdateStatus(); // Need to call this a bit less often
}

void
GameDefClient::UpdateServer(MediaNetLink& ioLink)
{
    MediaNetData netData;
    if (m_killed)
    {
        // Remove the image of this client on the server remote station
        GameProtocol::DeleteObjectCreate(netData, *this, NameGet());
    }
    else
    {
        // Update the client image on the remote station
        GameProtocol::CreateObjectCreate(netData, *this, NameGet());
    }
    
    try
    {
        ioLink.ReliableSend(netData);
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().NetLog() << "GameDefClient ticker send failed: " << e.what() << endl;
    }
}

void
GameDefClient::Kill(void)
{
    m_killed=true;
    // Schedule an immediate update on the ticker
    MediaNetLink *netLink=NULL;
    if (MediaNetUtils::FindLinkToStation(netLink, m_netAddress))
    {
        COREASSERT(netLink != NULL);
        UpdateServer(*netLink);
    }
}

void
GameDefClient::UpdateStatus(void)
{
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
    m_currentMsec=gameAppHandler.MillisecondsGet();

    if (m_currentMsec > CreationMsecGet() + kServerTimeoutMsec)
    {
        StatusSet(GameDef::kStatusNoServer);
    }
    
    CoreData<GameDefServer>::tMapIterator endValue = CoreData<GameDefServer>::Instance().End();

    for (CoreData<GameDefServer>::tMapIterator p = CoreData<GameDefServer>::Instance().Begin(); p != endValue; ++p)
    {
        if (p->second->ImageIs())
        {
            if (p->second->AddressGet() == AddressGet())
            {
                StatusSet(GameDef::kStatusOK);
                break;
            }
        }
    }
}

void
GameDefClient::WebPrint(ostream& ioOut) const
{
    ioOut << "<tr>";
    ioOut << "<td>" << MediaNetUtils::MakeWebSafe(NameGet()) << "</td>";
    ioOut << "<td>" << MediaNetUtils::MakeWebSafe(m_serverName) << "</td>";
    ioOut << "<td>" << m_netAddress << "</td>";
    ioOut << "<td>" << StatusWebStringGet() << "</td>";
    ioOut << "</tr>" << endl;
}

void
GameDefClient::NullHandler(CoreXML& inXML)
{
}

void
GameDefClient::HandleGameDefClientEnd(CoreXML& inXML)
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
    m_endTable[kPickleData]["gamedefclient"] = &GameDefClient::HandleGameDefClientEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
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

