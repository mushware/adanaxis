//%includeGuardStart {
#ifndef MUSTLMUSHCORE_H
#define MUSTLMUSHCORE_H
//%includeGuardStart } h+gqfDecxXjckM8W23Hqdg
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlMushcore.h
 *
 * Copyright Andy Southgate 2002-2004
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ld8VV7Ng9KnwdTTs5rn86A
/*
 * $Id: MustlMushcore.h,v 1.4 2004/01/02 21:13:15 southa Exp $
 * $Log: MustlMushcore.h,v $
 * Revision 1.4  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.3  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:28  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/13 15:01:20  southa
 * Fix Mustl command line build
 *
 */

#include "MustlStandard.h"

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#else
#include "Mushcore/Mushcore.h"
#endif
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
