#ifndef MUSTLASSERT_H
#define MUSTLASSERT_H

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
 * $Id: MustlAssert.h,v 1.1 2002/12/12 18:38:24 southa Exp $
 * $Log: MustlAssert.h,v $
 * Revision 1.1  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 */

#include "MustlStandard.h"

#include <assert.h>
#define MUSTLASSERT(x) assert(x)

#endif
