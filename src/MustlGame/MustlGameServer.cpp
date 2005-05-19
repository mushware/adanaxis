//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameServer.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 2nCy831nO8zMyYG9fdffcw
/*
 * $Id: MustlGameServer.cpp,v 1.4 2004/01/02 11:56:59 southa Exp $
 * $Log: MustlGameServer.cpp,v $
 * Revision 1.4  2004/01/02 11:56:59  southa
 * MushPie created
 *
 * Revision 1.3  2004/01/01 23:04:02  southa
 * XCode fixes
 *
 * Revision 1.2  2003/10/06 22:42:04  southa
 * Include fixes
 *
 * Revision 1.1  2003/10/06 22:22:38  southa
 * Moved from Game to MustlGame
 *
 * Revision 1.26  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.25  2003/08/21 23:08:42  southa
 * Fixed file headers
 *
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
 * Pass MustlGameBase status over link
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

#include "MustlGameServer.h"

#include "MustlGameClient.h"
#include "MustlGameSTL.h"

#include "mushGame.h"
#include "mushGL.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MustlGameServer);

MustlGameServer::MustlGameServer(const string& inName) :
    MustlGameBase(inName),
    m_playerCount(0),
    m_lastUpdateMsec(0),
    m_killed(false)
{
    StatusSet(MustlGameBase::kStatusInvalid);
}

void
MustlGameServer::HostGame(const string& inContract, U32 inPlayerLimit)
{
    m_contractName = inContract;
    m_playerLimit = inPlayerLimit;
    StatusSet(MustlGameBase::kStatusOK);
}

void
MustlGameServer::Ticker(const string& inName)
{
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());
    m_currentMsec=glAppHandler.MillisecondsGet();

    if (m_currentMsec > m_lastUpdateMsec + kUpdateMsec)
    {
        UpdateClients();
        m_lastUpdateMsec = m_currentMsec;
    }
}

void
MustlGameServer::UpdateClients(void)
{
    MushcoreData<MustlGameClient>::tMapIterator endValue=MushcoreData<MustlGameClient>::Sgl().End();

    for (MushcoreData<MustlGameClient>::tMapIterator p=MushcoreData<MustlGameClient>::Sgl().Begin(); p != endValue; ++p)
    {
        MustlGameClient *clientDef=p->second;
        MUSHCOREASSERT(clientDef != NULL);
        if (clientDef->ImageIs())
        {
            UpdateClient(*clientDef);
        }
    }
}

void
MustlGameServer::UpdateClient(MustlGameClient& inClient)
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
            MustlLog::Sgl().NetLog() << "MustlGameClient ticker send failed: " << e.what() << endl;
        }
    }
}

void
MustlGameServer::Kill(void)
{
    m_killed=true;
    UpdateClients();
}

void
MustlGameServer::WebPrint(ostream& ioOut) const
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
MustlGameServer::NullHandler(MushcoreXML& inXML)
{
}

void
MustlGameServer::HandleMessageEnd(MushcoreXML& inXML)
{
    m_serverMessage = inXML.TopData();
}

void
MustlGameServer::HandleContractEnd(MushcoreXML& inXML)
{
    m_contractName = inXML.TopData();
}

void
MustlGameServer::HandlePlayerCountEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for playercount.  Should be <playercount>3</playercount>";
    if (!(data >> m_playerCount)) inXML.Throw(failMessage);
}

void
MustlGameServer::HandlePlayerLimitEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for playerlimit.  Should be <playerlimit>4</playerlimit>";
    if (!(data >> m_playerLimit)) inXML.Throw(failMessage);
}

void
MustlGameServer::HandleDefServerEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
}

void
MustlGameServer::Pickle(ostream& inOut, const string& inPrefix) const
{
    MustlGameBase::Pickle(inOut, inPrefix);
    inOut << inPrefix << "<message>" << MustlUtils::MakeXMLSafe(m_serverMessage) << "</message>" << endl;
    inOut << inPrefix << "<contract>" << MustlUtils::MakeXMLSafe(m_contractName) << "</contract>" << endl;
    inOut << inPrefix << "<playercount>" << m_playerCount << "</playercount>" << endl;
    inOut << inPrefix << "<playerlimit>" << m_playerLimit << "</playerlimit>" << endl;
}

void
MustlGameServer::Unpickle(MushcoreXML& inXML)
{
    MustlGameBase::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_endTable[kPickleData]["gamedefserver"] = &MustlGameServer::HandleDefServerEnd;
    m_startTable[kPickleData]["message"] = &MustlGameServer::NullHandler;
    m_endTable[kPickleData]["message"] = &MustlGameServer::HandleMessageEnd;
    m_startTable[kPickleData]["contract"] = &MustlGameServer::NullHandler;
    m_endTable[kPickleData]["contract"] = &MustlGameServer::HandleContractEnd;
    m_startTable[kPickleData]["playercount"] = &MustlGameServer::NullHandler;
    m_endTable[kPickleData]["playercount"] = &MustlGameServer::HandlePlayerCountEnd;
    m_startTable[kPickleData]["playerlimit"] = &MustlGameServer::NullHandler;
    m_endTable[kPickleData]["playerlimit"] = &MustlGameServer::HandlePlayerLimitEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    inXML.ParseStream(*this);
}

void
MustlGameServer::XMLStartHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p2 = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p2 != m_startTable[m_pickleState].end())
    {
        (this->*p2->second)(inXML);
    }
    else
    {
        if (m_pickleState == kPickleData)
        {
MustlGameBase::XMLStartHandler(inXML);
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
MustlGameServer::XMLEndHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p2 = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p2 != m_endTable[m_pickleState].end())
    {
        (this->*p2->second)(inXML);
    }
    else
    {
        if (m_pickleState == kPickleWithinBase)
        {
MustlGameBase::XMLEndHandler(inXML);
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
MustlGameServer::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
MustlGameServer::TypeNameGet(void) const
{
    return "gamedefserver";
}

