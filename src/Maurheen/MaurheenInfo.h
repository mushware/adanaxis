//%includeGuardStart {
#ifndef MAURHEENINFO_H
#define MAURHEENINFO_H
//%includeGuardStart } TYbkYo+sCZ1xkgtCrLgLWQ
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenInfo.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } K6Z/iuW6tyk2lBPXUUQ8KQ
/*
 * $Id: MaurheenInfo.h,v 1.3 2004/01/06 20:46:52 southa Exp $
 * $Log: MaurheenInfo.h,v $
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
