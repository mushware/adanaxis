#ifndef MEDIANETADDRESS_H
#define MEDIANETADDRESS_H
/*
 * $Id: MediaNetAddress.h,v 1.1 2002/11/27 13:23:27 southa Exp $
 * $Log: MediaNetAddress.h,v $
 * Revision 1.1  2002/11/27 13:23:27  southa
 * Server and client data exchange
 *
 */

#include "mushCore.h"

class MediaNetAddress
{
public:
    MediaNetAddress() :
        m_ip(0),
        m_port(0)
    {}

    MediaNetAddress(U32 inHostNetworkOrder, U32 inPortNetworkOrder) :
        m_ip(inHostNetworkOrder),
        m_port(inPortNetworkOrder)
    {}

    string HostStringGet(void) const;
    U32 HostGetNetworkOrder(void) const { return m_ip; }
    U32 PortGetNetworkOrder(void) const { return m_port; }
    U32 PortGetHostOrder(void) const;

    void ResolveFrom(const string& inHost, U32 inPortHostOrder);
    
    void Print(ostream& ioOut) const;
    
private:
    U32 m_ip;
    U32 m_port;
};

inline ostream&
operator<<(ostream &ioOut, const MediaNetAddress& inLink)
{
    inLink.Print(ioOut);
    return ioOut;
}
#endif
