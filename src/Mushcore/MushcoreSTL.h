//%includeGuardStart {
#ifndef MUSHCORESTL_H
#define MUSHCORESTL_H
//%includeGuardStart } Hds411lfFyYAb5qD0dZRlA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreSTL.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } R50LoW9d2MyCM0eN10Ob1A
/*
 * $Id: MushcoreSTL.h,v 1.5 2003/10/06 22:50:02 southa Exp $
 * $Log: MushcoreSTL.h,v $
 * Revision 1.5  2003/10/06 22:50:02  southa
 * Added M_PI
 *
 * Revision 1.4  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:16  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/13 14:32:02  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.1  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 */

#include "MushcoreStandard.h"

// General purpose includes used by most files
#include <fstream>
#include <iomanip>
#include <iostream>

#ifdef MIMIC_SSTREAM
#include "sstream"
#else
#include <sstream>
#endif

#include <typeinfo>

#include <cerrno>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
