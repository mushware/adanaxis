/*
 *  MediaNetServer.cpp
 *  core-app
 *
 *  Created by Andy Southgate on Thu Oct 31 2002.
 *  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
 *
 */

#include "MediaNetServer.h"

#include "MediaNet.h"

MediaNetServer::MediaNetServer(U32 inPort)
{
    MediaNet::Instance();
    
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
}

MediaNetServer::~MediaNetServer()
{
    SDLNet_TCP_Close(m_tcpSocket);
}


void
MediaNetServer::Accept(void)
{
    TCPsocket newSocket=SDLNet_TCP_Accept(m_tcpSocket);
    if (newSocket != NULL)
    {
        IPaddress *remoteIP = SDLNet_TCP_GetPeerAddress(newSocket);
        if (remoteIP != NULL)
        {
            m_clients.push_back();
            m_clients.back().remoteIP = *remoteIP;
            m_clients.back().remoteSocket = newSocket;
            char *remoteName=SDLNet_ResolveIP(remoteIP);
            cout << "Connection from ";
            if (remoteName != NULL)
            {
                cout << remoteName;
            }
            else
            {
                cout << "unknown";
            }
            cout << " accepted" << endl;
        }
        else
        {
            static U32 errCtr=0;
            if (errCtr++ < 100)
            {
                cerr << "Couldn't get IP for connection attempt: " << SDLNet_GetError() << endl;
            }
        }
    }
}
        