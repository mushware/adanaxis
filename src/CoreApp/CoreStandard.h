#ifndef CORESTANDARD_H
#define CORESTANDARD_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: CoreStandard.h,v 1.18 2002/10/10 13:51:16 southa Exp $
 * $Log: CoreStandard.h,v $
 * Revision 1.18  2002/10/10 13:51:16  southa
 * Speed fixes and various others
 *
 * Revision 1.17  2002/08/27 09:03:24  southa
 * Added stdio.h
 *
 * Revision 1.16  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.15  2002/08/19 11:09:55  southa
 * GameTypeRace rendering
 *
 * Revision 1.14  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.13  2002/07/18 11:43:34  southa
 * Added M_PI
 *
 * Revision 1.12  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 * Revision 1.11  2002/07/07 11:16:07  southa
 * More designer work
 *
 * Revision 1.10  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.9  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.8  2002/06/24 12:12:30  southa
 * Added <math.h>
 *
 * Revision 1.7  2002/06/11 16:23:56  southa
 * New paths to data files
 *
 * Revision 1.6  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.5  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
 * Revision 1.4  2002/05/25 17:17:18  southa
 * CoreXML implementation
 *
 * Revision 1.3  2002/05/24 16:23:08  southa
 * Config and typenames
 *
 * Revision 1.2  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.9  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.8  2002/03/21 22:07:52  southa
 * Initial wrangle application handler
 *
 * Revision 1.7  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.6  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 * Revision 1.5  2002/03/04 22:30:49  southa
 * Interpreter work
 *
 * Revision 1.4  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 * Revision 1.3  2002/02/23 11:43:34  southa
 * Added AutoMonkey
 *
 * Revision 1.2  2002/02/18 22:04:37  southa
 * Initial texture loading
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */


// config.h
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// General purpose includes used by most files 
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>

#ifdef HAVE_SSTREAM
#include <sstream>
#else
#include "sstream"
#endif

#include <vector>
#include <list>
#include <map>
#include <stack>

#include <stdexcept>
#include <ctime>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>

#ifdef HAVE_VALARRAY
#include <valarray>
#define tValarray valarray
#else
// Mimic valarray using vector
#define tValarray vector
#endif

using namespace std;

typedef double tVal;
typedef signed int S32;
typedef unsigned int U32;
typedef unsigned char U8;
typedef unsigned int tSize;

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

#if 0
// This didn't work
typedef std::basic_istream<U8> u8istream;
typedef std::basic_ostream<U8> u8ostream;

typedef std::basic_ifstream<U8> u8ifstream;
typedef std::basic_ofstream<U8> u8ofstream;
#endif

typedef istream u8istream;
typedef ostream u8ostream;
typedef ifstream u8ifstream;
typedef ofstream u8ofstream;

#define Vec vector

#define COREASSERT(exp) assert(exp)

#endif
