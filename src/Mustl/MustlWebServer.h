//%includeGuardStart {
#ifndef MUSTLWEBSERVER_H
#define MUSTLWEBSERVER_H
//%includeGuardStart } UGjFcNOZGQARbjvBlq1cfQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlWebServer.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } NWN8pE6ocEw7eATVIZentw
/*
 * $Id: MustlWebServer.h,v 1.13 2006/06/01 15:39:56 southa Exp $
 * $Log: MustlWebServer.h,v $
 * Revision 1.13  2006/06/01 15:39:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.11  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.10  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.9  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:09:33  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
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

#include "MustlMushcore.h"

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

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
