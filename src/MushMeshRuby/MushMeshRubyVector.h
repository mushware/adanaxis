//%includeGuardStart {
#ifndef MUSHMESHRUBYVECTOR_H
#define MUSHMESHRUBYVECTOR_H
//%includeGuardStart } 0FzW4T4aHQE6CM7CVY2jXA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyVector.h
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
//%Header } oUHPpX14uzVX0VIOk8uDOA
/*
 * $Id: MushMeshRubyVector.h,v 1.9 2006/11/01 10:07:13 southa Exp $
 * $Log: MushMeshRubyVector.h,v $
 * Revision 1.9  2006/11/01 10:07:13  southa
 * Shield handling
 *
 * Revision 1.8  2006/09/30 13:46:33  southa
 * Seek and patrol
 *
 * Revision 1.7  2006/09/29 10:47:57  southa
 * Object AI
 *
 * Revision 1.6  2006/07/17 14:43:42  southa
 * Billboarded deco objects
 *
 * Revision 1.5  2006/06/14 18:45:50  southa
 * Ruby mesh generation
 *
 * Revision 1.4  2006/06/13 19:30:38  southa
 * Ruby mesh generation
 *
 * Revision 1.3  2006/06/13 10:35:04  southa
 * Ruby data objects
 *
 * Revision 1.2  2006/06/12 16:01:24  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/06/12 11:59:39  southa
 * Ruby wrapper for MushMeshVector
 *
 */

#include "MushMeshRubyStandard.h"

class MushMeshRubyVector : public MushRubyObj<Mushware::t4Val>
{
public:
	static void RubyInstall(void);
	
private:
    static Mushware::tRubyValue X(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue XEquals(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue Y(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue YEquals(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue Z(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue ZEquals(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue W(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue WEquals(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
    
	static Mushware::tRubyValue MushVectorInPlaceAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
	static Mushware::tRubyValue MushVectorAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
	static Mushware::tRubyValue MushVectorInPlaceSubtract(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
	static Mushware::tRubyValue MushVectorSubtract(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
	static Mushware::tRubyValue MushVectorInPlaceMultiply(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
	static Mushware::tRubyValue MushVectorMultiply(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
	static Mushware::tRubyValue MushVectorIsEqual(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
	static Mushware::tRubyValue ApproxEqual(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1);
	static Mushware::tRubyValue Magnitude(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue MagnitudeSquared(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue InnerProduct(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg1);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
