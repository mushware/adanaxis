/*
 * $Id$
 * $Log$
 */

#include "mushPlatform.h"

#include <windows.h>

void
PlatformNet::SocketNonBlockingSet(tSocket inSocket)
{
    u_long mode = 1;
    int result = ioctlsocket(inSocket, FIONBIO, &mode);

    if (result != 0)
    {
        ostringstream message;
        message << "Failed to set socket non-blocking: " << result;
        throw(NetworkFail(message.str()));
    }
}

void
PlatformNet::ReceiveNonBlocking(tSocket inSocket, void *outBuffer, U32 inSize)
{
    COREASSERT(false);
}
