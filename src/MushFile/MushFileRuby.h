//%includeGuardStart {
#ifndef MUSHFILERUBY_H
#define MUSHFILERUBY_H
//%includeGuardStart } maVG7GUsiEQQ3pwEUeL/Pg
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileRuby.h
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
//%Header } lSV+hOgNSN/wJXQt7yP9Xw
/*
 * $Id: MushFileRuby.h,v 1.2 2006/11/07 11:08:54 southa Exp $
 * $Log: MushFileRuby.h,v $
 * Revision 1.2  2006/11/07 11:08:54  southa
 * Texture loading from mushfiles
 *
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#include "MushFileStandard.h"

#include "API/mushMushRuby.h"

class MushFileRuby : public MushRubyEmptyObj<6000>
{
public:
	static void MushFileInstall(void);
	
	static Mushware::tRubyValue LibraryAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);    
	static Mushware::tRubyValue LibraryDump(Mushware::tRubyValue inSelf);    
	static Mushware::tRubyValue File(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);    
private:
};

MUSHRUBYEMPTYOBJ_INSTALL(6000)(void)
{
	EmptyInstall("MushFile");
	MushFileRuby::MushFileInstall();
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
