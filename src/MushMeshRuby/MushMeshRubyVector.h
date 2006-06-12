//%includeGuardStart {
#ifndef MUSHMESHRUBYVECTOR_H
#define MUSHMESHRUBYVECTOR_H
//%includeGuardStart } 0FzW4T4aHQE6CM7CVY2jXA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyVector.h
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
//%Header } 2J8UOQdZFzDY6iljFrjmCg
/*
 * $Id$
 * $Log$
 */

#include "MushMeshRubyStandard.h"

class MushMeshRubyVector
{
public:
	static Mushware::tRubyValue Mush4ValAllocate(Mushware::tRubyValue inKlass);
	static void Mush4ValFree(void *inPtr);			
	static Mushware::t4Val& Reft4Val(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue Mush4ValInitialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue Mush4ValInitializeCopy(Mushware::tRubyValue inCopy, Mushware::tRubyValue inOrig);
	static Mushware::tRubyValue Mush4Val_to_s(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue Mush4ValInPlaceAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
	static Mushware::tRubyValue Mush4ValAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
	static Mushware::tRubyValue Mush4ValIsEqual(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
	static void RubyInstall(void);
	
private:
	static Mushware::tRubyValue m_t4ValKlass;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
