#ifndef MEDIANETROUTER_H
#define MEDIANETROUTER_H
/*
 * $Id: MediaNetRouter.h,v 1.5 2002/11/25 10:43:28 southa Exp $
 * $Log: MediaNetRouter.h,v $
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

class MediaNetData;
class MediaNetLink;
class MediaNetHandler;

class MediaNetRouter
{
public:
    static inline MediaNetRouter& Instance(void);
    void ReceiveAll(MediaNetHandler& inHandler);

protected:
    MediaNetRouter();
    void UDPIfAddressMatchReceive(MediaNetData& ioData, MediaNetHandler& inHandler);
    void UDPReceiveFromServer(MediaNetHandler& inHandler);
    
private:
    enum
    {
        kTickPeriod=100,
        kUDPReceivePacketLimit=100
    };
    
    U32 m_lastTickMsec;
    
    static auto_ptr<MediaNetRouter> m_instance;
}; 

inline  MediaNetRouter&
MediaNetRouter::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MediaNetRouter);
    return *m_instance;
}
#endif
