#ifndef MUSTLSERVER_H
#define MUSTLSERVER_H
/*
 * $Id: MustlServer.h,v 1.1 2002/12/12 14:00:27 southa Exp $
 * $Log: MustlServer.h,v $
 * Revision 1.1  2002/12/12 14:00:27  southa
 * Created Mustl
 *
 * Revision 1.11  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.10  2002/11/23 14:45:34  southa
 * Replaced access to server port
 *
 * Revision 1.9  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.8  2002/11/22 15:00:33  southa
 * Network connection handling
 *
 * Revision 1.7  2002/11/21 18:06:18  southa
 * Non-blocking network connection
 *
 * Revision 1.6  2002/11/20 22:35:28  southa
 * Multiplayer setup
 *
 * Revision 1.5  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.4  2002/11/01 18:46:26  southa
 * UDP Links
 *
 * Revision 1.3  2002/10/31 19:55:54  southa
 * Network links
 *
 * Revision 1.2  2002/10/31 16:41:33  southa
 * Network client
 *
 * Revision 1.1  2002/10/31 15:52:15  southa
 * First network code
 *
 */

#include "MustlStandard.h"

class MustlData;

class MustlServer
{
public:
    ~MustlServer();

    static inline MustlServer& Instance(void);

    void Connect(Mustl::U32 inPort);
    void Disconnect(void);
    void Accept(void);
    void UDPSend(Mustl::U32 inHost, Mustl::U32 inPort, MustlData& inData);
    void UDPReceive(MustlData& inData);
    void UDPHarvest(void);
    void UDPDiscard(void);
    bool IsServing(void) const { return m_serving; }
    Mustl::U32 ServerPortHostOrderGet(void) const { return m_serverPortHostOrder; }
    
protected:
    MustlServer();
    
private:
    Mustl::tSocket m_tcpSocket;
    Mustl::tSocket m_udpSocket;
    Mustl::U32 m_serverPortHostOrder;
    Mustl::U32 m_linkCtr;
    bool m_serving;

    static auto_ptr<MustlServer> m_instance;
};

inline  MustlServer&
MustlServer::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MustlServer);
    return *m_instance;
}
#endif
