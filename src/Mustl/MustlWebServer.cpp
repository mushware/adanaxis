/*
 * $Id: MustlWebServer.cpp,v 1.9 2002/12/05 13:20:13 southa Exp $
 * $Log: MustlWebServer.cpp,v $
 * Revision 1.9  2002/12/05 13:20:13  southa
 * Client link handling
 *
 * Revision 1.8  2002/11/24 12:57:02  southa
 * Added configuration host protection
 *
 * Revision 1.7  2002/11/24 00:29:08  southa
 * Serve web pages to local addresses only
 *
 * Revision 1.6  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.5  2002/11/22 11:42:07  southa
 * Added developer controls
 *
 * Revision 1.4  2002/11/18 21:02:40  southa
 * Prevent crash on exit
 *
 * Revision 1.3  2002/11/15 18:58:34  southa
 * Configuration mode
 *
 * Revision 1.2  2002/11/06 14:16:57  southa
 * Basic web server
 *
 * Revision 1.1  2002/11/05 18:15:18  southa
 * Web server
 *
 */

#include "MustlWebServer.h"

#include "Mustl.h"
#include "MustlLog.h"
#include "MustlWebLink.h"

#include "mushPlatform.h"

auto_ptr<MustlWebServer> MustlWebServer::m_instance;

MustlWebServer::MustlWebServer() :
    m_linkCtr(0),
    m_permission(kPermissionLocal),
    m_serving(false)
{
}

void
MustlWebServer::Connect(U32 inPort)
{
    if (m_serving)
    {
        Disconnect();
    }

    Mustl::Instance();

    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, NULL, inPort) == -1)
    {
        ostringstream message;
        message << "Server creation failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }

    m_tcpSocket=SDLNet_TCP_Open(&ip);

    if (m_tcpSocket == NULL)
    {
        ostringstream message;
        message << "Server creation failed: " << SDLNet_GetError();
        throw(NetworkFail(message.str()));
    }

    MustlLog::Instance().WebLog() << "Created web server on port " << inPort << endl;
    m_serving=true;
}

void
MustlWebServer::Disconnect(void)
{
    if (m_serving)
    {
        SDLNet_TCP_Close(m_tcpSocket);
        m_tcpSocket = NULL;
        m_serving=false;
    }
}
        
MustlWebServer::~MustlWebServer()
{
    if (m_serving)
    {
        COREASSERT(m_tcpSocket != NULL);
        SDLNet_TCP_Close(m_tcpSocket);
    }
    MustlLog::Instance().WebLog() << "Closed web server" << endl;
}

void
MustlWebServer::Accept(void)
{
    if (m_serving)
    {
        COREASSERT(m_tcpSocket != NULL);
        TCPsocket newSocket=SDLNet_TCP_Accept(m_tcpSocket);
        if (newSocket != NULL)
        {
            IPaddress *remoteIP;

            remoteIP = SDLNet_TCP_GetPeerAddress(newSocket);
            if (remoteIP == NULL)
            {
                throw(NetworkFail(string("Couldn't resolve IP for socket: ")+SDLNet_GetError()));
            }
            U32 remoteHost=remoteIP->host;
            if (CheckIPAddressAllowed(remoteHost))
            {
                ostringstream name;
                name << "web" << m_linkCtr;
                CoreData<MustlWebLink>::Instance().Give(name.str(), new MustlWebLink(newSocket));
                m_linkCtr++;
                MustlLog::Instance().WebLog() << "Accepted web connection " << name.str() << endl;
            }
            else
            {
                SDLNet_TCP_Close(newSocket);
                MustlLog::Instance().WebLog() << "Rejected web connection from prohibited IP address " << MustlUtils::IPAddressToLogString(remoteHost) << endl;
            }
        }
    }
}

bool
MustlWebServer::IsConnected(void) const
{
    return m_serving;
}

void
MustlWebServer::ExtraAllowedAddrSet(const string& inAddr)
{
    if (inAddr != m_extraAllowedAddr)
    {
        m_extraAllowedAddr=inAddr;

        IPaddress remoteIP;
        char buffer[strlen(inAddr.c_str())+1];
        strncpy(buffer, inAddr.c_str(), strlen(inAddr.c_str())+1);

        if (SDLNet_ResolveHost(&remoteIP, buffer, 0) == -1)
        {
            PlatformMiscUtils::MinorErrorBox("Could not resolve host name '"+inAddr+"', entered as the Extra Allowed Configuration address");
            m_extraAllowedIP = 0;
        }
        else
        {
            m_extraAllowedIP = remoteIP.host;
        }
    }
}

bool
MustlWebServer::CheckIPAddressAllowed(U32 inIPNetworkOrder)
{
    bool retVal;
    bool askUser=false;
    
    switch (m_permission)
    {
        case kPermissionNone:
            askUser=true;
            break;

        case kPermissionLocal:
            if (PlatformNet::IsLocalAddress(inIPNetworkOrder))
            {
                retVal=true;
            }
            else
            {
                askUser=true;
            }
            break;

        case kPermissionAll:
            retVal=true;
            break;

        default:
            throw(LogicFail("Bad value for MustlWebServer::m_permission"));
    }

    if (askUser)
    {
        if (inIPNetworkOrder == m_extraAllowedIP && m_extraAllowedAddr.size() != 0)
        {
            // This is the extra allowed address
            retVal = true;
        }
        else
        {
            map<U32, bool>::const_iterator p = m_permissionMap.find(inIPNetworkOrder);
            if (p != m_permissionMap.end())
            {
                retVal = p->second;
            }
            else
            {
                ostringstream message;
                message << "A computer with IP address " << MustlUtils::IPAddressToString(inIPNetworkOrder);
                message << " is attempting to connect to the " << CoreInfo::ApplicationNameGet() << " localweb server.  Would you like to allow this?  If in doubt, choose Deny.";
                retVal=PlatformMiscUtils::PermissionBox(message.str(), false);
    
                if (!retVal && PlatformNet::IsLocalAddress(inIPNetworkOrder))
                {
                    // Don't store denied permission for local addresses
                }
                else
                {
                    m_permissionMap[inIPNetworkOrder] = retVal;
                }
            }
        }
    }
    return retVal;
}
