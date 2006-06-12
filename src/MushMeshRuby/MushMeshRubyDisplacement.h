//%includeGuardStart {
#ifndef MUSHMESHRUBYDISPLACEMENT_H
#define MUSHMESHRUBYDISPLACEMENT_H
//%includeGuardStart } wA/o7FTWPUZkSPtLetn3sA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyDisplacement.h
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
//%Header } RqIYygnsvbiaEc0+PyskZQ
/*
 * $Id$
 * $Log$
 */

#include "MushMeshRubyStandard.h"

class MushMeshDisplacement;

class MushMeshRubyDisplacement
{
public:
	static Mushware::tRubyValue MushDisplacementAllocate(Mushware::tRubyValue inKlass);
	static void MushDisplacementFree(void *inPtr);			
	static MushMeshDisplacement& RefObj(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue MushDisplacementInitialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue MushDisplacementInitializeCopy(Mushware::tRubyValue inCopy, Mushware::tRubyValue inOrig);
	static Mushware::tRubyValue MushDisplacement_to_s(Mushware::tRubyValue inSelf);
	static void RubyInstall(void);
	
private:
	static Mushware::tRubyValue m_DisplacementKlass;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
