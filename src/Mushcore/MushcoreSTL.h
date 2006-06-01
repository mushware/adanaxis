//%includeGuardStart {
#ifndef MUSHCORESTL_H
#define MUSHCORESTL_H
//%includeGuardStart } Hds411lfFyYAb5qD0dZRlA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreSTL.h
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
//%Header } R3eMTugyc/SEgaHtYlA2bg
/*
 * $Id: MushcoreSTL.h,v 1.8 2005/05/19 13:02:16 southa Exp $
 * $Log: MushcoreSTL.h,v $
 * Revision 1.8  2005/05/19 13:02:16  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.6  2004/01/01 21:15:46  southa
 * Created XCode project
 *
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
