/*
 * $Id: MediaNetLink.cpp,v 1.23 2002/12/05 13:20:13 southa Exp $
 * $Log: MediaNetLink.cpp,v $
 * Revision 1.23  2002/12/05 13:20:13  southa
 * Client link handling
 *
 * Revision 1.22  2002/11/28 18:05:36  southa
 * Print link ages
 *
 * Revision 1.21  2002/11/27 20:17:27  southa
 * Basic network cleardown
 *
 * Revision 1.20  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.19  2002/11/27 13:23:27  southa
 * Server and client data exchange
 *
 * Revision 1.18  2002/11/23 17:23:44  southa
 * Sleep in setup
 *
 * Revision 1.17  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.16  2002/11/22 18:16:44  southa
 * Network tweaks
 *
 * Revision 1.15  2002/11/22 18:02:43  southa
 * Wait for TCP connection
 *
 * Revision 1.14  2002/11/22 15:33:59  southa
 * More network logging
 *
 * Revision 1.13  2002/11/22 15:00:33  southa
 * Network connection handling
 *
 * Revision 1.12  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.11  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
 * Revision 1.10  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.9  2002/11/18 21:02:39  southa
 * Prevent crash on exit
 *
 * Revision 1.8  2002/11/04 19:34:46  southa
 * Network link maintenance
 *
 * Revision 1.7  2002/11/04 15:50:31  southa
 * Network log
 *
 * Revision 1.6  2002/11/04 13:11:58  southa
 * Link setup work
 *
 * Revision 1.5  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.4  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.3  2002/11/01 18:46:26  southa
 * UDP Links
 *
 * Revision 1.2  2002/11/01 16:15:27  southa
 * Network send and receive
 *
 * Revision 1.1  2002/10/31 19:55:54  southa
 * Network links
 *
 */

#include "MediaNetLink.h"

#include "MediaNetID.h"
#include "MediaNetLog.h"
#include "MediaNetProtocol.h"
#include "MediaNetServer.h"
#include "MediaNetUtils.h"

#include "mushPlatform.h"

auto_ptr< CoreData<MediaNetLink> > CoreData<MediaNetLink>::m_instance;

U32 MediaNetLink::m_linkNameNum=1;

MediaNetLink::MediaNetLink(const MediaNetID& inID, const string& inServer, U32 inPort)
{
    // I am the client end of the link
    m_netID = inID.Clone();
    Initialise();
    m_udpUseServerPort=false;
    MediaNetLog::Instance().NetLog() << "Connecting to " << inServer << ":" << inPort << endl;
    TCPConnect(inServer, inPort);
    m_tcpState.linkState=kLinkStateConnecting;
    
    UDPConnect(inPort);
    m_client.UDPRemotePortNetworkOrderSet(PlatformNet::HostToNetworkOrderU16(inPort));
    UDPLinkCheckSend();
    m_targetName=inServer;
}

MediaNetLink::MediaNetLink(const MediaNetID& inID, const MediaNetAddress& inAddress)
{
    // I am the client end of the link
    m_netID = inID.Clone();
    Initialise();
    m_udpUseServerPort=false;
    string serverName=inAddress.HostStringGet();
    U32 portNum=inAddress.PortGetHostOrder();
MediaNetLog::Instance().NetLog() << "Connecting to " << serverName << ":" << portNum << endl;
    TCPConnect(serverName, portNum);
    m_tcpState.linkState=kLinkStateConnecting;

    UDPConnect(portNum);
    m_client.UDPRemotePortNetworkOrderSet(PlatformNet::HostToNetworkOrderU16(portNum));
    UDPLinkCheckSend();
    m_targetName=serverName;
}

MediaNetLink::MediaNetLink(TCPsocket inSocket, U32 inPort)
{
    // I am the server end of the link
    m_netID = NULL;
    Initialise();
    m_udpState.linkState=kLinkStateWaitingForPort;
    m_udpUseServerPort=true;
    TCPSocketTake(inSocket);
    m_client.UDPRemotePortNetworkOrderSet(0); // We don't know yet
}

void
MediaNetLink::Initialise(void)
{
    m_currentMsec=SDL_GetTicks();
    m_creationMsec=m_currentMsec;
    m_lastActivityMsec=m_currentMsec;
    m_tcpState.linkCheckTime=0;
    m_tcpState.linkState=kLinkStateUntested;
    m_tcpState.linkCheckState=kLinkCheckStateIdle;
    m_tcpState.linkPingTime=0;
    m_tcpState.linkErrorsSinceGood=0;
    m_tcpState.linkErrorTotal=0;
    m_tcpState.linkSendCtr=0;
    m_tcpState.linkReceiveCtr=0;
    m_tcpState.linkCheckSeqNum='A';

    m_udpState.linkCheckTime=0;
    m_udpState.linkState=kLinkStateUntested;
    m_udpState.linkCheckState=kLinkCheckStateIdle;
    m_udpState.linkPingTime=0;
    m_udpState.linkErrorsSinceGood=0;
    m_udpState.linkErrorTotal=0;
    m_udpState.linkSendCtr=0;
    m_udpState.linkReceiveCtr=0;
    m_udpState.linkCheckSeqNum='M';
    m_loggedLinkInfo=false;
}

MediaNetLink::~MediaNetLink()
{
    if (m_netID != NULL)
    {
        delete m_netID;
    }
}

void
MediaNetLink::TCPConnect(const string& inServer, U32 inPort)
{
    m_client.TCPConnect(inServer, inPort);
    m_targetIsServer=true;
}

void
MediaNetLink::TCPSocketTake(TCPsocket inSocket)
{
    m_client.TCPSocketTake(inSocket);
    m_targetIsServer=false;
}

void
MediaNetLink::UDPConnect(U32 inPort)
{
    m_client.UDPConnect(inPort);
}

void
MediaNetLink::Disconnect(MediaNetProtocol::tReasonCode inCode)
{
    if (m_tcpState.linkState != kLinkStateDead ||
        m_udpState.linkState != kLinkStateDead)
    {
        MediaNetLog::Instance().NetLog() << "Link closing reasonCode=" << inCode << ": " << *this << endl;
    }
    
    try
    {
        if (m_tcpState.linkState != kLinkStateDead)
        {
            MediaNetData data;
            MediaNetProtocol::KillLinkCreate(data, inCode);
            TCPSend(data);
        }
    }
    catch (exception& e)
    {
        MediaNetLog::Instance().NetLog() << "TCP link disconnect exception: " << e.what() << endl;
    }
    
    try
    {
        if (m_udpState.linkState != kLinkStateDead)
        {
            MediaNetData data;
            MediaNetProtocol::KillLinkCreate(data, inCode);
            UDPSend(data);
        }
    }
    catch (exception& e)
    {
        MediaNetLog::Instance().NetLog() << "UDP link disconnect exception: " << e.what() << endl;
    }
    
    m_client.TCPDisconnect();
    m_client.UDPDisconnect();
    
    m_tcpState.linkState=kLinkStateDead;
    m_udpState.linkState=kLinkStateDead;
}

bool
MediaNetLink::LinkIsUpForSend(tLinkState inState)
{
    switch (inState)
    {
        case kLinkStateInvalid:
        case kLinkStateNotMade:
        case kLinkStateWaitingForPort:
        case kLinkStateConnecting:
        case kLinkStateDead:
            return false;

        case kLinkStateUntested:
        case kLinkStateTesting:
        case kLinkStateIdle:
            return true;
    }
    COREASSERT(false);
    return false;
}

bool
MediaNetLink::LinkIsUpForReceive(tLinkState inState)
{
    switch (inState)
    {
        case kLinkStateInvalid:
        case kLinkStateNotMade:
        case kLinkStateConnecting:
        case kLinkStateDead:
            return false;

        case kLinkStateWaitingForPort:
        case kLinkStateUntested:
        case kLinkStateTesting:
        case kLinkStateIdle:
            return true;
    }
    COREASSERT(false);
    return false;
}

void
MediaNetLink::LinkChecksSend(void)
{
    TCPLinkCheckSend();
    UDPLinkCheckSend();
}

void
MediaNetLink::TCPLinkCheckSend(void)
{
    m_currentMsec=SDL_GetTicks();
    if (m_currentMsec > m_tcpState.linkCheckTime + kLinkCheckDeadTime)
    {
        MediaNetData data;
        m_tcpState.linkCheckSeqNum++;
        MediaNetProtocol::TCPLinkCheckCreate(data, m_tcpState.linkCheckSeqNum);
        m_tcpState.linkCheckState=kLinkCheckStateAwaitingReply;
        m_tcpState.linkCheckTime=m_currentMsec;
        TCPSend(data);
    }
}

void
MediaNetLink::UDPLinkCheckSend(void)
{
    m_currentMsec=SDL_GetTicks();
    if (m_currentMsec > m_udpState.linkCheckTime + kLinkCheckDeadTime)
    {
        MediaNetData data;
        m_udpState.linkCheckSeqNum++;
        MediaNetProtocol::UDPLinkCheckCreate(data, m_udpState.linkCheckSeqNum);
        m_udpState.linkCheckState=kLinkCheckStateAwaitingReply;
        m_udpState.linkCheckTime=m_currentMsec;
        UDPSend(data);
    }
}    

void
MediaNetLink::Tick(void)
{
    m_currentMsec=SDL_GetTicks();
    
    if (m_currentMsec > m_lastActivityMsec + kLinkIdleTimeoutMsec)
    {
        // Idle timer expired
        Disconnect(MediaNetProtocol::kReasonCodeIdleTimeout);
    }
    
    if (m_tcpState.linkState == kLinkStateConnecting)
    {
        if (m_client.TCPConnectionCompleted())
        {
            m_tcpState.linkState = kLinkStateUntested;
            TCPLinkCheckSend();
        }
    }
    
    U32 tcpLinkCheckPeriod=kTCPFastLinkCheckPeriod;
    if (m_tcpState.linkState == kLinkStateIdle && m_tcpState.linkErrorsSinceGood == 0)
    {
        tcpLinkCheckPeriod=kTCPSlowLinkCheckPeriod;
    }

    if (LinkIsUpForSend(m_tcpState.linkState) &&
        m_currentMsec > m_tcpState.linkCheckTime + tcpLinkCheckPeriod)
    {
        m_tcpState.linkState = kLinkStateTesting;

        if (m_tcpState.linkCheckState == kLinkCheckStateAwaitingReply)
        {
            ++m_tcpState.linkErrorTotal;
            ++m_tcpState.linkErrorsSinceGood;
            if (LinkDeathCheck(m_tcpState))
            {
                m_client.TCPDisconnect();
                m_tcpState.linkState=kLinkStateDead;
            }
            if (LinkIsUpForSend(m_tcpState.linkState))
            {
                TCPLinkCheckSend();
            }
            MediaNetLog::Instance().NetLog() << "TCP link check failed" << endl;
        }
        else
        {
            TCPLinkCheckSend();
        }
    }

    if (m_tcpState.linkState != kLinkStateDead && LinkDeathCheck(m_tcpState))
    {
        m_client.TCPDisconnect();
        m_tcpState.linkState=kLinkStateDead;
    }
    
    U32 udpLinkCheckPeriod=kUDPFastLinkCheckPeriod;
    if (m_udpState.linkState == kLinkStateIdle && m_udpState.linkErrorsSinceGood == 0)
    {
        udpLinkCheckPeriod=kUDPSlowLinkCheckPeriod;
    }

    if (LinkIsUpForSend(m_udpState.linkState) &&
        m_currentMsec > m_udpState.linkCheckTime + udpLinkCheckPeriod)
    {
        m_udpState.linkState = kLinkStateTesting;
        
        if (m_udpState.linkCheckState == kLinkCheckStateAwaitingReply)
        {
            ++m_udpState.linkErrorTotal;
            ++m_udpState.linkErrorsSinceGood;
            if (LinkDeathCheck(m_udpState))
            {
                // Just disconnnect UDP if it fails
                m_client.UDPDisconnect();
                m_udpState.linkState=kLinkStateDead;
            }
            
            if (LinkIsUpForSend(m_udpState.linkState))
            {
                UDPLinkCheckSend();
            }
            MediaNetLog::Instance().NetLog() << "UDP link check failed" << endl;
        }
        else
        {
            UDPLinkCheckSend();
        }
    }

    if (m_udpState.linkState != kLinkStateDead && LinkDeathCheck(m_udpState))
    {
        // Just disconnnect UDP if it fails
        m_client.UDPDisconnect();
        m_udpState.linkState=kLinkStateDead;
    }
}

bool
MediaNetLink::LinkDeathCheck(LinkState& ioLinkState)
{
    if (!LinkIsUpForSend(ioLinkState.linkState) && m_currentMsec > m_creationMsec + kLinkInitTimeoutMsec)
    {
        // Timed out creating the link
        return true;
    }
    
    return (ioLinkState.linkErrorTotal >= kErrorTotalLimit ||
            ioLinkState.linkErrorsSinceGood >= kErrorsSinceGoodLimit
            );
}

bool
MediaNetLink::IsDead(void)
{
    return m_tcpState.linkState == kLinkStateDead &&
           m_udpState.linkState == kLinkStateDead;
}

bool
MediaNetLink::ReadyIs(void) const
{
    return (m_tcpState.linkState == kLinkStateTesting ||
            m_tcpState.linkState == kLinkStateIdle ||
            m_udpState.linkState == kLinkStateTesting ||
            m_udpState.linkState == kLinkStateIdle);
}

void
MediaNetLink::TCPSend(MediaNetData& ioData)
{
    try
    {
        if (!LinkIsUpForSend(m_tcpState.linkState))
        {
            throw(NetworkFail("TCPSend on down link"));
        }
        m_client.TCPSend(ioData);
        ++m_tcpState.linkSendCtr;
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().NetLog() << "TCPSend exception: " << e.what() << endl;
        if (m_tcpState.linkErrorTotal == 0)
        {
            MediaNetLog::Instance().VerboseLog() << "TCPSend: Failed link=" << *this << endl;
        } 
        ++m_tcpState.linkErrorTotal;
        ++m_tcpState.linkErrorsSinceGood;
    }
}

void
MediaNetLink::TCPReceive(MediaNetData& outData)
{
    try
    {
        if (!LinkIsUpForReceive(m_tcpState.linkState))
        {
            // Receive on dead link.  Don't raise an exception for this
            return;
        }
        m_client.TCPReceive(outData);
        ++m_tcpState.linkReceiveCtr;
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().NetLog() << "TCPReceive exception: " << e.what() << endl;
        if (m_tcpState.linkErrorTotal == 0)
        {
            MediaNetLog::Instance().VerboseLog() << "TCPReceive: Failed link=" << *this << endl;
        }        
        ++m_tcpState.linkErrorTotal;
        ++m_tcpState.linkErrorsSinceGood;
    }
}

void
MediaNetLink::UDPSend(MediaNetData& ioData)
{
    try
    {
        if (!LinkIsUpForSend(m_udpState.linkState))
        {
            throw(NetworkFail("UDPSend on down link"));
        }
        if (m_udpUseServerPort)
        {
            MediaNetServer::Instance().UDPSend(m_client.RemoteIPGet(), m_client.UDPRemotePortGet(), ioData);
        }
        else
        {
            m_client.UDPSend(ioData);
            ++m_udpState.linkSendCtr;
        }
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().NetLog() << "UDPSend exception: " << e.what() << endl;
        if (m_udpState.linkErrorTotal == 0)
        {
            MediaNetLog::Instance().VerboseLog() << "UDPSend: Failed link=" << *this << endl;
        }
        ++m_udpState.linkErrorTotal;
        ++m_udpState.linkErrorsSinceGood;
    }
}

void
MediaNetLink::UDPReceive(MediaNetData& outData)
{
    try
    {
        if (!LinkIsUpForReceive(m_udpState.linkState))
        {
            // Receive on dead link.  Don't raise an exception for this
            return;
        }
        if (m_udpUseServerPort)
        {
            // Don't receive here - the server will give us our data
        }
        else
        {
            m_client.UDPReceive(outData);
            ++m_udpState.linkReceiveCtr;
        }
    }
    catch (NetworkFail& e)
    {
        MediaNetLog::Instance().NetLog() << "UDPReceive exception: " << e.what() << endl;
        if (m_udpState.linkErrorTotal == 0)
        {
            MediaNetLog::Instance().VerboseLog() << "UDPReceive: Failed link=" << *this << endl;
        }
        ++m_udpState.linkErrorTotal;
        ++m_udpState.linkErrorsSinceGood;
    }
}

void
MediaNetLink::FastSend(MediaNetData& ioData)
{
    if (LinkIsUpForSend(m_udpState.linkState))
    {
        UDPSend(ioData);
    }
    else if (LinkIsUpForSend(m_tcpState.linkState))
    {
        TCPSend(ioData);
    }
    else
    {
        throw(NetworkFail("Send on dead link"));
    }
    m_lastActivityMsec = SDL_GetTicks();
}

void
MediaNetLink::ReliableSend(MediaNetData& ioData)
{
    if (LinkIsUpForSend(m_tcpState.linkState))
    {
        TCPSend(ioData);
    }    
    else if (LinkIsUpForSend(m_udpState.linkState))
    {
        UDPSend(ioData);
    }
    else
    {
        throw(NetworkFail("Send on dead link"));
    }
    m_lastActivityMsec = SDL_GetTicks();
}

bool
MediaNetLink::UDPIfAddressMatchReceive(bool& outTakeMessage, MediaNetData& ioData)
{
    if (ioData.SourceHostGet() == UDPTargetIPGet() &&
        (UDPTargetPortGet() == 0 ||
         ioData.SourcePortGet() == UDPTargetPortGet())
        )
    {
        // We receive if port and IP match.  Also if IP matches and our target port is 0,
        // as this allows us to receive the initial link check which tells the server which
        // port to talk back the the client on.
        
        // This function should append the data to m_udpState to handled fragmentation, but doesn't yet
        MediaNetProtocol::Unpack(ioData);
        outTakeMessage=MediaNetProtocol::MessageTake(ioData);
        return true;
    }
    else
    {
        outTakeMessage=false;
        return false;
    }
}

bool
MediaNetLink::Receive(MediaNetData * & outData)
{

    UDPReceive(m_udpState.linkData);
    if (!m_udpState.linkData.IsEmptyForRead())
    {
        MediaNetProtocol::Unpack(m_udpState.linkData);
        if (MediaNetProtocol::MessageTake(m_udpState.linkData))
        {
            outData = &m_udpState.linkData;
            return true;
        }
    }
    
    TCPReceive(m_tcpState.linkData);
    if (!m_tcpState.linkData.IsEmptyForRead())
    {
        MediaNetProtocol::Unpack(m_tcpState.linkData);
        if (MediaNetProtocol::MessageTake(m_tcpState.linkData))
        {
            outData = &m_tcpState.linkData;
            return true;
        }
    }
    
    return false;
}

void
MediaNetLink::NetIDSet(const MediaNetID& inID)
{
    if (m_netID != NULL)
    {
        delete m_netID;
    }
    m_netID = inID.Clone();
}

void
MediaNetLink::MessageHandle(U32 inType, MediaNetData& ioData)
{
    switch (inType)
    {
        case MediaNetProtocol::kMessageTypeTCPLinkCheck:
            MessageTCPLinkCheckHandle(ioData);
            break;

        case MediaNetProtocol::kMessageTypeTCPLinkCheckReply:
            MessageTCPLinkCheckReplyHandle(ioData);
            break;

        case MediaNetProtocol::kMessageTypeUDPLinkCheck:
            MessageUDPLinkCheckHandle(ioData);
            break;

        case MediaNetProtocol::kMessageTypeUDPLinkCheckReply:
            MessageUDPLinkCheckReplyHandle(ioData);
            break;

        case MediaNetProtocol::kMessageTypeKillLink:
            MessageKillLinkHandle(ioData);
            break;

        default:
            break;
    }
}

void
MediaNetLink::MessageTCPLinkCheckHandle(MediaNetData& ioData)
{
    U8 seqNum = ioData.MessageBytePop();
    
    MediaNetData replyData;
    MediaNetProtocol::TCPLinkCheckReplyCreate(replyData, seqNum);
    TCPSend(replyData);

    if (m_tcpState.linkState == kLinkStateUntested)
    {
        TCPLinkCheckSend();
    }
}

void
MediaNetLink::MessageTCPLinkCheckReplyHandle(MediaNetData& ioData)
{
    m_currentMsec=SDL_GetTicks();

    U32 seqNum = ioData.MessageBytePop();
    if (seqNum == m_tcpState.linkCheckSeqNum &&
        m_tcpState.linkCheckState == kLinkCheckStateAwaitingReply)
    {
        m_tcpState.linkPingTime=m_currentMsec - m_tcpState.linkCheckTime;
        if (m_tcpState.linkState == kLinkStateUntested ||
            m_tcpState.linkState == kLinkStateTesting)
        {
            m_tcpState.linkState = kLinkStateIdle;
            if (m_udpState.linkState == kLinkStateIdle) LinkInfoLog();
        }
        m_tcpState.linkCheckState = kLinkCheckStateIdle;
        m_tcpState.linkErrorsSinceGood=0;
        MediaNetLog::Instance().VerboseLog() << "TCP link check good" << endl;
    }
}

void
MediaNetLink::MessageUDPLinkCheckHandle(MediaNetData& ioData)
{
    U8 seqNum = ioData.MessageBytePop();
    if (!m_udpUseServerPort && !m_client.UDPConnectedGet())
    {
        UDPConnect(PlatformNet::NetworkToHostOrderU16(ioData.SourcePortGet()));
        m_udpState.linkState=kLinkStateUntested;
    }
    
    if (m_udpState.linkState == kLinkStateWaitingForPort)
    {
        m_client.UDPRemotePortNetworkOrderSet(ioData.SourcePortGet());
        m_udpState.linkState = kLinkStateUntested;
    }
    MediaNetData replyData;
    MediaNetProtocol::UDPLinkCheckReplyCreate(replyData, seqNum);
    UDPSend(replyData);

    if (m_udpState.linkState == kLinkStateUntested)
    {
        UDPLinkCheckSend();
    }
}

void
MediaNetLink::MessageUDPLinkCheckReplyHandle(MediaNetData& ioData)
{
    m_currentMsec=SDL_GetTicks();

    U32 seqNum = ioData.MessageBytePop();
    if (seqNum == m_udpState.linkCheckSeqNum &&
        m_udpState.linkCheckState == kLinkCheckStateAwaitingReply)
    {
        m_udpState.linkPingTime=m_currentMsec - m_udpState.linkCheckTime;
        if (m_udpState.linkState == kLinkStateUntested ||
            m_udpState.linkState == kLinkStateTesting)
        {
            m_udpState.linkState = kLinkStateIdle;
            if (m_tcpState.linkState == kLinkStateIdle) LinkInfoLog();
        }
        m_udpState.linkCheckState = kLinkCheckStateIdle;
        m_udpState.linkErrorsSinceGood=0;
        MediaNetLog::Instance().VerboseLog() << "UDP link check good" << endl;
    }
}

void
MediaNetLink::MessageKillLinkHandle(MediaNetData& ioData)
{
    U32 reasonCode = ioData.MessageBytePop();
    MediaNetLog::Instance().VerboseLog() << "Link kill received (" << reasonCode << ")" << endl;
    if (reasonCode != MediaNetProtocol::kReasonCodePeerDisconnected)
    {
        Disconnect(MediaNetProtocol::kReasonCodePeerDisconnected);
    }
}

void
MediaNetLink::LinkInfoLog(void) const
{
    if (!m_loggedLinkInfo)
    {
        MediaNetLog::Instance().VerboseLog() << "Link: " << *this << endl;
    }
    m_loggedLinkInfo=true;
}

void
MediaNetLink::Print(ostream& ioOut) const
{
    ioOut << "[tcpState=" << m_tcpState << ", udpState=" << m_udpState;
    ioOut << ", creationMsec =" << m_creationMsec << ", lastActivityMsec=" << m_lastActivityMsec;
    ioOut << ", currentMsec=" << m_currentMsec << ", targetName=" << m_targetName << ", netID";
    if (m_netID == NULL)
    {
        ioOut << " is NULL";
    }
    else
    {
        ioOut << "=" << *m_netID;
    }
    ioOut << ", targetIsServer=" << m_targetIsServer;
    ioOut << ", udpUseServerPort=" << m_udpUseServerPort;
    ioOut << ", client=" << m_client << "]";
}

string
MediaNetLink::LinkStateToBG(const LinkState& inLinkState)
{
    switch (inLinkState.linkState)
    {
        default:
        case kLinkStateInvalid:
            return "bgblue";

        case kLinkStateDead:
        case kLinkStateNotMade:
            return "bgred";

        case kLinkStateConnecting:
        case kLinkStateWaitingForPort:
        case kLinkStateUntested:
            return "bgyellow";
            
        case kLinkStateTesting:
        case kLinkStateIdle:
            if (inLinkState.linkPingTime > 0)
            {
                return "bggreen";
            }
            else
            {
                return "bgyellow";
            }
    }
}

void
MediaNetLink::WebStatusHeaderPrint(ostream& ioOut)
{
    ioOut << "<tr class=\"bgred\">";
    ioOut << "<td class=\"bold\">Owner</td>";
    ioOut << "<td class=\"bold\">IP:TCP port/UDP port:type</td>";
    ioOut << "<td class=\"bold\">TCP</td>" << endl;
    ioOut << "<td class=\"bold\">UDP</td>" << endl;
    ioOut << "<td class=\"bold\">Age</td></tr>" << endl;
}

void
MediaNetLink::WebStatusPrint(ostream& ioOut) const
{
    ioOut << "<td>";
    if (m_netID == NULL)
    {
        ioOut << "(Unknown)";
    }
    else
    {
        ioOut << *m_netID;
    }
    ioOut << "</td><td>" << MediaNetUtils::IPAddressToString(m_client.RemoteIPGet());
    ioOut << ":" << PlatformNet::NetworkToHostOrderU16(m_client.TCPRemotePortGet());
    ioOut << "/" << PlatformNet::NetworkToHostOrderU16(m_client.UDPRemotePortGet());
    if (m_targetIsServer)
    {
        ioOut << ":client";
    }
    else
    {
        ioOut << ":server";
    }
    ioOut << "</td>";
    ioOut << "<td><font class=\"";
    ioOut << LinkStateToBG(m_tcpState);
    ioOut << "\">" << m_tcpState.linkPingTime << "ms</font></td>";
ioOut << "<td><font class=\"";
    ioOut << LinkStateToBG(m_udpState);
    ioOut << "\">" << m_udpState.linkPingTime << "ms</font></td>";

    m_currentMsec=SDL_GetTicks();
    ioOut << "<td>" << MediaNetUtils::MsecDurationToString(m_currentMsec - m_creationMsec) << "</td>";
    ioOut << endl;
}

string
MediaNetLink::NextLinkNameTake(void)
{
    ostringstream nameStream("link");
    nameStream << m_linkNameNum;
    ++m_linkNameNum;
    return nameStream.str();
}