/*
 * $Id: GameStationDef.h,v 1.1 2002/11/21 18:06:17 southa Exp $
 * $Log: GameStationDef.h,v $
 * Revision 1.1  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
 */

#include "mushCore.h"
#include "mushMedia.h"

class GameStationDef
{
public:
    GameStationDef();
    
    void NameSet(const string& inName) { m_name=inName; }
    const string& NameGet(void) const { return m_name; }
    void AddressSet(const string& inAddress) { m_address=inAddress; }
    const string& AddressGet(void) const { return m_address; }
    void IsServerSet(bool inServer) { m_isServer=inServer; }
    bool IsServer(void) const { return m_isServer; }
    void IPSet(U32 inIP) { m_ip=inIP; }
    U32 IPGet(void) const { return m_ip; }
    void PortSetHostOrder(U32 inPort) { m_port=inPort; }
    U32 PortGet(void) const { return m_port; }
    
private:
    string m_name;
    string m_address;
    U32 m_ip; // Network byte order
    U32 m_port; // Machine order
    bool m_isServer;
};
