/*
 * $Id: MustlLink.cpp,v 1.3 2002/12/13 01:06:53 southa Exp $
 * $Log: MustlLink.cpp,v $
 * Revision 1.3  2002/12/13 01:06:53  southa
 * Mustl work
 *
 * Revision 1.2  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
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

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlNamespace.h"

auto_ptr< CoreData<MustlLink> > CoreData<MustlLink>::m_instance;

U32 MustlLink::m_linkNameNum=1;

MustlLink::MustlLink(const MustlID& inID, const MustlAddress& inAddress)
{
    // I am the client end of the link
    MustlLog::Instance().NetLog() << "Connecting to " << inAddress << endl;

    m_netID = inID.Clone();

    Initialise();
    m_udpUseServerPort=false;


    TCPConnect(inAddress);
    m_tcpState.linkState=kLinkStateConnecting;
    
    UDPConnect(inAddress);
    UDPLinkCheckSend();
}

MustlLink::MustlLink(tSocket inSocket, const MustlAddress& inAddress)
{
    // I am the server end of the link
    m_netID = NULL;

    Initialise();
    m_udpState.linkState=kLinkStateWaitingForPort;
    m_udpUseServerPort=true;

    TCPSocketTake(inSocket, inAddress);
    MustlAddress udpAddress = inAddress;
    udpAddress.PortSetNetworkOrder(0);
    m_client.UDPAddressSet(udpAddress); // We don't know yet
}

void
MustlLink::Initialise(void)
{
    m_currentMsec = MustlTimer::Instance().CurrentMsecGet();
    
    m_creationMsec=m_currentMsec;
    m_lastActivityMsec=m_currentMsec;
    m_lastIDRequestMsec=m_currentMsec;
    
    m_tcpState.linkCheckMsec=0;
    m_tcpState.linkState=kLinkStateUntested;
    m_tcpState.linkCheckState=kLinkCheckStateIdle;
    m_tcpState.linkPingMsec=0;
    m_tcpState.linkErrorsSinceGood=0;
    m_tcpState.linkErrorTotal=0;
    m_tcpState.linkSendCtr=0;
    m_tcpState.linkReceiveCtr=0;
    m_tcpState.linkCheckSeqNum='A';

    m_udpState.linkCheckMsec=0;
    m_udpState.linkState=kLinkStateUntested;
    m_udpState.linkCheckState=kLinkCheckStateIdle;
    m_udpState.linkPingMsec=0;
    m_udpState.linkErrorsSinceGood=0;
    m_udpState.linkErrorTotal=0;
    m_udpState.linkSendCtr=0;
    m_udpState.linkReceiveCtr=0;
    m_udpState.linkCheckSeqNum='M';
    m_syncedID=false;
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
MustlLink::TCPConnect(const MustlAddress& inAddress)
{
    m_client.TCPConnect(inAddress);
    m_targetIsServer=true;
}

void
MustlLink::TCPSocketTake(tSocket inSocket, const MustlAddress& inAddress)
{
    m_client.TCPSocketTake(inSocket, inAddress);
    m_targetIsServer=false;
}

void
MustlLink::UDPConnect(const MustlAddress& inAddress)
{
    MustlAddress localAddress = inAddress;
    U32 failCtr=0;
    do
    {
        try
        {
            // Think about unbound UDP socket?
            m_client.UDPConnect(localAddress);
            break;
        }
        catch (MustlFail& e)
        {
            if (++failCtr > 8)
            {
                throw;
            }

            localAddress.PortSetHostOrder(localAddress.PortGetHostOrder() + 1);
        }
    } while(1);

    if (failCtr > 0)
    {
        MustlLog::Instance().NetLog() << "Selected local UDP port " << localAddress.PortGetHostOrder() << endl;
    }
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
    MUSTLASSERT(false);
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
    MUSTLASSERT(false);
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
    if (m_currentMsec > m_tcpState.linkCheckMsec + kLinkCheckDeadTime ||
        m_currentMsec == 0)
    {
        MustlData data;
        m_tcpState.linkCheckSeqNum++;
        MustlProtocol::TCPLinkCheckCreate(data, m_tcpState.linkCheckSeqNum);
        m_tcpState.linkCheckState = kLinkCheckStateAwaitingReply;
        m_tcpState.linkCheckMsec = m_currentMsec;
        TCPSend(data);
    }
}

void
MustlLink::UDPLinkCheckSend(void)
{
    if (m_currentMsec > m_udpState.linkCheckMsec + kLinkCheckDeadTime ||
        m_currentMsec == 0)
    {
        MustlData data;
        m_udpState.linkCheckSeqNum++;
        MustlProtocol::UDPLinkCheckCreate(data, m_udpState.linkCheckSeqNum);
        m_udpState.linkCheckState = kLinkCheckStateAwaitingReply;
        m_udpState.linkCheckMsec = m_currentMsec;
        UDPSend(data);
    }
}    

void
MustlLink::IDRequestSend(void)
{
    MustlData data;
    MustlProtocol::IDRequestCreate(data);
    ReliableSend(data);
    m_lastIDRequestMsec = m_currentMsec;
}

bool
MustlLink::TCPConnectingCheck(void)
{
    if (m_tcpState.linkState == kLinkStateConnecting)
    {
        if (m_client.TCPConnectionCompleted())
        {
            m_tcpState.linkState = kLinkStateUntested;
            TCPLinkCheckSend();
            return true;
        }
    }
    return false;
}

void
MustlLink::Tick(void)
{
    m_currentMsec = MustlTimer::Instance().CurrentMsecGet();
    
    if (m_currentMsec > m_lastActivityMsec + kLinkIdleTimeoutMsec)
    {
        // Idle timer expired
        Disconnect(MustlProtocol::kReasonCodeIdleTimeout);
    }

    TCPConnectingCheck();
    
    U32 tcpLinkCheckPeriod=kTCPFastLinkCheckPeriod;
    if (m_tcpState.linkState == kLinkStateIdle && m_tcpState.linkErrorsSinceGood == 0)
    {
        tcpLinkCheckPeriod=kTCPSlowLinkCheckPeriod;
    }

    if (LinkIsUpForSend(m_tcpState.linkState) &&
        m_currentMsec > m_tcpState.linkCheckMsec + tcpLinkCheckPeriod)
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
        m_currentMsec > m_udpState.linkCheckMsec + udpLinkCheckPeriod)
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

    // Request ID if necessary
    if (m_netID == NULL && LinkIsUpForSend(m_tcpState.linkState))
    {
        if (m_currentMsec > m_lastIDRequestMsec + kIDRequestPeriod)
        {
            IDRequestSend();
        }        
    }
}

void
MustlLink::TCPLinkEnteredIdle(void)
{
    // Called once as the link enters the idle state
    if (m_netID == NULL && LinkIsUpForSend(m_tcpState.linkState))
    {
        IDRequestSend();
    }
}

void
MustlLink::UDPLinkEnteredIdle(void)
{
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
    return m_syncedID && (m_tcpState.linkState == kLinkStateTesting ||
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
            throw(MustlFail("TCPSend on down link"));
        }
        m_client.TCPSend(ioData);
        ++m_tcpState.linkSendCtr;
    }
    catch (MustlFail& e)
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
            if (!TCPConnectingCheck())
            {
                // Receive on dead link.  Don't raise an exception for this
                return;
            }
        }
        m_client.TCPReceive(outData);
        ++m_tcpState.linkReceiveCtr;
    }
    catch (MustlFail& e)
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
            throw(MustlFail("UDPSend on down link"));
        }
        if (m_udpUseServerPort)
        {
            MustlServer::Instance().UDPSend(m_client.UDPAddressGet(), ioData);
        }
        else
        {
            m_client.UDPSend(ioData);
            ++m_udpState.linkSendCtr;
        }
    }
    catch (MustlFail& e)
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
    catch (MustlFail& e)
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
    m_lastActivityMsec = MustlTimer::Instance().CurrentMsecGet();
;
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
        throw(MustlFail("Send on dead link"));
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
        throw(MustlFail("Send on dead link"));
    }
    TouchLink();
}

bool
MustlLink::UDPIfAddressMatchReceive(bool& outTakeMessage, MustlData& ioData)
{
    if (ioData.SourceGet().HostGetNetworkOrder() == UDPAddressGet().HostGetNetworkOrder() &&
        (UDPAddressGet().HostGetNetworkOrder() == 0 ||
         ioData.SourceGet().PortGetNetworkOrder() == UDPAddressGet().PortGetNetworkOrder())
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
        throw(MustlFail("Net ID for link not set"));
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
    // Assume that this ID is ready to go
    m_syncedID = true;
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
    m_currentMsec = MustlTimer::Instance().CurrentMsecGet();

    U32 seqNum = ioData.MessageBytePop();
    if (seqNum == m_tcpState.linkCheckSeqNum &&
        m_tcpState.linkCheckState == kLinkCheckStateAwaitingReply)
    {
        m_tcpState.linkPingMsec=m_currentMsec - m_tcpState.linkCheckMsec;
        if (m_tcpState.linkState == kLinkStateUntested ||
            m_tcpState.linkState == kLinkStateTesting)
        {
            m_tcpState.linkState = kLinkStateIdle;
            if (m_udpState.linkState == kLinkStateIdle) LinkInfoLog();
            TCPLinkEnteredIdle();
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
        UDPConnect(ioData.SourceGet());
        m_udpState.linkState=kLinkStateUntested;
    }
    
    if (m_udpState.linkState == kLinkStateWaitingForPort)
    {
        m_client.UDPAddressSet(ioData.SourceGet());
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
    m_currentMsec = MustlTimer::Instance().CurrentMsecGet();

    U32 seqNum = ioData.MessageBytePop();
    if (seqNum == m_udpState.linkCheckSeqNum &&
        m_udpState.linkCheckState == kLinkCheckStateAwaitingReply)
    {
        m_udpState.linkPingMsec=m_currentMsec - m_udpState.linkCheckMsec;
        if (m_udpState.linkState == kLinkStateUntested ||
            m_udpState.linkState == kLinkStateTesting)
        {
            m_udpState.linkState = kLinkStateIdle;
            if (m_tcpState.linkState == kLinkStateIdle) LinkInfoLog();
            UDPLinkEnteredIdle();
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
        // Once we send our ID the link should be ready
        m_syncedID = true;
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
    ioOut << ", netID";
    if (m_netID == NULL)
    {
        ioOut << " is NULL";
    }
    else
    {
        ioOut << "=" << *m_netID;
    }
    ioOut << ", syncedID=" << m_syncedID;
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
            return "bggreen";
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
    ioOut << "</td><td>";
    ioOut << MustlUtils::IPAddressToString(m_client.TCPAddressGet().HostGetNetworkOrder()) << ":";
    ioOut << m_client.TCPAddressGet().PortGetHostOrder() << "/";
    if (m_client.TCPAddressGet().HostGetNetworkOrder() != m_client.UDPAddressGet().HostGetNetworkOrder())
    {
        ioOut << MustlUtils::IPAddressToString(m_client.UDPAddressGet().HostGetNetworkOrder()) << ":";
    }
    ioOut << m_client.UDPAddressGet().PortGetHostOrder();
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
    ioOut << "\">" << m_tcpState.linkPingMsec << "ms</font></td>";
ioOut << "<td><font class=\"";
    ioOut << LinkStateToBG(m_udpState);
    ioOut << "\">" << m_udpState.linkPingMsec << "ms</font></td>";

    m_currentMsec = MustlTimer::Instance().CurrentMsecGet();
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
