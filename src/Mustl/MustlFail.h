//%includeGuardStart {
#ifndef MUSTLFAIL_H
#define MUSTLFAIL_H
//%includeGuardStart } sHgBgEU8yDHBSP7QzKWU8w
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlFail.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 7KmSfBC22LGmXgqYwN9kgA
/*
 * $Id: MustlFail.h,v 1.13 2006/06/01 15:39:51 southa Exp $
 * $Log: MustlFail.h,v $
 * Revision 1.13  2006/06/01 15:39:51  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.11  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.10  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.9  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
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
#include "MustlMushcore.h"

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
