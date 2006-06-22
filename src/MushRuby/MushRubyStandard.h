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
 * $Id: MushRubyStandard.h,v 1.6 2006/06/16 12:11:06 southa Exp $
 * $Log: MushRubyStandard.h,v $
 * Revision 1.6  2006/06/16 12:11:06  southa
 * Ruby subclasses
 *
 * Revision 1.5  2006/06/13 10:35:06  southa
 * Ruby data objects
 *
 * Revision 1.4  2006/06/12 16:01:24  southa
 * Ruby mesh generation
 *
 * Revision 1.3  2006/06/12 11:59:40  southa
 * Ruby wrapper for MushMeshVector
 *
 * Revision 1.2  2006/04/21 00:10:43  southa
 * MushGLFont ruby module
 *
 * Revision 1.1  2006/04/20 00:22:45  southa
 * Added ruby executive
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
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
	typedef tRubyValue (*tfpRubyMethodNoParams)(tRubyValue inSelf);
	typedef tRubyValue (*tfpRubyMethodOneParam)(tRubyValue inSelf, tRubyValue inArg1);
	typedef tRubyValue (*tfpRubyMethodTwoParams)(tRubyValue inSelf, tRubyValue inArg1, tRubyValue inArg2);
	typedef tRubyValue (*tfpRubyMethodThreeParams)(tRubyValue inSelf, tRubyValue inArg1, tRubyValue inArg2, tRubyValue inArg3);
	typedef tRubyValue (*tfpRubyMethodFourParams)(tRubyValue inSelf, tRubyValue inArg1, tRubyValue inArg2, tRubyValue inArg3, tRubyValue inArg4);
	typedef tRubyValue (*tfpRubyAllocFunc)(tRubyValue);
	typedef void (*tfpRubyDataFunc)(void *);

    extern const Mushware::tRubyValue kRubyQnil;
	extern const Mushware::tRubyValue kRubyQfalse;
	extern const Mushware::tRubyValue kRubyQtrue;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
