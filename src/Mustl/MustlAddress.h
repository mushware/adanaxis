#ifndef MUSTLADDRESS_H
#define MUSTLADDRESS_H
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
 * $Id: MustlAddress.h,v 1.9 2003/01/16 15:58:01 southa Exp $
 * $Log: MustlAddress.h,v $
 * Revision 1.9  2003/01/16 15:58:01  southa
 * Mustl exception handling
 *
 * Revision 1.8  2003/01/16 13:11:32  southa
 * Install and uninstall MustlPlatform
 *
 * Revision 1.7  2003/01/14 22:02:12  southa
 * Command line build fixes
 *
 * Revision 1.6  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/12/17 00:58:28  southa
 * Added support for libmustl target
 *
 * Revision 1.4  2002/12/14 15:04:33  southa
 * Mustl fixes
 *
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
    typedef Mustl::U32 tIPv4Addr;
    typedef Mustl::U32 tPort;
    
    MustlAddress() :
        m_ip(0),
        m_port(0)
    {}

    MustlAddress(tIPv4Addr inHostNetworkOrder, tPort inPortNetworkOrder) :
        m_ip(inHostNetworkOrder),
        m_port(inPortNetworkOrder)
    {}

    MustlAddress(const std::string& inName, tPort inPortHostOrder)
    {
        ResolveFromHostName(inName, inPortHostOrder);
    }

    std::string StringGet(void) const;
    std::string LogStringGet(void) const;
    std::string HostStringGet(void) const;
    tIPv4Addr HostGetNetworkOrder(void) const { return m_ip; }
    void HostSetNetworkOrder(tIPv4Addr inIP) { m_ip = inIP; }
    tPort PortGetNetworkOrder(void) const { return m_port; }
    tPort PortGetHostOrder(void) const;
    void PortSetNetworkOrder(tPort inPortNetworkOrder) { m_port = inPortNetworkOrder; }
    void PortSetHostOrder(tPort inPortHostOrder);

    void ResolveFromIPAddressString(const std::string& inHostName, tPort inPortHostOrder);

    // This one can block if given a name which needs looking up
    void ResolveFromHostName(const std::string& inHostName, tPort inPortHostOrder);
        
    // For use by std::ostream <<
    void Print(std::ostream& ioOut) const;

    // For use by the operators == != < > 
    bool Equals(const MustlAddress& inAddress) const;
    bool LessThan(const MustlAddress& inAddress) const;
    bool GreaterThan(const MustlAddress& inAddress) const;
    
private:
    tIPv4Addr m_ip; // Network order
    tPort m_port; // Network order
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

inline std::ostream&
operator<<(std::ostream &ioOut, const MustlAddress& inLink)
{
    inLink.Print(ioOut);
    return ioOut;
}
#endif
