/*
 *  PlatformNet.cpp
 *  core-app
 *
 *  Created by Andy Southgate on Fri Nov 01 2002.
 *  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
 *
 */

#include "PlatformNet.h"

#include <fcntl.h>

void
PlatformNet::SocketNonBlockingSet(tSocket inSocket)
{
    errno=0;
    if (fcntl(inSocket, F_SETFL, O_NONBLOCK) == -1)
    {
        ostringstream message;
        message << "Failed to set socket non-blocking: " << errno;
        throw(NetworkFail(message.str()));
    }
}

void
PlatformNet::ReceiveNonBlocking(tSocket inSocket, void *outBuffer, U32 inSize)
{
    COREASSERT(false);
}
