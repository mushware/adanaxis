//%includeGuardStart {
#ifndef MEDIASTL_H
#define MEDIASTL_H
//%includeGuardStart } 49s9eOqW2RTUoIsat9M5Ew
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaSTL.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } +Td/2IvsgUkwjOVIGbU3xg
/*
 * $Id: MediaSTL.h,v 1.3 2003/09/17 19:40:34 southa Exp $
 * $Log: MediaSTL.h,v $
 * Revision 1.3  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:02  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/13 15:01:19  southa
 * Fix Mustl command line build
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORESTL_H)
#include <Mushcore/MushcoreSTL.h>
#else
#if defined(HAVE_MUSHCORESTL_H)
#include <MushcoreSTL.h>
#else
#include "MushcoreSTL.h"
#endif
#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
