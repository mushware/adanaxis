//%includeGuardStart {
#ifndef MUSHMESHRUBYPOST_H
#define MUSHMESHRUBYPOST_H
//%includeGuardStart } LENY2n19YIp+tUhqba3KBg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyPost.h
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
//%Header } CZu+CbK/tJNlMUx3J13yoA
/*
 * $Id: MushMeshRubyPost.h,v 1.1 2006/06/20 19:06:53 southa Exp $
 * $Log: MushMeshRubyPost.h,v $
 * Revision 1.1  2006/06/20 19:06:53  southa
 * Object creation
 *
 */

#include "MushMeshRubyStandard.h"

class MushMeshRubyPost : public MushRubyObj<MushMeshPosticity>
{
public:
	static void RubyInstall(void);
	
protected:
	static Mushware::tRubyValue position(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue velocity(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue angular_position(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue angular_velocity(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue position_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);	
	static Mushware::tRubyValue velocity_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);	
	static Mushware::tRubyValue angular_position_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);	
	static Mushware::tRubyValue angular_velocity_equal(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);	
private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
