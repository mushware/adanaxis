//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlPlatformError.cpp
 *
 * Copyright Andy Southgate 2002-2004
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ROBkZRUCXgpewY9gxTb4Rw
/*
 * $Id: MustlPlatformError.cpp,v 1.7 2003/09/17 19:40:38 southa Exp $
 * $Log: MustlPlatformError.cpp,v $
 * Revision 1.7  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:29  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/02/04 14:54:51  southa
 * Build fixes
 *
 * Revision 1.4  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.3  2003/01/17 00:41:04  southa
 * Configuration updates from POST data
 *
 * Revision 1.2  2003/01/16 16:38:37  southa
 * Error codes for win32
 *
 * Revision 1.1  2003/01/16 15:58:02  southa
 * Mustl exception handling
 *
 */

#include "MustlPlatformError.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"
#include "MustlPlatformHeaders.h"

using namespace Mustl;
using namespace std;

#ifdef MUSTL_NO_EXCEPTIONS

MustlPlatformError::Throw(tErrorCode inCode, constr string& inStr)
{
    cerr << "Error: " << inStr << endl;
}

void
MustlPlatformError::Throw(tErrorCode inSystemCode, constr string& inPrefix)
{
    cerr << "Error (" << inSystemCode << ") " << inStr << endl;
}    

#else

void
MustlPlatformError::Throw(const string& inStr)
{
    throw MustlPermanentFail(inStr);
}

void
MustlPlatformError::Throw(tErrorCode inSystemCode, const string& inPrefix)
{
    ostringstream prefixStream;
    prefixStream << inPrefix << ": (" << inSystemCode << ") ";
    string prefixStr = prefixStream.str();
    
    switch (inSystemCode)
    {
        case MUSTL_ERROR_EINTR:
            throw(MustlTemporaryFail(prefixStr+"EINTR"));

	case MUSTL_ERROR_EACCES:
            throw(MustlTemporaryFail(prefixStr+"EACCES: Permission denied"));

	case MUSTL_ERROR_EINVAL:
            throw(MustlTemporaryFail(prefixStr+"EINVAL: Invalid operation"));

#if MUSTL_ERROR_EWOULDBLOCK != MUSTL_ERROR_EAGAIN
        case MUSTL_ERROR_EAGAIN:
#endif
        case MUSTL_ERROR_EWOULDBLOCK:
            throw(MustlTemporaryFail(prefixStr+"EWOULDBLOCK/EAGAIN"));
            
        case MUSTL_ERROR_EINPROGRESS:
            throw(MustlTemporaryFail(prefixStr+"EINPROGRESS: (Connection) is in progress"));
            
        case MUSTL_ERROR_EALREADY:
            throw(MustlTemporaryFail(prefixStr+"EALREADY"));

        case MUSTL_ERROR_ENOTSOCK:
            throw(MustlSocketFail(prefixStr+"ENOTSOCK: Not a socket"));
            
        case MUSTL_ERROR_EDESTADDRREQ:
            throw(MustlPermanentFail(prefixStr+"EDESTADDRREQ"));
            
        case MUSTL_ERROR_EMSGSIZE:
            throw(MustlMessageFail(prefixStr+"EMSGSIZE: Message is too long for this protocol"));
            
        case MUSTL_ERROR_EPROTOTYPE:
            throw(MustlPermanentFail(prefixStr+"EPROTOTYPE:"));
            
        case MUSTL_ERROR_ENOPROTOOPT:
            throw(MustlPermanentFail(prefixStr+"ENOPROTOOPT: Requested protocol is not available"));

#if MUSTL_ERROR_ENOTSUP != MUSTL_ERROR_EOPNOTSUPP
        case MUSTL_ERROR_ENOTSUP:
#endif
        case MUSTL_ERROR_EOPNOTSUPP:
            throw(MustlPermanentFail(prefixStr+"EOPNOTSUPP/ENOTSUP: Not supported"));
            
        case MUSTL_ERROR_EADDRINUSE:
            throw(MustlAddressFail(prefixStr+"EADDRINUSE: Address is already in use"));
            
        case MUSTL_ERROR_EADDRNOTAVAIL:
            throw(MustlAddressFail(prefixStr+"EADDRNOTAVAIL: Address is invalid"));

        case MUSTL_ERROR_ENETDOWN:
            throw(MustlAddressFail(prefixStr+"ENETDOWN: Network is down"));
            
        case MUSTL_ERROR_ENETUNREACH:
            throw(MustlAddressFail(prefixStr+"ENETUNREACH: Network is unreachable"));
            
        case MUSTL_ERROR_ENETRESET:
            throw(MustlSocketFail(prefixStr+"ENETRESET: Network connection reset"));
            
        case MUSTL_ERROR_ECONNABORTED:
            throw(MustlSocketFail(prefixStr+"ECONNABORTED: Local host aborted the connection"));
            
        case MUSTL_ERROR_ECONNRESET:
#ifdef MUSTL_WIN32
            // win32 also returns ECONNRESET if ICMP has indicated that a UDP packet
            // has been rejected by its target
            throw(MustlSocketOrUDPFail(prefixStr+"ECONNRESET: Connection reset by peer"));
#else
            throw(MustlSocketFail(prefixStr+"ECONNRESET: Connection reset by peer"));
#endif

        case MUSTL_ERROR_ENOBUFS:
            throw(MustlTemporaryFail(prefixStr+"ENOBUFS"));
            
        case MUSTL_ERROR_EISCONN:
            throw(MustlSocketFail(prefixStr+"EISCONN: Socket is already connected"));
            
        case MUSTL_ERROR_ENOTCONN:
            throw(MustlSocketFail(prefixStr+"ENOTCONN: Socket is not connected"));
            
        case MUSTL_ERROR_ESHUTDOWN:
            throw(MustlSocketFail(prefixStr+"ESHUTDOWN: Socket is shutdown"));
            
        case MUSTL_ERROR_ETIMEDOUT:
            throw(MustlConnectionFail(prefixStr+"ETIMEDOUT: Operation timed out"));
            
        case MUSTL_ERROR_ECONNREFUSED:
            throw(MustlConnectionFail(prefixStr+"ECONNREFUSED: Connection refused"));

        case MUSTL_ERROR_EHOSTDOWN:
            throw(MustlAddressFail(prefixStr+"EHOSTDOWN: Target host is down"));
            
        case MUSTL_ERROR_EHOSTUNREACH:
            throw(MustlAddressFail(prefixStr+"EHOSTUNREACH: Target host is unreachable"));

#ifdef MUSTL_WIN32
        case MUSTL_ERROR_NOTINITIALISED:
            throw(MustlPermanentFail(prefixStr+"MUSTL_ERROR_ENOTINITIALISED: Sockets system is not initialised"));

        case MUSTL_ERROR_EDISCON:
            throw(MustlSocketFail(prefixStr+"MUSTL_ERROR_EDISCON: Peer disconnected"));
#endif

	default:
            throw(MustlAddressFail(prefixStr+"Unknown error"));
    }
}
#endif
