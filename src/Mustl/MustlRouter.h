#ifndef MUSTLROUTER_H
#define MUSTLROUTER_H
/*
 * $Id: MustlRouter.h,v 1.6 2002/11/25 12:06:19 southa Exp $
 * $Log: MustlRouter.h,v $
 * Revision 1.6  2002/11/25 12:06:19  southa
 * Received net message routing
 *
 * Revision 1.5  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.4  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.3  2002/11/22 15:00:33  southa
 * Network connection handling
 *
 * Revision 1.2  2002/11/04 19:34:47  southa
 * Network link maintenance
 *
 * Revision 1.1  2002/11/04 01:02:38  southa
 * Link checks
 *
 */

#include "mushCore.h"

class MustlData;
class MustlLink;
class MustlHandler;

class MustlRouter
{
public:
    static inline MustlRouter& Instance(void);
    void ReceiveAll(MustlHandler& inHandler);

protected:
    MustlRouter();
    void UDPIfAddressMatchReceive(MustlData& ioData, MustlHandler& inHandler);
    void UDPReceiveFromServer(MustlHandler& inHandler);
    
private:
    enum
    {
        kTickPeriod=100,
        kUDPReceivePacketLimit=100
    };
    
    U32 m_lastTickMsec;
    
    static auto_ptr<MustlRouter> m_instance;
}; 

inline  MustlRouter&
MustlRouter::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MustlRouter);
    return *m_instance;
}
#endif
