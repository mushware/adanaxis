//%includeGuardStart {
#ifndef MUSHPIESTL_H
#define MUSHPIESTL_H
//%includeGuardStart } s1VDDs8uoifg5yG0M4Ld0Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSTL.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 5GZB7i38V1ZXHKD6QTXNHw
/*
 * $Id: MushPieSTL.h,v 1.1 2004/01/02 11:57:47 southa Exp $
 * $Log: MushPieSTL.h,v $
 * Revision 1.1  2004/01/02 11:57:47  southa
 * Created
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/MushcoreSTL.h>
#elif defined(HAVE_MUSHCORE_H)
#include <MushcoreSTL.h>
#else
#include "Mushcore/MushcoreSTL.h"
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
