//%includeGuardStart {
#ifndef MUSHMESHRUBYTOOLS_H
#define MUSHMESHRUBYTOOLS_H
//%includeGuardStart } AhDIfg56yXx3qhiZE8dkOA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyTools.h
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
//%Header } bXehXXY7VVdSW1knmNpOqw
/*
 * $Id$
 * $Log$
 */

#include "MushMeshRubyStandard.h"

class MushMeshRubyTools : public MushRubyObj<MushMeshTools>
{
public:
	static void RubyInstall(void);
	
protected:
	static Mushware::tRubyValue RotationInAxis(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
											   Mushware::tRubyValue inArg1);
	static Mushware::tRubyValue RotationInXYPlane(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue RotationInZWPlane(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue RotationInXZPlane(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue RotationInYWPlane(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue RotationInXWPlane(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue RotationInYZPlane(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);

private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
