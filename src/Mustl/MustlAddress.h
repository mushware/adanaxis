#ifndef MUSTLADDRESS_H
#define MUSTLADDRESS_H
/*
 * $Id: MustlAddress.h,v 1.3 2002/11/28 15:14:14 southa Exp $
 * $Log: MustlAddress.h,v $
 * Revision 1.3  2002/11/28 15:14:14  southa
 * Multiplayer setup timing
 *
 * Revision 1.2  2002/11/28 12:05:46  southa
 * Server name work
 *
 * Revision 1.1  2002/11/27 13:23:27  southa
 * Server and client data exchange
 *
 */

#include "mushCore.h"

class MustlAddress
{
public:
    MustlAddress() :
        m_ip(0),
        m_port(0)
    {}

    MustlAddress(U32 inHostNetworkOrder, U32 inPortNetworkOrder) :
        m_ip(inHostNetworkOrder),
        m_port(inPortNetworkOrder)
    {}

    string HostStringGet(void) const;
    U32 HostGetNetworkOrder(void) const { return m_ip; }
    U32 PortGetNetworkOrder(void) const { return m_port; }
    U32 PortGetHostOrder(void) const;

    void ResolveFrom(const string& inHost, U32 inPortHostOrder);
    
    void Print(ostream& ioOut) const;

    bool Equals(const MustlAddress& inAddress) const;
    
private:
    U32 m_ip;
    U32 m_port;
};

inline bool
MustlAddress::Equals(const MustlAddress& inAddress) const
{
    return m_ip == inAddress.HostGetNetworkOrder() &&
           m_port == inAddress.PortGetNetworkOrder();
}

inline bool
operator==(const MustlAddress& a, const MustlAddress& b)
{
    return a.Equals(b);
}

inline ostream&
operator<<(ostream &ioOut, const MustlAddress& inLink)
{
    inLink.Print(ioOut);
    return ioOut;
}
#endif
