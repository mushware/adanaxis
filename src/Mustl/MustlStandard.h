//%includeGuardStart {
#ifndef MUSTLSTANDARD_H
#define MUSTLSTANDARD_H
//%includeGuardStart } et2J+l7uTDJO7v1niqd5zA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlStandard.h
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } tDPVBPiOtfBuU7Ie+HZRZA
/*
 * $Id: MustlStandard.h,v 1.9 2003/08/21 23:09:31 southa Exp $
 * $Log: MustlStandard.h,v $
 * Revision 1.9  2003/08/21 23:09:31  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.7  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
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

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
