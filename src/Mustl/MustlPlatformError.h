//%includeGuardStart {
#ifndef MUSTLPLATFORMERROR_H
#define MUSTLPLATFORMERROR_H
//%includeGuardStart } QbpcCz1efIT/WY1UE3COEw
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlPlatformError.h
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
//%Header } upeTbRH9Ef5Ukgd2bTD+Dw
/*
 * $Id: MustlPlatformError.h,v 1.4 2003/09/17 19:40:38 southa Exp $
 * $Log: MustlPlatformError.h,v $
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
