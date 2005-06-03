#ifndef MUSHCORESTL_H
#define MUSHCORESTL_H
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
 * $Id: MushcoreSTL.h,v 1.1 2003/01/12 17:33:00 southa Exp $
 * $Log: MushcoreSTL.h,v $
 * Revision 1.1  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 */

#include "MushcoreStandard.h"

// General purpose includes used by most files
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
#include <cstdio>
#include <cstdlib>
#include <ctime>

#endif
