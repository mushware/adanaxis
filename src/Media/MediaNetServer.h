/*
 * $Id: MediaNetServer.h,v 1.2 2002/10/31 16:41:33 southa Exp $
 * $Log: MediaNetServer.h,v $
 * Revision 1.2  2002/10/31 16:41:33  southa
 * Network client
 *
 * Revision 1.1  2002/10/31 15:52:15  southa
 * First network code
 *
 */

#include "mushCore.h"

#include "MediaSDL.h"

class MediaNetServer
{
public:
    explicit MediaNetServer(U32 inPort);
    ~MediaNetServer();

    void Accept(void);
    
private:
    TCPsocket m_serverSocket;
    U32 m_linkCtr;
};
