#ifndef MUSTLSTANDARD_H
#define MUSTLSTANDARD_H
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
 * $Id: MustlStandard.h,v 1.6 2003/01/17 13:30:41 southa Exp $
 * $Log: MustlStandard.h,v $
 * Revision 1.6  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.5  2003/01/17 00:41:05  southa
 * Configuration updates from POST data
 *
 * Revision 1.4  2003/01/13 15:01:20  southa
 * Fix Mustl command line build
 *
 * Revision 1.3  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/13 01:06:54  southa
 * Mustl work
 *
 * Revision 1.1  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iosfwd>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Mustl
{
    typedef int tSocket;
    typedef float tVal;
    typedef double tLongVal;
    typedef signed int S32;
    typedef unsigned int U32;
    typedef signed short S16;
    typedef unsigned short U16;
    typedef signed char S8;
    typedef unsigned char U8;
    typedef double tMsec;
};

#define MUSTL_DECLARE_INLINE inline

#endif
