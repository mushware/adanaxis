/*
 * $Id: GameDefServer.cpp,v 1.2 2002/11/25 18:02:57 southa Exp $
 * $Log: GameDefServer.cpp,v $
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

GameDefServer::GameDefServer(const string& inName) :
    GameDef(inName),
    m_lastLinkMsec(0),
    m_lastUpdateMsec(0)
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
    CoreData<GameDef>::tMapIterator endValue=CoreData<GameDef>::Instance().End();

    for (CoreData<GameDef>::tMapIterator p=CoreData<GameDef>::Instance().Begin(); p != endValue; ++p)
    {
        GameDefClient *clientDef=dynamic_cast<GameDefClient *>(p->second);
        if (clientDef != NULL && clientDef->IsImage())
        {
            UpdateClient(*clientDef);
        }
    }
}

void
GameDefServer::UpdateClient(GameDefClient& inClient)
{
    MediaNetLink *netLink=NULL;
    if (MediaNetUtils::FindLinkToStation(netLink, inClient.AddressGet()))
    {
        COREASSERT(netLink != NULL);
        if (m_lastUpdateMsec + kUpdateMsec < m_currentMsec)
        {
            MediaNetData netData;
            GameProtocol::CreateObjectCreate(netData, *this, NameGet());
            netLink->ReliableSend(netData);
        }
    }
    else
    {
        if (m_lastLinkMsec + kLinkSetupMsec < m_currentMsec)
        {
            CreateNewLink(inClient.AddressGet());
            m_lastLinkMsec = m_currentMsec;
        }
    }
}

void
GameDefServer::WebPrint(ostream& ioOut) const
{
    ioOut << "<tr>";
    ioOut << "<td>" << MediaNetUtils::MakeWebSafe(m_serverName) << "</td>";
    ioOut << "<td>" << MediaNetUtils::MakeWebSafe(m_contractName) << "</td>";
    ioOut << "<td>" << m_playerLimit << "</td>";
    ioOut << "<td><font class=\"bggreen\">" << "GO" << "</font></td>";
    ioOut << "</tr>";
}

void
GameDefServer::NullHandler(CoreXML& inXML)
{
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
    inOut << inPrefix << "<!-- Incomplete -->" << endl;
}

void
GameDefServer::Unpickle(CoreXML& inXML)
{
GameDef::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_endTable[kPickleData]["gamedefserver"] = &GameDefServer::HandleDefServerEnd;
    m_pickleState=kPickleData;
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

