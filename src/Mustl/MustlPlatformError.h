#ifndef MUSTLPLATFORMERROR_H
#define MUSTLPLATFORMERROR_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MustlPlatformError.h,v 1.1 2003/01/16 15:58:02 southa Exp $
 * $Log: MustlPlatformError.h,v $
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
#endif
