#ifndef MEDIANETWEBSERVER_H
#define MEDIANETWEBSERVER_H
/*
 * $Id: MediaNetWebServer.h,v 1.5 2002/11/24 12:57:02 southa Exp $
 * $Log: MediaNetWebServer.h,v $
 * Revision 1.5  2002/11/24 12:57:02  southa
 * Added configuration host protection
 *
 * Revision 1.4  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.3  2002/11/21 18:06:18  southa
 * Non-blocking network connection
 *
 * Revision 1.2  2002/11/15 18:58:34  southa
 * Configuration mode
 *
 * Revision 1.1  2002/11/05 18:15:19  southa
 * Web server
 *
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaNetData;

class MediaNetWebServer
{
public:
    enum tPermission
    {
        kPermissionInvalid,
        kPermissionNone,
        kPermissionLocal,
        kPermissionAll
    };

    ~MediaNetWebServer();

    static inline MediaNetWebServer& Instance(void);

    void Connect(U32 inPort);
    void Disconnect(void);
    void Accept(void);
    bool IsConnected(void) const;
    void PermissionSet(tPermission inPermission) { m_permission=inPermission; }
    void ExtraAllowedAddrSet(const string& inAddr);
    
protected:
    MediaNetWebServer();
    bool CheckIPAddressAllowed(U32 inIPNetworkOrder);

private:
    TCPsocket m_tcpSocket;
    U32 m_linkCtr;
    map<U32, bool> m_permissionMap;
    string m_extraAllowedAddr;
    U32 m_extraAllowedIP;
    tPermission m_permission;
    
    bool m_serving;

    static auto_ptr<MediaNetWebServer> m_instance;
};

inline  MediaNetWebServer&
MediaNetWebServer::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MediaNetWebServer);
    return *m_instance;
}
#endif
