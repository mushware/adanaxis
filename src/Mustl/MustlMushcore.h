//%includeGuardStart {
#ifndef MUSTLMUSHCORE_H
#define MUSTLMUSHCORE_H
//%includeGuardStart } h+gqfDecxXjckM8W23Hqdg
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlMushcore.h
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } byYmC5TkB+uUNKE664Jzlw
/*
 * $Id: MustlMushcore.h,v 1.2 2003/08/21 23:09:28 southa Exp $
 * $Log: MustlMushcore.h,v $
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
#include "Mushcore.h"
#endif
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
