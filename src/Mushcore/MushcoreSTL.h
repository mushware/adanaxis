/*
 * $Id$
 * $Log$
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

#include <ctime>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef HAVE_VALARRAY
#include <valarray>
#define tValarray valarray
#else
// Mimic valarray using vector
#define tValarray vector
#endif

#ifndef M_PI
#define M_PI 3.14159265358979
#endif


