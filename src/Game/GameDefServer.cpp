/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameDefServer.cpp,v 1.24 2003/01/20 10:45:26 southa Exp $
 * $Log: GameDefServer.cpp,v $
 * Revision 1.24  2003/01/20 10:45:26  southa
 * Singleton tidying
 *
 * Revision 1.23  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.22  2003/01/17 13:30:38  southa
 * Source conditioning and build fixes
 *
 * Revision 1.21  2003/01/14 17:38:19  southa
 * Mustl web configuration
 *
 * Revision 1.20  2003/01/13 14:31:57  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.19  2003/01/12 17:32:53  southa
 * Mushcore work
 *
 * Revision 1.18  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.17  2003/01/07 17:13:41  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.16  2002/12/29 20:59:55  southa
 * More build fixes
 *
 * Revision 1.15  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.14  2002/12/12 18:38:57  southa
 * Mustl separation
 *
 * Revision 1.13  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.12  2002/12/07 18:32:14  southa
 * Network ID stuff
 *
 * Revision 1.11  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.10  2002/11/28 18:05:35  southa
 * Print link ages
 *
 * Revision 1.9  2002/11/28 16:19:25  southa
 * Fix delete object messaging
 *
 * Revision 1.8  2002/11/28 15:33:31  southa
 * Pass GameDef status over link
 *
 * Revision 1.7  2002/11/28 15:14:14  southa
 * Multiplayer setup timing
 *
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
#include "GameSTL.h"

#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(GameDefServer);

GameDefServer::GameDefServer(const string& inName) :
    GameDef(inName),
    m_playerCount(0),
    m_lastUpdateMsec(0),
    m_killed(false)
{
    StatusSet(GameDef::kStatusInvalid);
}

void
GameDefServer::HostGame(const string& inContract, U32 inPlayerLimit)
{
    m_contractName = inContract;
    m_playerLimit = inPlayerLimit;
    StatusSet(GameDef::kStatusOK);
}

void
GameDefServer::Ticker(const string& inName)
{
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    m_currentMsec=gameAppHandler.MillisecondsGet();

    if (m_currentMsec > m_lastUpdateMsec + kUpdateMsec)
    {
        UpdateClients();
        m_lastUpdateMsec = m_currentMsec;
    }
}

void
GameDefServer::UpdateClients(void)
{
    MushcoreData<GameDefClient>::tMapIterator endValue=MushcoreData<GameDefClient>::Sgl().End();

    for (MushcoreData<GameDefClient>::tMapIterator p=MushcoreData<GameDefClient>::Sgl().Begin(); p != endValue; ++p)
    {
        GameDefClient *clientDef=p->second;
        MUSHCOREASSERT(clientDef != NULL);
        if (clientDef->ImageIs())
        {
            UpdateClient(*clientDef);
        }
    }
}

void
GameDefServer::UpdateClient(GameDefClient& inClient)
{
    MUSHCOREASSERT(inClient.ImageIs()); // Server shouldn't deal directly with clients on this station
    MustlLink *netLink=NULL;
    if (MustlUtils::FindLinkToStation(netLink, inClient.AddressGet()))
    {
        MUSHCOREASSERT(netLink != NULL);
        MustlData netData;

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
        catch (MushcoreNonFatalFail& e)
        {
            MustlLog::Sgl().NetLog() << "GameDefClient ticker send failed: " << e.what() << endl;
        }
    }
}

void
GameDefServer::Kill(void)
{
    m_killed=true;
    UpdateClients();
}

void
GameDefServer::WebPrint(ostream& ioOut) const
{
    ioOut << "<tr>";
    ioOut << "<td>" << MustlUtils::MakeWebSafe(NameGet()) << "</td>";
    ioOut << "<td>" << m_netAddress << "</td>";
    ioOut << "<td>" << MustlUtils::MakeWebSafe(m_contractName) << "</td>";
    ioOut << "<td>" << m_playerCount << "/" << m_playerLimit << "</td>";
    ioOut << "<td><font class=\"bggreen\">" << "GO" << "</font></td>";
    ioOut << "</tr>";
}

void
GameDefServer::NullHandler(MushcoreXML& inXML)
{
}

void
GameDefServer::HandleMessageEnd(MushcoreXML& inXML)
{
    m_serverMessage = inXML.TopData();
}

void
GameDefServer::HandleContractEnd(MushcoreXML& inXML)
{
    m_contractName = inXML.TopData();
}

void
GameDefServer::HandlePlayerCountEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for playercount.  Should be <playercount>3</playercount>";
    if (!(data >> m_playerCount)) inXML.Throw(failMessage);
}

void
GameDefServer::HandlePlayerLimitEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for playerlimit.  Should be <playerlimit>4</playerlimit>";
    if (!(data >> m_playerLimit)) inXML.Throw(failMessage);
}

void
GameDefServer::HandleDefServerEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameDefServer::Pickle(ostream& inOut, const string& inPrefix) const
{
    GameDef::Pickle(inOut, inPrefix);
    inOut << inPrefix << "<message>" << MustlUtils::MakeXMLSafe(m_serverMessage) << "</message>" << endl;
    inOut << inPrefix << "<contract>" << MustlUtils::MakeXMLSafe(m_contractName) << "</contract>" << endl;
    inOut << inPrefix << "<playercount>" << m_playerCount << "</playercount>" << endl;
    inOut << inPrefix << "<playerlimit>" << m_playerLimit << "</playerlimit>" << endl;
}

void
GameDefServer::Unpickle(MushcoreXML& inXML)
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
GameDefServer::XMLStartHandler(MushcoreXML& inXML)
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
GameDefServer::XMLEndHandler(MushcoreXML& inXML)
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
GameDefServer::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
GameDefServer::TypeNameGet(void) const
{
    return "gamedefserver";
}

