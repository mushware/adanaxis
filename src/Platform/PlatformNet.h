/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class PlatformNet
{
public:
    typedef S32 tSocket;
    static void SocketNonBlockingSet(tSocket inSocket);
    static void ReceiveNonBlocking(tSocket inSocket, void *outBuffer, U32 inSize);

};


