//%includeGuardStart {
#ifndef TESTMUSHPIESTANDARD_H
#define TESTMUSHPIESTANDARD_H
//%includeGuardStart } O+ohKXYI4LUaueB8IiVCOA
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushPie/TestMushPieStandard.h
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
//%Header } Owajn1E3Ga4bRosk0dqEug
/*
 * $Id: TestMushPieStandard.h,v 1.4 2006/06/01 15:40:03 southa Exp $
 * $Log: TestMushPieStandard.h,v $
 * Revision 1.4  2006/06/01 15:40:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.2  2004/01/07 11:14:15  southa
 * Snapshot fixes
 *
 * Revision 1.1  2004/01/06 00:34:57  southa
 * MushPie testing
 *
 */

// Include everything we might need to keep things simple

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#elif defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#else
#include "Mushcore/Mushcore.h"
#endif

#if defined(HAVE_MUSHMESH_MUSHPIE_H)
#include <MushPie/MushPie.h>
#elif defined(HAVE_MUSHPIE_H)
#include <MushPie.h>
#else
#include "MushPie/MushPie.h"
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
