#ifndef MUSHCORESTL_H
#define MUSHCORESTL_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MushcoreSTL.h,v 1.2 2003/01/13 14:32:02 southa Exp $
 * $Log: MushcoreSTL.h,v $
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
