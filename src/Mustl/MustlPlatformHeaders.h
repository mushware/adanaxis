/*
 * $Id$
 * $Log$
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

#define MUSTL_ERROR_PREFIX int wsaError
#define MUSTL_ERROR_RESET
#define MUSTL_ERROR_FETCH wsaError = WSAGetLastError()
#define MUSTL_ERROR_VALUE wsaError
#define MUSTL_ERROR_EAGAIN WSAEWOULDBLOCK
#define MUSTL_ERROR_EINTR WSAEINTR
#define MUSTL_ERROR_EWOULDBLOCK WSAEWOULDBLOCK
#define MUSTL_ERROR_EINPROGRESS WSAEINPROGRESS
#define MUSTL_INVALID_SOCKET INVALID_SOCKET

#else

#define MUSTL_ERROR_PREFIX
#define MUSTL_ERROR_RESET errno=0
#define MUSTL_ERROR_FETCH
#define MUSTL_ERROR_VALUE errno
#define MUSTL_ERROR_EAGAIN EAGAIN
#define MUSTL_ERROR_EINTR EINTR
#define MUSTL_ERROR_EWOULDBLOCK EWOULDBLOCK
#define MUSTL_ERROR_EINPROGRESS EINPROGRESS
#define MUSTL_INVALID_SOCKET -1

#endif
