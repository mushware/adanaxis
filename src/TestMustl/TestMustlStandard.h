//%includeGuardStart {
#ifndef TESTMUSTLSTANDARD_H
#define TESTMUSTLSTANDARD_H
//%includeGuardStart } 3eZYJcCuEjLA1xgox18STA
//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlStandard.h
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
//%Header } BFgQuIHy03qH6vWGg/n7cA
/*
 * $Id: TestMustlStandard.h,v 1.7 2006/06/01 15:40:06 southa Exp $
 * $Log: TestMustlStandard.h,v $
 * Revision 1.7  2006/06/01 15:40:06  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:25  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/07 11:14:15  southa
 * Snapshot fixes
 *
 * Revision 1.4  2004/01/02 21:13:18  southa
 * Source conditioning
 *
 * Revision 1.3  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:40  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 */

// Include everything we might need to keep things simple

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#include <list>
#include <map>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#include <fstream>
#include <iomanip>
#include <iostream>

#ifdef HAVE_SSTREAM
#include <sstream>
#else
#include "sstream"
#endif

#include <typeinfo>

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <ctime>

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#else
#include "Mushcore/Mushcore.h"
#endif
#endif

#if defined(HAVE_MUSTL_MUSTL_H)
#include <Mustl/Mustl.h>
#else
#if defined(HAVE_MUSTL_H)
#include <Mustl.h>
#else
#include "Mustl/Mustl.h"
#endif
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
