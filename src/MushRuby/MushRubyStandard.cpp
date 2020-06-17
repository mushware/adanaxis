//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyStandard.cpp
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
//%Header } 2uEL50ykqpbnP9QMkwdCxA
/*
 * $Id: MushRubyStandard.cpp,v 1.4 2006/06/16 12:11:05 southa Exp $
 * $Log: MushRubyStandard.cpp,v $
 * Revision 1.4  2006/06/16 12:11:05  southa
 * Ruby subclasses
 *
 * Revision 1.3  2006/06/13 10:35:06  southa
 * Ruby data objects
 *
 * Revision 1.2  2006/04/21 00:10:43  southa
 * MushGLFont ruby module
 *
 */

#include "MushRubyStandard.h"

#include "MushRubyRuby.h"

namespace Mushware
{
	const Mushware::tRubyValue kRubyQnil = Qnil;
	const Mushware::tRubyValue kRubyQfalse = Qfalse;
	const Mushware::tRubyValue kRubyQtrue = Qtrue;	
}
