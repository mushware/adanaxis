#ifndef MUSTLADDRESS_H
#define MUSTLADDRESS_H
/*
 * $Id: MustlAddress.h,v 1.3 2002/12/13 19:03:04 southa Exp $
 * $Log: MustlAddress.h,v $
 * Revision 1.3  2002/12/13 19:03:04  southa
 * Mustl interface cleanup
 *
 * Revision 1.2  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
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

#include "MustlStandard.h"

class MustlAddress
{
public:
    MustlAddress() :
        m_ip(0),
        m_port(0)
    {}

    MustlAddress(Mustl::U32 inHostNetworkOrder, Mustl::U32 inPortNetworkOrder) :
        m_ip(inHostNetworkOrder),
        m_port(inPortNetworkOrder)
    {}

    MustlAddress(const std::string& inName, Mustl::U32 inPortHostOrder)
    {
        ResolveFrom(inName, inPortHostOrder);
    }
    
    std::string HostStringGet(void) const;
    Mustl::U32 HostGetNetworkOrder(void) const { return m_ip; }
    void HostSetNetworkOrder(Mustl::U32 inIP) { m_ip = inIP; }
    Mustl::U32 PortGetNetworkOrder(void) const { return m_port; }
    Mustl::U32 PortGetHostOrder(void) const;
    void PortSetNetworkOrder(Mustl::U32 inPortNetworkOrder) { m_port = inPortNetworkOrder; }
    void PortSetHostOrder(Mustl::U32 inPortHostOrder);

    // This one can block if given a name which needs looking up
    void ResolveFrom(const std::string& inHostName, Mustl::U32 inPortHostOrder);

    // For use by <<
    void Print(ostream& ioOut) const;

    // For use by the operators == != < > 
    bool Equals(const MustlAddress& inAddress) const;
    bool LessThan(const MustlAddress& inAddress) const;
    bool GreaterThan(const MustlAddress& inAddress) const;
    
private:
    Mustl::U32 m_ip; // Network order
    Mustl::U32 m_port; // Network order
};

inline bool
MustlAddress::Equals(const MustlAddress& inAddress) const
{
    return m_ip == inAddress.HostGetNetworkOrder() &&
           m_port == inAddress.PortGetNetworkOrder();
}

inline bool
MustlAddress::LessThan(const MustlAddress& inAddress) const
{
    return m_ip < inAddress.HostGetNetworkOrder() ||
    m_port < inAddress.PortGetNetworkOrder();
}

inline bool
MustlAddress::GreaterThan(const MustlAddress& inAddress) const
{
    return m_ip > inAddress.HostGetNetworkOrder() ||
    m_port > inAddress.PortGetNetworkOrder();
}

inline bool
operator==(const MustlAddress& a, const MustlAddress& b)
{
    return a.Equals(b);
}

inline bool
operator!=(const MustlAddress& a, const MustlAddress& b)
{
    return !a.Equals(b);
}

// These are network order comparisons, provided so that the class can be
// used as the key in maps, so not for mathematical comparisons
inline bool
operator<(const MustlAddress& a, const MustlAddress& b)
{
    return a.LessThan(b);
}

inline bool
operator>(const MustlAddress& a, const MustlAddress& b)
{
    return a.GreaterThan(b);
}

inline ostream&
operator<<(ostream &ioOut, const MustlAddress& inLink)
{
    inLink.Print(ioOut);
    return ioOut;
}
#endif
