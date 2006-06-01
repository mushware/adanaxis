//%includeGuardStart {
#ifndef MAURHEENINFO_H
#define MAURHEENINFO_H
//%includeGuardStart } TYbkYo+sCZ1xkgtCrLgLWQ
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenInfo.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } oag+7uiqRDT5RHN+c5+vjQ
/*
 * $Id: MaurheenInfo.h,v 1.2 2005/05/19 13:02:07 southa Exp $
 * $Log: MaurheenInfo.h,v $
 * Revision 1.2  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.1  2004/03/06 14:01:42  southa
 * Maurheen created
 *
 */

#include "mushMushcore.h"

class MaurheenInfo : public MushcoreInfo
{
public:
    virtual std::string ApplicationNameGet(void);
    virtual std::string PackageNameGet(void);
    virtual std::string PackageVersionGet(void);

    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
