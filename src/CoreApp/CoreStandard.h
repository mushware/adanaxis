#ifndef CORESTANDARD_H
#define CORESTANDARD_H
/*
 * $Id: CoreStandard.h,v 1.9 2002/05/09 17:10:38 southa Exp $
 * $Log: CoreStandard.h,v $
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

// General purpose includes used by most files 
#include <string>
#include <iostream>
#include <fstream>

#ifdef HAVE_SSTREAM
#include <sstream>
#else
#include "sstream"
#endif

#include <vector>
#include <list>
#include <map>
#include <stdexcept>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

using namespace std;

typedef double Val;
typedef unsigned int U32;
typedef unsigned char U8;
typedef size_t Size;

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