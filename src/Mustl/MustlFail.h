//%includeGuardStart {
#ifndef MUSTLFAIL_H
#define MUSTLFAIL_H
//%includeGuardStart } sHgBgEU8yDHBSP7QzKWU8w
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlFail.h
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } sPc94WevUhmO9uyFU8xaVA
/*
 * $Id: MustlFail.h,v 1.8 2003/08/21 23:09:25 southa Exp $
 * $Log: MustlFail.h,v $
 * Revision 1.8  2003/08/21 23:09:25  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/02/04 14:54:51  southa
 * Build fixes
 *
 * Revision 1.6  2003/01/16 15:58:01  southa
 * Mustl exception handling
 *
 * Revision 1.5  2003/01/14 17:38:21  southa
 * Mustl web configuration
 *
 * Revision 1.4  2003/01/07 17:13:44  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.3  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.2  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 */

#include "MustlStandard.h"

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/MushcoreFail.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <MushcoreFail.h>
#else
#include "MushcoreFail.h"
#endif
#endif

class MustlFail : public MushcoreNonFatalFail
{
public:
    MustlFail(const std::string& inMessage);
};

// PermanentFail indicates that the requested operation will never succeed in
// that context.  It indicates to the user that they should close the socket or link
// because it is not usable
class MustlPermanentFail : public MustlFail
{
public:
    MustlPermanentFail(const std::string& inMessage);
};

// TemporaryFail implies that the operation may succeed if retried later
class MustlTemporaryFail : public MustlFail
{
public:
    MustlTemporaryFail(const std::string& inMessage);
};

// Address is not contactable
class MustlAddressFail : public MustlPermanentFail
{
public:
    MustlAddressFail(const std::string& inMessage);
};

// The process of connecting a socket failed.  Dropped connections are reported
// as SocketFails
class MustlConnectionFail : public MustlPermanentFail
{
public:
    MustlConnectionFail(const std::string& inMessage);
};

// A send operation failed becuase of a problem with the message, such as it
// being too long for a UDP packet
class MustlMessageFail : public MustlPermanentFail
{
public:
    MustlMessageFail(const std::string& inMessage);
};

// The socket is not usable and should be closed
class MustlSocketFail : public MustlPermanentFail
{
public:
    MustlSocketFail(const std::string& inMessage);
};

// Indicates a dropped connection or, for a UDP sockets on some platforms,
// that a previously sent UDP packet could not be delivered to its target
class MustlSocketOrUDPFail : public MustlSocketFail
{
public:
    MustlSocketOrUDPFail(const std::string& inMessage);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
