#ifndef MUSTLASSERT_H
#define MUSTLASSERT_H

/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MustlAssert.h,v 1.2 2002/12/20 13:17:45 southa Exp $
 * $Log: MustlAssert.h,v $
 * Revision 1.2  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 */

#include "MustlStandard.h"

#include <assert.h>
#define MUSTLASSERT(x) assert(x)

#endif
