#ifndef MUSTLSTL_H
#define MUSTLSTL_H
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
 * $Id: MustlSTL.h,v 1.4 2003/01/17 00:41:05 southa Exp $
 * $Log: MustlSTL.h,v $
 * Revision 1.4  2003/01/17 00:41:05  southa
 * Configuration updates from POST data
 *
 * Revision 1.3  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.2  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 */

#include "MustlStandard.h"

#include "MustlAssert.h"

#include <stack>
#include <stdexcept>

#ifdef HAVE_SSTREAM
#include <sstream>
#else
#include "sstream"
#endif

#include <fstream>
#include <iomanip>
#include <iostream>

#include <typeinfo>

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <ctime>

#endif
