/*
 * $Id: MustlPlatformHeaders.h,v 1.3 2003/01/16 15:58:02 southa Exp $
 * $Log: MustlPlatformHeaders.h,v $
 * Revision 1.3  2003/01/16 15:58:02  southa
 * Mustl exception handling
 *
 * Revision 1.2  2003/01/16 13:11:32  southa
 * Install and uninstall MustlPlatform
 *
 * Revision 1.1  2003/01/16 12:03:55  southa
 * Platform and invalid socket fixes
 *
 */

// This file #defines the following values for platform selection
//
// MUSTL_WIN32             win32 platform
// MUSTL_MACOSX            Mac OS X platform
// MUSTL_POSIX_OR_MACOSX   POSIX-style or Mac OS X platform
// MUSTL_POSIX_NOT_MACOSX  POSIX-style platform which is not Mac OS X

#if defined(WIN32) || defined(_WIN32)
#define MUSTL_WIN32 1
#else
#if defined(__APPLE__) || defined(MACOSX)
#define MUSTL_MACOSX 1
#define MUSTL_POSIX_OR_MACOSX 1
#else
#define MUSTL_POSIX_NOT_MACOSX 1
#endif
#endif


// win32 includes
#ifdef MUSTL_WIN32
#include <windows.h>
#include <iphlpapi.h>
#endif

// Mac OS X includes
#ifdef MUSTL_MACOSX

// Mac OS X Carbon section
#ifndef MUSTL_NO_CARBON
#include <Carbon/Carbon.h>
// Remove definitions which are also in the POSIX includes
#undef TCP_NODELAY
#undef TCP_MAXSEG
#endif

#endif

// POSIX includes (including Mac OS X)
#ifdef MUSTL_POSIX_OR_MACOSX
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <fcntl.h>

#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif

// win32 has a different error handling and different names for some values,
// so they are #defined here
#ifdef MUSTL_WIN32

#define MUSTL_ERROR_PROLOGUE int wsaError
#define MUSTL_ERROR_RESET
#define MUSTL_ERROR_FETCH wsaError = WSAGetLastError()
#define MUSTL_ERROR_VALUE wsaError

/* non-blocking and interrupt i/o */
#define MUSTL_ERROR_EINTR           WSAEINTR              /* Interrupted system call */
#define MUSTL_ERROR_EACCES          WSAEACCES              /* Interrupted system call */
#define MUSTL_ERROR_EINVAL          WSAEINVAL              /* Interrupted system call */
#define MUSTL_ERROR_EAGAIN          WSAEWOULDBLOCK             /* Resource temporarily unavailable */
#define MUSTL_ERROR_EWOULDBLOCK     WSAEWOULDBLOCK        /* Operation would block */
#define MUSTL_ERROR_EINPROGRESS     WSAEINPROGRESS        /* Operation now in progress */
#define MUSTL_ERROR_EALREADY        WSAEALREADY           /* Operation already in progress */

/* ipc/network software -- argument errors */
#define MUSTL_ERROR_ENOTSOCK        WSAENOTSOCK           /* Socket operation on non-socket */
#define MUSTL_ERROR_EDESTADDRREQ    WSAEDESTADDRREQ       /* Destination address required */
#define MUSTL_ERROR_EMSGSIZE        WSAEMSGSIZE           /* Message too long */
#define MUSTL_ERROR_EPROTOTYPE      WSAEPROTOTYPE         /* Protocol wrong type for socket */
#define MUSTL_ERROR_ENOPROTOOPT     WSAENOPROTOOPT        /* Protocol not available */
#define MUSTL_ERROR_ENOTSUP         WSAEOPNOTSUPP         /* Operation not supported */
#define MUSTL_ERROR_EOPNOTSUPP      WSAEOPNOTSUPP         /* Operation not supported */
#define MUSTL_ERROR_EADDRINUSE      WSAEADDRINUSE         /* Address already in use */
#define MUSTL_ERROR_EADDRNOTAVAIL   WSAEADDRNOTAVAIL      /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define MUSTL_ERROR_ENETDOWN        WSAENETDOWN           /* Network is down */
#define MUSTL_ERROR_ENETUNREACH     WSAENETUNREACH        /* Network is unreachable */
#define MUSTL_ERROR_ENETRESET       WSAENETRESET          /* Network dropped connection on reset */
#define MUSTL_ERROR_ECONNABORTED    WSAECONNABORTED       /* Software caused connection abort */
#define MUSTL_ERROR_ECONNRESET      WSAECONNRESET         /* Connection reset by peer */
#define MUSTL_ERROR_ENOBUFS         WSAENOBUFS            /* No buffer space available */
#define MUSTL_ERROR_EISCONN         WSAEISCONN            /* Socket is already connected */
#define MUSTL_ERROR_ENOTCONN        WSAENOTCONN           /* Socket is not connected */
#define MUSTL_ERROR_ESHUTDOWN       WSAESHUTDOWN          /* Can't send after socket shutdown */
#define MUSTL_ERROR_ETIMEDOUT       WSAETIMEDOUT          /* Operation timed out */
#define MUSTL_ERROR_ECONNREFUSED    WSAECONNREFUSED       /* Connection refused */

#define MUSTL_ERROR_EHOSTDOWN       WSAEHOSTDOWN          /* Host is down */
#define MUSTL_ERROR_EHOSTUNREACH    WSAEHOSTUNREACH       /* No route to host */

#define MUSTL_ERROR_NOTINITIALISED WSANOTINITIALISED
#define MUSTL_ERROR_EDISCON         WSAEDISCON

#define MUSTL_INVALID_SOCKET INVALID_SOCKET

#else

#define MUSTL_ERROR_PROLOGUE
#define MUSTL_ERROR_RESET errno=0
#define MUSTL_ERROR_FETCH
#define MUSTL_ERROR_VALUE errno

/* non-blocking and interrupt i/o */
#define MUSTL_ERROR_EINTR           EINTR              /* Interrupted system call */
#define MUSTL_ERROR_EAGAIN          EAGAIN             /* Resource temporarily unavailable */
#define MUSTL_ERROR_EWOULDBLOCK     EWOULDBLOCK        /* Operation would block */
#define MUSTL_ERROR_EINPROGRESS     EINPROGRESS        /* Operation now in progress */
#define MUSTL_ERROR_EALREADY        EALREADY           /* Operation already in progress */

/* ipc/network software -- argument errors */
#define MUSTL_ERROR_ENOTSOCK        ENOTSOCK           /* Socket operation on non-socket */
#define MUSTL_ERROR_EDESTADDRREQ    EDESTADDRREQ       /* Destination address required */
#define MUSTL_ERROR_EMSGSIZE        EMSGSIZE           /* Message too long */
#define MUSTL_ERROR_EPROTOTYPE      EPROTOTYPE         /* Protocol wrong type for socket */
#define MUSTL_ERROR_ENOPROTOOPT     ENOPROTOOPT        /* Protocol not available */
#define MUSTL_ERROR_ENOTSUP         ENOTSUP            /* Operation not supported */
#define MUSTL_ERROR_EOPNOTSUPP      EOPNOTSUPP         /* Operation not supported */
#define MUSTL_ERROR_EADDRINUSE      EADDRINUSE         /* Address already in use */
#define MUSTL_ERROR_EADDRNOTAVAIL   EADDRNOTAVAIL      /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define MUSTL_ERROR_ENETDOWN        ENETDOWN           /* Network is down */
#define MUSTL_ERROR_ENETUNREACH     ENETUNREACH        /* Network is unreachable */
#define MUSTL_ERROR_ENETRESET       ENETRESET          /* Network dropped connection on reset */
#define MUSTL_ERROR_ECONNABORTED    ECONNABORTED       /* Software caused connection abort */
#define MUSTL_ERROR_ECONNRESET      ECONNRESET         /* Connection reset by peer */
#define MUSTL_ERROR_ENOBUFS         ENOBUFS            /* No buffer space available */
#define MUSTL_ERROR_EISCONN         EISCONN            /* Socket is already connected */
#define MUSTL_ERROR_ENOTCONN        ENOTCONN           /* Socket is not connected */
#define MUSTL_ERROR_ESHUTDOWN       ESHUTDOWN          /* Can't send after socket shutdown */
#define MUSTL_ERROR_ETIMEDOUT       ETIMEDOUT          /* Operation timed out */
#define MUSTL_ERROR_ECONNREFUSED    ECONNREFUSED       /* Connection refused */

#define MUSTL_ERROR_EHOSTDOWN       EHOSTDOWN          /* Host is down */
#define MUSTL_ERROR_EHOSTUNREACH    EHOSTUNREACH       /* No route to host */

#define MUSTL_ERROR_ENOTINITIALISED ENOTINITIALISED
#define MUSTL_ERROR_EDISCON         EDISCON

#define MUSTL_INVALID_SOCKET -1

#endif
