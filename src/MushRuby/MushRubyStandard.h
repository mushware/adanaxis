//%includeGuardStart {
#ifndef MUSHRUBYSTANDARD_H
#define MUSHRUBYSTANDARD_H
//%includeGuardStart } nBDoPvfnxLSuYSrB2MSw2A
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyStandard.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Yh+jb7Kt8ubaZEY+Q2v/cg
/*
 * $Id: MushRubyStandard.h,v 1.1 2006/04/20 00:22:45 southa Exp $
 * $Log: MushRubyStandard.h,v $
 * Revision 1.1  2006/04/20 00:22:45  southa
 * Added ruby executive
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#elif defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#else
#include "Mushcore/Mushcore.h"
#endif

namespace Mushware
{
    typedef unsigned long tRubyValue;
    typedef unsigned long tRubyID;
    typedef int tRubyError, tRubyArgC;
    typedef tRubyValue (*tfpRubyMethod)(tRubyArgC inArgC, tRubyValue *inpArgV, tRubyValue inSelf);
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
