#ifndef MUSTLSTANDARD_H
#define MUSTLSTANDARD_H
/*
 * $Id: MustlStandard.h,v 1.1 2002/12/12 18:38:25 southa Exp $
 * $Log: MustlStandard.h,v $
 * Revision 1.1  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 */

#include <iosfwd>
#include <map>
#include <string>
#include <vector>
#include <memory>

namespace Mustl
{
    typedef int tSocket;
    typedef float tVal;
    typedef double tLongVal;
    typedef signed int S32;
    typedef unsigned int U32;
    typedef signed short S16;
    typedef unsigned short U16;
    typedef signed char S8;
    typedef unsigned char U8;
    typedef double tMsec;
};

#endif
