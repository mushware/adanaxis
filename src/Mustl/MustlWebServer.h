#ifndef MUSTLWEBSERVER_H
#define MUSTLWEBSERVER_H
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
 * $Id: MustlWebServer.h,v 1.6 2003/01/15 13:27:33 southa Exp $
 * $Log: MustlWebServer.h,v $
 * Revision 1.6  2003/01/15 13:27:33  southa
 * Static library linking fixes
 *
 * Revision 1.5  2002/12/29 20:30:57  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/17 12:53:35  southa
 * Mustl library
 *
 * Revision 1.2  2002/12/12 18:38:26  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:27  southa
 * Created Mustl
 *
 * Revision 1.6  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
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

#include "MustlStandard.h"

#include "MustlMushcoreSingleton.h"

class MustlData;

class MustlWebServer : public MushcoreSingleton<MustlWebServer>
{
public:
    typedef bool (*tPermissionFunction)(const std::string& inAddress);
    
    enum tPermission
    {
        kPermissionInvalid,
        kPermissionNone,
        kPermissionLocal,
        kPermissionAll
    };

    MustlWebServer();
    ~MustlWebServer();

    void Connect(Mustl::U32 inPort);
    void Disconnect(void);
    void Accept(void);
    bool IsConnected(void) const;
    void PermissionSet(tPermission inPermission) { m_permission=inPermission; }
    void ExtraAllowedAddrSet(const std::string& inAddr);
    void PermissionFunctionSet(tPermissionFunction inFunction); 

    static void NullFunction(void);
    
protected:
    bool CheckIPAddressAllowed(Mustl::U32 inIPNetworkOrder);

private:
    Mustl::tSocket m_tcpSocket;
    Mustl::U32 m_linkCtr;
    std::map<Mustl::U32, bool> m_permissionMap;
    std::string m_extraAllowedAddr;
    Mustl::U32 m_extraAllowedIP;
    tPermission m_permission;
    tPermissionFunction m_permissionFunction;
    
    bool m_serving;
};

#endif
