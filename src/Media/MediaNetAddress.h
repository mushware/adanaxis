#ifndef MEDIANETADDRESS_H
#define MEDIANETADDRESS_H
/*
 * $Id$
 * $Log$
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
