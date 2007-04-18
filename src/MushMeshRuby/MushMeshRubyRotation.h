//%includeGuardStart {
#ifndef MUSHMESHRUBYROTATION_H
#define MUSHMESHRUBYROTATION_H
//%includeGuardStart } hXr+yjZg5zElUUq0RZNB4g
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyRotation.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } glN7eBVRDsJxwZNS52M+MA
/*
 * $Id: MushMeshRubyRotation.h,v 1.3 2006/08/20 14:19:22 southa Exp $
 * $Log: MushMeshRubyRotation.h,v $
 * Revision 1.3  2006/08/20 14:19:22  southa
 * Seek operation
 *
 * Revision 1.2  2006/06/20 19:06:54  southa
 * Object creation
 *
 * Revision 1.1  2006/06/13 19:30:38  southa
 * Ruby mesh generation
 *
 */


#include "MushMeshRubyStandard.h"

class MushMeshRubyRotation : public MushRubyObj<Mushware::tQValPair>
{
public:
	static void RubyInstall(void);
	
protected:
	static Mushware::tRubyValue Rotate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue Inverse(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue IsEqual(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue Normalise(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue Scale(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue Scaled(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
