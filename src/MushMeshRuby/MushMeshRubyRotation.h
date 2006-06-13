//%includeGuardStart {
#ifndef MUSHMESHRUBYROTATION_H
#define MUSHMESHRUBYROTATION_H
//%includeGuardStart } hXr+yjZg5zElUUq0RZNB4g
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyRotation.h
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
//%Header } NU6ZSof2ssS4JvX3KgPtTw
/*
 * $Id$
 * $Log$
 */


#include "MushMeshRubyStandard.h"

class MushMeshRubyRotation : public MushRubyObj<Mushware::tQValPair>
{
public:
	static void RubyInstall(void);
	
protected:
	static Mushware::tRubyValue Rotate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	
private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
