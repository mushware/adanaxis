//%includeGuardStart {
#ifndef TESTMUSTLSTANDARD_H
#define TESTMUSTLSTANDARD_H
//%includeGuardStart } 3eZYJcCuEjLA1xgox18STA
//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlStandard.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } fOd+zqmx5mhzTvwuIeBb7g
/*
 * $Id: TestMustlStandard.h,v 1.2 2003/08/21 23:09:40 southa Exp $
 * $Log: TestMustlStandard.h,v $
 * Revision 1.2  2003/08/21 23:09:40  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 */

// Include everything we might need to keep things simple

#ifdef HAVE_CONFIG_H
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
#include "Mushcore.h"
#endif
#endif

#if defined(HAVE_MUSTL_MUSTL_H)
#include <Mustl/Mustl.h>
#else
#if defined(HAVE_MUSTL_H)
#include <Mustl.h>
#else
#include "Mustl.h"
#endif
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
