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
 * $Id: MustlStandard.h,v 1.3 2002/12/20 13:17:46 southa Exp $
 * $Log: MustlStandard.h,v $
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

#endif
