//%includeGuardStart {
#ifndef TESTMUSHCORESTANDARD_H
#define TESTMUSHCORESTANDARD_H
//%includeGuardStart } KajMHda8B99p147d9sr7AQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreStandard.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /AKq2mFxZ2UD/0DtLiL98g
/*
 * $Id: TestMushcoreStandard.h,v 1.4 2004/01/02 21:13:18 southa Exp $
 * $Log: TestMushcoreStandard.h,v $
 * Revision 1.4  2004/01/02 21:13:18  southa
 * Source conditioning
 *
 * Revision 1.3  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:38  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/20 15:38:28  southa
 * Created MushcoreTest
 *
 */

// Include everything we might need to keep things simple

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#include <Mushcore/MushcoreIO.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#include <MushcoreIO.h>
#else
#include "Mushcore.h"
#include "MushcoreIO.h"
#endif
#endif

#include <list>
#include <map>
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

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
