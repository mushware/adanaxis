//%Header {
/*****************************************************************************
 *
 * File: src/Game/MustlGameClient.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } m88+th2pONGD/3Tj10JOUg
/*
 * $Id: MustlGameClient.cpp,v 1.33 2003/10/04 15:32:09 southa Exp $
 * $Log: MustlGameClient.cpp,v $
 * Revision 1.33  2003/10/04 15:32:09  southa
 * Module split
 *
 * Revision 1.32  2003/10/04 12:22:59  southa
 * File renaming
 *
 * Revision 1.31  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.30  2003/08/21 23:08:42  southa
 * Fixed file headers
 *
 * Revision 1.29  2003/01/20 10:45:25  southa
 * Singleton tidying
 *
 * Revision 1.28  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.27  2003/01/17 13:30:38  southa
 * Source conditioning and build fixes
 *
 * Revision 1.26  2003/01/14 17:38:19  southa
 * Mustl web configuration
 *
 * Revision 1.25  2003/01/13 14:31:57  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.24  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.23  2003/01/07 17:13:41  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.22  2002/12/29 20:59:54  southa
 * More build fixes
 *
 * Revision 1.21  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.20  2002/12/17 00:58:28  southa
 * Added support for libmustl target
 *
 * Revision 1.19  2002/12/12 18:38:57  southa
 * Mustl separation
 *
 * Revision 1.18  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.17  2002/12/09 23:59:58  southa
 * Network control
 *
 * Revision 1.16  2002/12/07 18:32:14  southa
 * Network ID stuff
 *
 * Revision 1.15  2002/12/05 23:52:51  southa
 * Network management and status
 *
 * Revision 1.14  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.13  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.12  2002/11/28 18:05:35  southa
 * Print link ages
 *
 * Revision 1.11  2002/11/28 16:19:25  southa
 * Fix delete object messaging
 *
 * Revision 1.10  2002/11/28 15:33:31  southa
 * Pass MustlGameBase status over link
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
 * Added type name accessor to MushcorePickle
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

#include "MustlGameClient.h"

#include "GameAppHandler.h"

// Need to remove this dependency
#include "Infernal/InfernalData.h"

#include "MustlGameServer.h"
#include "MustlGameUtils.h"
#include "GameProtocol.h"
#include "GameSTL.h"

#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MustlGameClient);

MustlGameClient::MustlGameClient(const string& inName) :
    MustlGameBase(inName),
    m_lastLinkMsec(0),
    m_lastRegistrationMsec(0),
    m_netLinks(kMaxLinks, MushcoreDataRef<MustlLink>("invalid-link")),
    m_lastLinkNum(0),
    m_numLinks(kNumSetupModeLinks),
    m_uplinkBandwidth(0),
    m_playerRef(inName, &InfernalData::Sgl().PlayerGet()),
    m_killed(false),
    m_joined(false)
{
    StatusSet(MustlGameBase::kStatusInvalid); // Change this
}

void
MustlGameClient::JoinGame(const string& inServer, U32 inPort)
{
    StatusSet(MustlGameBase::kStatusNoServer);
    m_netAddress.ResolveFromHostName(inServer, inPort); // Can block, throws MustlFail
    StatusSet(MustlGameBase::kStatusTesting);
    m_joined=true;
    m_lastRegistrationMsec=0; // Schedule immediate registration
}

void
MustlGameClient::Ticker(const string& inName)
{
    // Needs calling at least once per second
    if (!m_joined) return;

    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    if (gameAppHandler.GameRunningIs())
    {
        m_numLinks=kNumGameModeLinks;
    }
    else
    {
        m_numLinks=kNumSetupModeLinks;
    }
    
    m_linkGood = MustlGameUtils::MaintainLinks(m_netLinks, inName, m_netAddress, m_numLinks);
    
    m_currentMsec=gameAppHandler.MillisecondsGet();

    // This can update the server itself, so do it before the registration time check
    UpdateStatus();
    
    if (m_linkGood)
    {
        if (m_currentMsec > m_lastRegistrationMsec + kRegistrationMsec)
        {
            UpdateServer();
        }
    }

}

void
MustlGameClient::UpdateServer(void)
{
    MustlData netData;
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
        ReliableSendToServer(netData);
        m_lastRegistrationMsec = m_currentMsec;
    }
    catch (MushcoreNonFatalFail& e)
    {
        MustlLog::Sgl().NetLog() << "MustlGameClient ticker send failed: " << e.what() << endl;
    }
}

void
MustlGameClient::Kill(void)
{
    m_killed=true;

    UpdateServer();
}

void
MustlGameClient::UpdateStatus(void)
{
    MustlGameBase::tStatus oldStatus = StatusGet();
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    m_currentMsec=gameAppHandler.MillisecondsGet();

    if (m_currentMsec > CreationMsecGet() + kServerTimeoutMsec)
    {
        StatusSet(MustlGameBase::kStatusNoServer);
    }
    
    MushcoreData<MustlGameServer>::tMapIterator endValue = MushcoreData<MustlGameServer>::Sgl().End();

    for (MushcoreData<MustlGameServer>::tMapIterator p = MushcoreData<MustlGameServer>::Sgl().Begin(); p != endValue; ++p)
    {
        if (p->second->ImageIs())
        {
            if (p->second->AddressGet() == AddressGet())
            {
                StatusSet(MustlGameBase::kStatusOK);
                break;
            }
        }
    }
    if (oldStatus != StatusGet())
    {
        // Change of status, so inform the server
        UpdateServer();
    }
}

void
MustlGameClient::ReliableSendToServer(MustlData& ioData)
{
    m_uplinkBandwidth += ioData.ReadSizeGet();
    MustlGameUtils::ReliableSend(m_lastLinkNum, m_netLinks, m_numLinks, ioData);
}

void
MustlGameClient::FastSendToServer(MustlData& ioData)
{
    m_uplinkBandwidth += ioData.ReadSizeGet();
    MustlGameUtils::FastSend(m_lastLinkNum, m_netLinks, m_numLinks, ioData);
}

void
MustlGameClient::WebHeaderPrint(ostream& ioOut)
{
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Player</font></td>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Server</font></td>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Address</font></td>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Bytes sent</font></td>";
    ioOut << "<td class=\"bgred\"><font class=\"bold\">Status</font></td>";
}

void
MustlGameClient::WebPrint(ostream& ioOut) const
{
    ioOut << "<td>" << MustlUtils::MakeWebSafe(NameGet()) << "</td>";
    ioOut << "<td>" << MustlUtils::MakeWebSafe(m_serverName) << "</td>";
    ioOut << "<td>" << m_netAddress << "</td>";
    ioOut << "<td>" << m_uplinkBandwidth << "</td>";
    ioOut << "<td>" << StatusWebStringGet() << "</td>";
}

void
MustlGameClient::NullHandler(MushcoreXML& inXML)
{
}

void
MustlGameClient::HandleULBytesEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for ulbytes.  Should be <ulbytes>10240</ulbytes>";
    if (!(data >> m_uplinkBandwidth)) inXML.Throw(failMessage);
}

void
MustlGameClient::HandleGameDefClientEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
}

void
MustlGameClient::Pickle(ostream& inOut, const string& inPrefix) const
{
    MustlGameBase::Pickle(inOut, inPrefix);
    inOut << inPrefix << "<ulbytes>" << m_uplinkBandwidth << "</ulbytes>" << endl;
}

void
MustlGameClient::Unpickle(MushcoreXML& inXML)
{
    MustlGameBase::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_endTable[kPickleData]["gamedefclient"] = &MustlGameClient::HandleGameDefClientEnd;
    m_startTable[kPickleData]["ulbytes"] = &MustlGameClient::NullHandler;
    m_endTable[kPickleData]["ulbytes"] = &MustlGameClient::HandleULBytesEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    inXML.ParseStream(*this);
}

void
MustlGameClient::XMLStartHandler(MushcoreXML& inXML)
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
MustlGameBase::XMLStartHandler(inXML);
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
MustlGameClient::XMLEndHandler(MushcoreXML& inXML)
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
MustlGameClient::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
MustlGameClient::TypeNameGet(void) const
{
    return "gamedefclient";
}

