#ifndef TESTMUSHCORESTANDARD_H
#define TESTMUSHCORESTANDARD_H
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
 * $Id: TestMushcoreStandard.h,v 1.1 2003/01/20 15:38:28 southa Exp $
 * $Log: TestMushcoreStandard.h,v $
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
#else
#if defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#else
#include "Mushcore.h"
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

#endif
