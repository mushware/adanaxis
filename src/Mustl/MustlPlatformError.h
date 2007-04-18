//%includeGuardStart {
#ifndef MUSTLPLATFORMERROR_H
#define MUSTLPLATFORMERROR_H
//%includeGuardStart } QbpcCz1efIT/WY1UE3COEw
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlPlatformError.h
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
//%Header } FqCq1ok9eVpldtz8W0NuHQ
/*
 * $Id: MustlPlatformError.h,v 1.7 2006/06/01 15:39:53 southa Exp $
 * $Log: MustlPlatformError.h,v $
 * Revision 1.7  2006/06/01 15:39:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:29  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.1  2003/01/16 15:58:02  southa
 * Mustl exception handling
 *
 */

#include "MustlStandard.h"

class MustlPlatformError
{
public:
    typedef int tErrorCode;
    static void Throw(const std::string& inPrefix);
    static void Throw(tErrorCode inCode, const std::string& inPrefix);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
