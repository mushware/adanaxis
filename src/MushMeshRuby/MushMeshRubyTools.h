//%includeGuardStart {
#ifndef MUSHMESHRUBYTOOLS_H
#define MUSHMESHRUBYTOOLS_H
//%includeGuardStart } AhDIfg56yXx3qhiZE8dkOA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyTools.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } VmBRSnlsuVcSgRzEFXpyWA
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
