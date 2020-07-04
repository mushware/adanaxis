//%includeGuardStart {
#ifndef MUSTLPLATFORMHEADERS_H
#define MUSTLPLATFORMHEADERS_H
//%includeGuardStart } y7EFdhSkcPaops1CuTlFAA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlPlatformHeaders.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } W1aCBqrrT/Lk170w6U3Lug
/*
 * $Id: MustlPlatformHeaders.h,v 1.18 2006/06/01 20:13:01 southa Exp $
 * $Log: MustlPlatformHeaders.h,v $
 * Revision 1.18  2006/06/01 20:13:01  southa
 * Initial texture caching
 *
 * Revision 1.17  2006/06/01 15:39:54  southa
 * DrawArray verification and fixes
 *
 * Revision 1.16  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.15  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.14  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.13  2003/08/21 23:23:06  southa
 * Replaced changes inadvertently lost
 *
 * Revision 1.12  2003/08/21 23:09:29  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/07/17 19:14:01  southa
 * Unix include order fix
 *
 * Revision 1.10  2003/02/05 17:06:38  southa
 * Build fixes
 *
 * Revision 1.9  2003/02/05 16:19:46  southa
 * Build fixes
 *
 * Revision 1.8  2003/02/04 19:07:12  southa
 * Build fixes
 *
 * Revision 1.7  2003/02/04 14:54:52  southa
 * Build fixes
 *
 * Revision 1.6  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.5  2003/01/17 00:41:04  southa
 * Configuration updates from POST data
 *
 * Revision 1.4  2003/01/16 16:38:37  southa
 * Error codes for win32
 *
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

#include "MustlStandard.h"

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
#define MUSTL_POSIX_OR_MACOSX 1
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

#include <Carbon/Carbon.h>

// Mac OS X Carbon section
// Remove definitions which are also in the POSIX includes
#undef TCP_NODELAY
#undef TCP_MAXSEG
#endif


// POSIX includes (including Mac OS X)
#ifdef MUSTL_POSIX_OR_MACOSX
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#endif

// win32 has a different error handling and different names for some values,
// so they are #defined here
#ifdef MUSTL_WIN32

#define MUSTL_ERROR_PROLOGUE int wsaError
#define MUSTL_ERROR_RESET
#define MUSTL_ERROR_FETCH wsaError = WSAGetLastError()
#define MUSTL_ERROR_VALUE wsaError

#define MUSTL_ERROR_EINTR           WSAEINTR
#define MUSTL_ERROR_EACCES          WSAEACCES
#define MUSTL_ERROR_EINVAL          WSAEINVAL
#define MUSTL_ERROR_EAGAIN          WSAEWOULDBLOCK
#define MUSTL_ERROR_EWOULDBLOCK     WSAEWOULDBLOCK
#define MUSTL_ERROR_EINPROGRESS     WSAEINPROGRESS
#define MUSTL_ERROR_EALREADY        WSAEALREADY
#define MUSTL_ERROR_ENOTSOCK        WSAENOTSOCK
#define MUSTL_ERROR_EDESTADDRREQ    WSAEDESTADDRREQ
#define MUSTL_ERROR_EMSGSIZE        WSAEMSGSIZE
#define MUSTL_ERROR_EPROTOTYPE      WSAEPROTOTYPE
#define MUSTL_ERROR_ENOPROTOOPT     WSAENOPROTOOPT
#define MUSTL_ERROR_ENOTSUP         WSAEOPNOTSUPP
#define MUSTL_ERROR_EOPNOTSUPP      WSAEOPNOTSUPP
#define MUSTL_ERROR_EADDRINUSE      WSAEADDRINUSE
#define MUSTL_ERROR_EADDRNOTAVAIL   WSAEADDRNOTAVAIL
#define MUSTL_ERROR_ENETDOWN        WSAENETDOWN
#define MUSTL_ERROR_ENETUNREACH     WSAENETUNREACH
#define MUSTL_ERROR_ENETRESET       WSAENETRESET
#define MUSTL_ERROR_ECONNABORTED    WSAECONNABORTED
#define MUSTL_ERROR_ECONNRESET      WSAECONNRESET
#define MUSTL_ERROR_ENOBUFS         WSAENOBUFS
#define MUSTL_ERROR_EISCONN         WSAEISCONN
#define MUSTL_ERROR_ENOTCONN        WSAENOTCONN
#define MUSTL_ERROR_ESHUTDOWN       WSAESHUTDOWN
#define MUSTL_ERROR_ETIMEDOUT       WSAETIMEDOUT
#define MUSTL_ERROR_ECONNREFUSED    WSAECONNREFUSED
#define MUSTL_ERROR_EHOSTDOWN       WSAEHOSTDOWN
#define MUSTL_ERROR_EHOSTUNREACH    WSAEHOSTUNREACH

// win32 only
#define MUSTL_ERROR_NOTINITIALISED  WSANOTINITIALISED
#define MUSTL_ERROR_EDISCON         WSAEDISCON

#define MUSTL_INVALID_SOCKET        INVALID_SOCKET
#define MUSTL_SOCKLEN_T             int
#endif


#ifdef MUSTL_POSIX_OR_MACOSX

#define MUSTL_ERROR_PROLOGUE
#define MUSTL_ERROR_RESET errno=0
#define MUSTL_ERROR_FETCH
#define MUSTL_ERROR_VALUE errno

#define MUSTL_ERROR_EINTR           EINTR
#define MUSTL_ERROR_EACCES          EACCES
#define MUSTL_ERROR_EINVAL          EINVAL
#define MUSTL_ERROR_EAGAIN          EAGAIN
#define MUSTL_ERROR_EWOULDBLOCK     EWOULDBLOCK
#define MUSTL_ERROR_EINPROGRESS     EINPROGRESS
#define MUSTL_ERROR_EALREADY        EALREADY
#define MUSTL_ERROR_ENOTSOCK        ENOTSOCK
#define MUSTL_ERROR_EDESTADDRREQ    EDESTADDRREQ
#define MUSTL_ERROR_EMSGSIZE        EMSGSIZE
#define MUSTL_ERROR_EPROTOTYPE      EPROTOTYPE
#define MUSTL_ERROR_ENOPROTOOPT     ENOPROTOOPT
#define MUSTL_ERROR_ENOTSUP         ENOTSUP
#define MUSTL_ERROR_EOPNOTSUPP      EOPNOTSUPP
#define MUSTL_ERROR_EADDRINUSE      EADDRINUSE
#define MUSTL_ERROR_EADDRNOTAVAIL   EADDRNOTAVAIL
#define MUSTL_ERROR_ENETDOWN        ENETDOWN
#define MUSTL_ERROR_ENETUNREACH     ENETUNREACH
#define MUSTL_ERROR_ENETRESET       ENETRESET
#define MUSTL_ERROR_ECONNABORTED    ECONNABORTED
#define MUSTL_ERROR_ECONNRESET      ECONNRESET
#define MUSTL_ERROR_ENOBUFS         ENOBUFS
#define MUSTL_ERROR_EISCONN         EISCONN
#define MUSTL_ERROR_ENOTCONN        ENOTCONN
#define MUSTL_ERROR_ESHUTDOWN       ESHUTDOWN
#define MUSTL_ERROR_ETIMEDOUT       ETIMEDOUT
#define MUSTL_ERROR_ECONNREFUSED    ECONNREFUSED
#define MUSTL_ERROR_EHOSTDOWN       EHOSTDOWN
#define MUSTL_ERROR_EHOSTUNREACH    EHOSTUNREACH

#define MUSTL_INVALID_SOCKET -1

#endif


#ifdef MUSTL_MACOSX
#define MUSTL_SOCKLEN_T             socklen_t // was int
#endif


#ifdef MUSTL_POSIX_NOT_MACOSX
#define MUSTL_SOCKLEN_T             socklen_t
#endif

#if defined(MUSTL_MACOSX) || defined (HAVE_SOCKLEN_SA_LEN)
#define MUSTL_HAVE_SOCKADDR_SA_LEN 1
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
