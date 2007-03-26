//%includeGuardStart {
#ifndef MUSHMESHRUBYTOOLS_H
#define MUSHMESHRUBYTOOLS_H
//%includeGuardStart } AhDIfg56yXx3qhiZE8dkOA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyTools.h
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
//%Header } bes5fnAf1xT1KrYurE5FtA
/*
 * $Id: MushMeshRubyTools.h,v 1.4 2006/08/20 14:19:22 southa Exp $
 * $Log: MushMeshRubyTools.h,v $
 * Revision 1.4  2006/08/20 14:19:22  southa
 * Seek operation
 *
 * Revision 1.3  2006/07/18 16:58:38  southa
 * Texture fixes
 *
 * Revision 1.2  2006/07/17 14:43:42  southa
 * Billboarded deco objects
 *
 * Revision 1.1  2006/06/13 19:30:38  southa
 * Ruby mesh generation
 *
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
	static Mushware::tRubyValue RandomOrientation(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue RandomUnitVector(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue RandomAngularVelocity(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue RandomSeedSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue SeekRotation(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue TurnToFace(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
                                           Mushware::tRubyValue inArg1, Mushware::tRubyValue inArg2);
    static Mushware::tRubyValue Slerp(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
                                      Mushware::tRubyValue inArg1, Mushware::tRubyValue inArg2);
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
