/*
 * $Id: GameDefServer.cpp,v 1.6 2002/11/28 12:05:45 southa Exp $
 * $Log: GameDefServer.cpp,v $
 * Revision 1.6  2002/11/28 12:05:45  southa
 * Server name work
 *
 * Revision 1.5  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.4  2002/11/27 16:35:09  southa
 * Client and server image handling
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

#include "GameDefServer.h"

#include "GameAppHandler.h"
#include "GameDefClient.h"
#include "GameProtocol.h"

#include "mushPlatform.h"

auto_ptr< CoreData<GameDefServer> > CoreData<GameDefServer>::m_instance;

GameDefServer::GameDefServer(const string& inName) :
    GameDef(inName),
    m_playerCount(0),
    m_lastUpdateMsec(0),
    m_killed(false)
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
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
    m_currentMsec=gameAppHandler.MillisecondsGet();

    if (m_lastUpdateMsec + kUpdateMsec < m_currentMsec)
    {
        UpdateClients();
        m_lastUpdateMsec = m_currentMsec;
    }
}

void
GameDefServer::UpdateClients(void)
{
    CoreData<GameDefClient>::tMapIterator endValue=CoreData<GameDefClient>::Instance().End();

    for (CoreData<GameDefClient>::tMapIterator p=CoreData<GameDefClient>::Instance().Begin(); p != endValue; ++p)
    {
        GameDefClient *clientDef=p->second;
        COREASSERT(clientDef != NULL);
        if (clientDef->IsImage())
        {
            UpdateClient(*clientDef);
        }
    }
}

void
GameDefServer::UpdateClient(GameDefClient& inClient)
{
    COREASSERT(inClient.IsImage()); // Server shouldn't deal directly with clients on this station
    MediaNetLink *netLink=NULL;
    if (MediaNetUtils::FindLinkToStation(netLink, inClient.AddressGet()))
    {
        COREASSERT(netLink != NULL);
        MediaNetData netData;

        if (m_killed)
        {
            // Server is killed, so delete the server image on the remote station
            GameProtocol::DeleteObjectCreate(netData, *this, NameGet());
        }
        else
        {
            // Update the server image on the remote station
            GameProtocol::CreateObjectCreate(netData, *this, NameGet());
        }

        try
        {
            netLink->ReliableSend(netData);
        }
        catch (NetworkFail& e)
        {
            MediaNetLog::Instance().NetLog() << "GameDefClient ticker send failed: " << e.what() << endl;
        }
    }
}

void
GameDefServer::Kill(void)
{
    m_killed=true;

    // Schedule an immediate update on the ticker
    m_lastUpdateMsec=0;
}

void
GameDefServer::WebPrint(ostream& ioOut) const
{
    ioOut << "<tr>";
    ioOut << "<td>" << MediaNetUtils::MakeWebSafe(NameGet()) << "</td>";
    ioOut << "<td>" << m_netAddress << "</td>";
    ioOut << "<td>" << MediaNetUtils::MakeWebSafe(m_contractName) << "</td>";
    ioOut << "<td>" << m_playerCount << "/" << m_playerLimit << "</td>";
    ioOut << "<td><font class=\"bggreen\">" << "GO" << "</font></td>";
    ioOut << "</tr>";
}

void
GameDefServer::NullHandler(CoreXML& inXML)
{
}

void
GameDefServer::HandleMessageEnd(CoreXML& inXML)
{
    m_serverMessage = inXML.TopData();
}

void
GameDefServer::HandleContractEnd(CoreXML& inXML)
{
    m_contractName = inXML.TopData();
}

void
GameDefServer::HandlePlayerCountEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for playercount.  Should be <playercount>3</playercount>";
    if (!(data >> m_playerCount)) inXML.Throw(failMessage);
}

void
GameDefServer::HandlePlayerLimitEnd(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for playerlimit.  Should be <playerlimit>4</playerlimit>";
    if (!(data >> m_playerLimit)) inXML.Throw(failMessage);
}

void
GameDefServer::HandleDefServerEnd(CoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameDefServer::Pickle(ostream& inOut, const string& inPrefix="") const
{
    GameDef::Pickle(inOut, inPrefix);
    inOut << inPrefix << "<message>" << MediaNetUtils::MakeXMLSafe(m_serverMessage) << "</message>" << endl;
    inOut << inPrefix << "<contract>" << MediaNetUtils::MakeXMLSafe(m_contractName) << "</contract>" << endl;
    inOut << inPrefix << "<playercount>" << m_playerCount << "</playercount>" << endl;
    inOut << inPrefix << "<playerlimit>" << m_playerLimit << "</playerlimit>" << endl;
}

void
GameDefServer::Unpickle(CoreXML& inXML)
{
    GameDef::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_endTable[kPickleData]["gamedefserver"] = &GameDefServer::HandleDefServerEnd;
    m_startTable[kPickleData]["message"] = &GameDefServer::NullHandler;
    m_endTable[kPickleData]["message"] = &GameDefServer::HandleMessageEnd;
    m_startTable[kPickleData]["contract"] = &GameDefServer::NullHandler;
    m_endTable[kPickleData]["contract"] = &GameDefServer::HandleContractEnd;
    m_startTable[kPickleData]["playercount"] = &GameDefServer::NullHandler;
    m_endTable[kPickleData]["playercount"] = &GameDefServer::HandlePlayerCountEnd;
    m_startTable[kPickleData]["playerlimit"] = &GameDefServer::NullHandler;
    m_endTable[kPickleData]["playerlimit"] = &GameDefServer::HandlePlayerLimitEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    inXML.ParseStream(*this);
}

void
GameDefServer::XMLStartHandler(CoreXML& inXML)
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
            message << "Unexpected tag <" << inXML.TopTag() << "> in DefServer.  Potential matches are";
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
GameDefServer::XMLEndHandler(CoreXML& inXML)
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
            message << "Unexpected end of tag </" << inXML.TopTag() << "> in DefServer.  Potential matches are";
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
GameDefServer::XMLDataHandler(CoreXML& inXML)
{
}

char *
GameDefServer::TypeNameGet(void) const
{
    return "gamedefserver";
}

