//%includeGuardStart {
#ifndef MUSHMESHRUBYROTATION_H
#define MUSHMESHRUBYROTATION_H
//%includeGuardStart } hXr+yjZg5zElUUq0RZNB4g
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyRotation.h
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
//%Header } tdkVOv+Eg9z3+jBFRuB5fw
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
