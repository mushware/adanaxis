/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MustlWebServer.cpp,v 1.7 2002/12/29 21:00:00 southa Exp $
 * $Log: MustlWebServer.cpp,v $
 * Revision 1.7  2002/12/29 21:00:00  southa
 * More build fixes
 *
 * Revision 1.6  2002/12/29 20:30:57  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.5  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/12/17 12:53:35  southa
 * Mustl library
 *
 * Revision 1.3  2002/12/17 00:58:29  southa
 * Added support for libmustl target
 *
 * Revision 1.2  2002/12/12 18:38:26  southa
 * Mustl separation
 *
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
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "mustlCore.h"

using namespace Mustl;
using namespace std;

auto_ptr<MustlWebServer> MustlWebServer::m_instance;

MustlWebServer::MustlWebServer() :
    m_linkCtr(0),
    m_permission(kPermissionLocal),
    m_permissionFunction(NULL),
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

    MustlAddress netAddress;

    MustlPlatform::ResolveHostName(netAddress, "", inPort);

    m_tcpSocket = MustlPlatform::TCPBindNonBlocking(netAddress);
    
    MustlLog::Instance().WebLog() << "Created web server on port " << inPort << endl;
    m_serving=true;
}

void
MustlWebServer::Disconnect(void)
{
    if (m_serving)
    {
        MUSTLASSERT(m_tcpSocket != NULL);
        MustlPlatform::SocketClose(m_tcpSocket);
        m_tcpSocket = NULL;
        m_serving=false;
    }
}
        
MustlWebServer::~MustlWebServer()
{
    if (m_serving)
    {
        MUSTLASSERT(m_tcpSocket != NULL);
        MustlPlatform::SocketClose(m_tcpSocket);
    }
    MustlLog::Instance().WebLog() << "Closed web server" << endl;
}

void
MustlWebServer::Accept(void)
{
    if (m_serving)
    {
        MUSTLASSERT(m_tcpSocket != NULL);
        MustlAddress remoteAddress;
        tSocket newSocket;
        if (MustlPlatform::Accept(newSocket, remoteAddress, m_tcpSocket))
        {
            U32 remoteHost=remoteAddress.HostGetNetworkOrder();
            if (CheckIPAddressAllowed(remoteHost))
            {
                ostringstream name;
                name << "web" << m_linkCtr;
                MushcoreData<MustlWebLink>::Instance().Give(name.str(), new MustlWebLink(newSocket));
                m_linkCtr++;
                MustlLog::Instance().WebLog() << "Accepted web connection " << name.str() << endl;
            }
            else
            {
                MustlPlatform::SocketClose(newSocket);
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

        MustlAddress netAddress;
        try
        {
            MustlPlatform::ResolveHostName(netAddress, inAddr, 0);
            m_extraAllowedIP = netAddress.HostGetNetworkOrder();
        }
        catch (MustlFail& e)
        {
            m_extraAllowedIP = 0;
            throw(MustlFail("Could not resolve host name '"+inAddr+"', entered as the Extra Allowed Configuration address: " + e.what()));
        }
    }
}

void
MustlWebServer::PermissionFunctionSet(tPermissionFunction inFunction)
{
    m_permissionFunction = inFunction;
}

bool
MustlWebServer::CheckIPAddressAllowed(U32 inIPNetworkOrder)
{
    bool retVal=false;
    bool askUser=false;
    
    switch (m_permission)
    {
        case kPermissionNone:
            askUser=true;
            break;

        case kPermissionLocal:
            if (MustlPlatform::IsLocalAddress(inIPNetworkOrder))
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
            throw(MustlFail("Bad value for MustlWebServer::m_permission"));
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
                if (m_permissionFunction == NULL)
                {
                    retVal = false;
                }
                else
                {
                    retVal = m_permissionFunction(MustlUtils::IPAddressToString(inIPNetworkOrder));
                }

                if (!retVal && MustlPlatform::IsLocalAddress(inIPNetworkOrder))
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
