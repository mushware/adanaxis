/*
 * $Id: MustlLink.cpp,v 1.27 2002/12/10 20:38:05 southa Exp $
 * $Log: MustlLink.cpp,v $
 * Revision 1.27  2002/12/10 20:38:05  southa
 * Server timing
 *
 * Revision 1.26  2002/12/09 23:59:59  southa
 * Network control
 *
 * Revision 1.25  2002/12/09 16:18:00  southa
 * Link ID transfer
 *
 * Revision 1.24  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
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

#include "MustlLink.h"

#include "MustlID.h"
#include "MustlLog.h"
#include "MustlProtocol.h"
#include "MustlServer.h"
#include "MustlUtils.h"

#include "mushPlatform.h"

auto_ptr< CoreData<MustlLink> > CoreData<MustlLink>::m_instance;

U32 MustlLink::m_linkNameNum=1;

MustlLink::MustlLink(const MustlID& inID, const string& inServer, U32 inPort)
{
    // I am the client end of the link
    m_netID = inID.Clone();
    Initialise();
    m_udpUseServerPort=false;
    MustlLog::Instance().NetLog() << "Connecting to " << inServer << ":" << inPort << endl;
    TCPConnect(inServer, inPort);
    m_tcpState.linkState=kLinkStateConnecting;
    
    UDPConnect(inPort);
    m_client.UDPRemotePortNetworkOrderSet(PlatformNet::HostToNetworkOrderU16(inPort));
    UDPLinkCheckSend();
    m_targetName=inServer;
}

MustlLink::MustlLink(const MustlID& inID, const MustlAddress& inAddress)
{
    // I am the client end of the link
    m_netID = inID.Clone();
    Initialise();
    m_udpUseServerPort=false;
    string serverName=inAddress.HostStringGet();
    U32 portNum=inAddress.PortGetHostOrder();
MustlLog::Instance().NetLog() << "Connecting to " << serverName << ":" << portNum << endl;
    TCPConnect(serverName, portNum);
    m_tcpState.linkState=kLinkStateConnecting;

    UDPConnect(portNum);
    m_client.UDPRemotePortNetworkOrderSet(PlatformNet::HostToNetworkOrderU16(portNum));
    UDPLinkCheckSend();
    m_targetName=serverName;
}

MustlLink::MustlLink(TCPsocket inSocket, U32 inPort)
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
MustlLink::Initialise(void)
{
    m_currentMsec=SDL_GetTicks();
    m_creationMsec=m_currentMsec;
    m_lastActivityMsec=m_currentMsec;
    m_lastIDRequestMsec=m_currentMsec;
    
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

MustlLink::~MustlLink()
{
    if (m_netID != NULL)
    {
        delete m_netID;
    }
}

void
MustlLink::TCPConnect(const string& inServer, U32 inPort)
{
    m_client.TCPConnect(inServer, inPort);
    m_targetIsServer=true;
}

void
MustlLink::TCPSocketTake(TCPsocket inSocket)
{
    m_client.TCPSocketTake(inSocket);
    m_targetIsServer=false;
}

void
MustlLink::UDPConnect(U32 inPort)
{
    m_client.UDPConnect(inPort);
}

void
MustlLink::Disconnect(MustlProtocol::tReasonCode inCode)
{
    if (m_tcpState.linkState != kLinkStateDead ||
        m_udpState.linkState != kLinkStateDead)
    {
        MustlLog::Instance().NetLog() << "Link closing reasonCode=" << inCode << ": " << *this << endl;
    }
    
    try
    {
        if (m_tcpState.linkState != kLinkStateDead)
        {
            MustlData data;
            MustlProtocol::KillLinkCreate(data, inCode);
            TCPSend(data);
        }
    }
    catch (exception& e)
    {
        MustlLog::Instance().NetLog() << "TCP link disconnect exception: " << e.what() << endl;
    }
    
    try
    {
        if (m_udpState.linkState != kLinkStateDead)
        {
            MustlData data;
            MustlProtocol::KillLinkCreate(data, inCode);
            UDPSend(data);
        }
    }
    catch (exception& e)
    {
        MustlLog::Instance().NetLog() << "UDP link disconnect exception: " << e.what() << endl;
    }
    
    m_client.TCPDisconnect();
    m_client.UDPDisconnect();
    
    m_tcpState.linkState=kLinkStateDead;
    m_udpState.linkState=kLinkStateDead;
}

bool
MustlLink::LinkIsUpForSend(tLinkState inState)
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
MustlLink::LinkIsUpForReceive(tLinkState inState)
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
MustlLink::LinkChecksSend(void)
{
    TCPLinkCheckSend();
    UDPLinkCheckSend();
}

void
MustlLink::TCPLinkCheckSend(void)
{
    if (m_currentMsec > m_tcpState.linkCheckTime + kLinkCheckDeadTime)
    {
        MustlData data;
        m_tcpState.linkCheckSeqNum++;
        MustlProtocol::TCPLinkCheckCreate(data, m_tcpState.linkCheckSeqNum);
        m_tcpState.linkCheckState = kLinkCheckStateAwaitingReply;
        m_tcpState.linkCheckTime = m_currentMsec;
        TCPSend(data);
    }
}

void
MustlLink::UDPLinkCheckSend(void)
{
    if (m_currentMsec > m_udpState.linkCheckTime + kLinkCheckDeadTime)
    {
        MustlData data;
        m_udpState.linkCheckSeqNum++;
        MustlProtocol::UDPLinkCheckCreate(data, m_udpState.linkCheckSeqNum);
        m_udpState.linkCheckState = kLinkCheckStateAwaitingReply;
        m_udpState.linkCheckTime = m_currentMsec;
        UDPSend(data);
    }
}    

void
MustlLink::IDRequestSend(void)
{
    if (m_currentMsec > m_lastIDRequestMsec + kIDRequestPeriod)
    {
        MustlData data;
        MustlProtocol::IDRequestCreate(data);
        ReliableSend(data);
        m_lastIDRequestMsec = m_currentMsec;
    }
}

void
MustlLink::Tick(void)
{
    m_currentMsec=SDL_GetTicks();
    
    if (m_currentMsec > m_lastActivityMsec + kLinkIdleTimeoutMsec)
    {
        // Idle timer expired
        Disconnect(MustlProtocol::kReasonCodeIdleTimeout);
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
            MustlLog::Instance().NetLog() << "TCP link check failed" << endl;
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
            MustlLog::Instance().NetLog() << "UDP link check failed" << endl;
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

    if (m_netID == NULL && LinkIsUpForSend(m_tcpState.linkState))
    {
        IDRequestSend();
    }
}

bool
MustlLink::LinkDeathCheck(LinkState& ioLinkState)
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
MustlLink::IsDead(void)
{
    return m_tcpState.linkState == kLinkStateDead &&
           m_udpState.linkState == kLinkStateDead;
}

bool
MustlLink::ReadyIs(void) const
{
    return (m_tcpState.linkState == kLinkStateTesting ||
            m_tcpState.linkState == kLinkStateIdle ||
            m_udpState.linkState == kLinkStateTesting ||
            m_udpState.linkState == kLinkStateIdle);
}

void
MustlLink::TCPSend(MustlData& ioData)
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
        MustlLog::Instance().NetLog() << "TCPSend exception: " << e.what() << endl;
        if (m_tcpState.linkErrorTotal == 0)
        {
            MustlLog::Instance().VerboseLog() << "TCPSend: Failed link=" << *this << endl;
        } 
        ++m_tcpState.linkErrorTotal;
        ++m_tcpState.linkErrorsSinceGood;
    }
}

void
MustlLink::TCPReceive(MustlData& outData)
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
        MustlLog::Instance().NetLog() << "TCPReceive exception: " << e.what() << endl;
        if (m_tcpState.linkErrorTotal == 0)
        {
            MustlLog::Instance().VerboseLog() << "TCPReceive: Failed link=" << *this << endl;
        }        
        ++m_tcpState.linkErrorTotal;
        ++m_tcpState.linkErrorsSinceGood;
    }
}

void
MustlLink::UDPSend(MustlData& ioData)
{
    try
    {
        if (!LinkIsUpForSend(m_udpState.linkState))
        {
            throw(NetworkFail("UDPSend on down link"));
        }
        if (m_udpUseServerPort)
        {
            MustlServer::Instance().UDPSend(m_client.RemoteIPGet(), m_client.UDPRemotePortGet(), ioData);
        }
        else
        {
            m_client.UDPSend(ioData);
            ++m_udpState.linkSendCtr;
        }
    }
    catch (NetworkFail& e)
    {
        MustlLog::Instance().NetLog() << "UDPSend exception: " << e.what() << endl;
        if (m_udpState.linkErrorTotal == 0)
        {
            MustlLog::Instance().VerboseLog() << "UDPSend: Failed link=" << *this << endl;
        }
        ++m_udpState.linkErrorTotal;
        ++m_udpState.linkErrorsSinceGood;
    }
}

void
MustlLink::UDPReceive(MustlData& outData)
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
        MustlLog::Instance().NetLog() << "UDPReceive exception: " << e.what() << endl;
        if (m_udpState.linkErrorTotal == 0)
        {
            MustlLog::Instance().VerboseLog() << "UDPReceive: Failed link=" << *this << endl;
        }
        ++m_udpState.linkErrorTotal;
        ++m_udpState.linkErrorsSinceGood;
    }
}

void
MustlLink::TouchLink(void)
{
    m_lastActivityMsec = SDL_GetTicks();
}

void
MustlLink::FastSend(MustlData& ioData)
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
    TouchLink();
}

void
MustlLink::ReliableSend(MustlData& ioData)
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
    TouchLink();
}

bool
MustlLink::UDPIfAddressMatchReceive(bool& outTakeMessage, MustlData& ioData)
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
        MustlProtocol::Unpack(ioData);
        outTakeMessage=MustlProtocol::MessageTake(ioData);
        return true;
    }
    else
    {
        outTakeMessage=false;
        return false;
    }
}

bool
MustlLink::Receive(MustlData * & outData)
{

    UDPReceive(m_udpState.linkData);
    if (!m_udpState.linkData.IsEmptyForRead())
    {
        MustlProtocol::Unpack(m_udpState.linkData);
        if (MustlProtocol::MessageTake(m_udpState.linkData))
        {
            outData = &m_udpState.linkData;
            return true;
        }
    }
    
    TCPReceive(m_tcpState.linkData);
    if (!m_tcpState.linkData.IsEmptyForRead())
    {
        MustlProtocol::Unpack(m_tcpState.linkData);
        if (MustlProtocol::MessageTake(m_tcpState.linkData))
        {
            outData = &m_tcpState.linkData;
            return true;
        }
    }
    
    return false;
}

const MustlID&
MustlLink::NetIDGet(void) const
{
    if (m_netID == NULL)
    {
        throw(ReferenceFail("Net ID for link not set"));
    }
    return *m_netID;
}

void
MustlLink::NetIDSet(const MustlID& inID)
{
    if (m_netID != NULL)
    {
        delete m_netID;
    }
    m_netID = inID.Clone();
}

void
MustlLink::MessageHandle(U32 inType, MustlData& ioData)
{
    switch (inType)
    {
        case MustlProtocol::kMessageTypeTCPLinkCheck:
            MessageTCPLinkCheckHandle(ioData);
            break;

        case MustlProtocol::kMessageTypeTCPLinkCheckReply:
            MessageTCPLinkCheckReplyHandle(ioData);
            break;

        case MustlProtocol::kMessageTypeUDPLinkCheck:
            MessageUDPLinkCheckHandle(ioData);
            break;

        case MustlProtocol::kMessageTypeUDPLinkCheckReply:
            MessageUDPLinkCheckReplyHandle(ioData);
            break;

        case MustlProtocol::kMessageTypeKillLink:
            MessageKillLinkHandle(ioData);
            break;

        case MustlProtocol::kMessageTypeIDRequest:
            MessageIDRequestHandle(ioData);
            break;

        default:
            MustlLog::Instance().NetLog() << "Discarding type " << inType << " link layer message" << endl; 
            break;
    }
}

void
MustlLink::MessageTCPLinkCheckHandle(MustlData& ioData)
{
    U8 seqNum = ioData.MessageBytePop();
    
    MustlData replyData;
    MustlProtocol::TCPLinkCheckReplyCreate(replyData, seqNum);
    TCPSend(replyData);

    if (m_tcpState.linkState == kLinkStateUntested)
    {
        TCPLinkCheckSend();
    }
}

void
MustlLink::MessageTCPLinkCheckReplyHandle(MustlData& ioData)
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
        MustlLog::Instance().VerboseLog() << "TCP link check good" << endl;
    }
}

void
MustlLink::MessageUDPLinkCheckHandle(MustlData& ioData)
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
    MustlData replyData;
    MustlProtocol::UDPLinkCheckReplyCreate(replyData, seqNum);
    UDPSend(replyData);

    if (m_udpState.linkState == kLinkStateUntested)
    {
        UDPLinkCheckSend();
    }
}

void
MustlLink::MessageUDPLinkCheckReplyHandle(MustlData& ioData)
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
        MustlLog::Instance().VerboseLog() << "UDP link check good" << endl;
    }
}

void
MustlLink::MessageKillLinkHandle(MustlData& ioData)
{
    U32 reasonCode = ioData.MessageBytePop();
    MustlLog::Instance().VerboseLog() << "Link kill received (" << reasonCode << ")" << endl;
    if (reasonCode != MustlProtocol::kReasonCodePeerDisconnected)
    {
        Disconnect(MustlProtocol::kReasonCodePeerDisconnected);
    }
}

void
MustlLink::MessageIDRequestHandle(MustlData& ioData)
{
    if (m_netID == NULL)
    {
                    MustlLog::Instance().NetLog() << "No ID present to answer to ID request" << endl;
    }
    else
    {
        MustlData netData;
        MustlProtocol::IDTransferCreate(netData, *m_netID);
        ReliableSend(netData);
    }
}

void
MustlLink::LinkInfoLog(void) const
{
    if (!m_loggedLinkInfo)
    {
        MustlLog::Instance().VerboseLog() << "Link: " << *this << endl;
    }
    m_loggedLinkInfo=true;
}

void
MustlLink::Print(ostream& ioOut) const
{
    ioOut << "[tcpState=" << m_tcpState << ", udpState=" << m_udpState;
    ioOut << ", currentMsec=" << m_currentMsec << ", creationMsec =" << m_creationMsec;
    ioOut  << ", lastActivityMsec=" << m_lastActivityMsec << ", lastIDRequestMsec=" << m_lastIDRequestMsec;
    ioOut << ", targetName=" << m_targetName << ", netID";
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
MustlLink::LinkStateToBG(const LinkState& inLinkState)
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
MustlLink::WebStatusHeaderPrint(ostream& ioOut)
{
    ioOut << "<tr class=\"bgred\">";
    ioOut << "<td class=\"bold\">Owner</td>";
    ioOut << "<td class=\"bold\">IP:TCP port/UDP port:type</td>";
    ioOut << "<td class=\"bold\">TCP</td>" << endl;
    ioOut << "<td class=\"bold\">UDP</td>" << endl;
    ioOut << "<td class=\"bold\">Age</td></tr>" << endl;
}

void
MustlLink::WebStatusPrint(ostream& ioOut) const
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
    ioOut << "</td><td>" << MustlUtils::IPAddressToString(m_client.RemoteIPGet());
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
    ioOut << "<td>" << MustlUtils::MsecDurationToString(m_currentMsec - m_creationMsec) << "</td>";
    ioOut << endl;
}

string
MustlLink::NextLinkNameTake(void)
{
    ostringstream nameStream("link");
    nameStream << m_linkNameNum;
    ++m_linkNameNum;
    return nameStream.str();
}