//%includeGuardStart {
#ifndef MUSTLMESSAGEHANDLER_H
#define MUSTLMESSAGEHANDLER_H
//%includeGuardStart } eoVFM54gveFyGhSDCR2BDA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlMessageHandler.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } bHno4icukXe7bh3oXU/2HA
/*
 * $Id: MustlMessageHandler.h,v 1.5 2004/01/02 21:13:15 southa Exp $
 * $Log: MustlMessageHandler.h,v $
 * Revision 1.5  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:27  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.1  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.3  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.3  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.2  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.1  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 */

#include "MustlStandard.h"

class MustlData;
class MustlLink;

class MustlMessageHandler
{
public:
    virtual void MessageHandle(MustlData& ioData, MustlLink& inLink, Mustl::U32 inType) = 0;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
