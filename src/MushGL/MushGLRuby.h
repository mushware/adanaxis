//%includeGuardStart {
#ifndef MUSHGLRUBY_H
#define MUSHGLRUBY_H
//%includeGuardStart } f8JH71NND8fMo45CMrGt2Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLRuby.h
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
//%Header } YYOPwACC2o8cADrvWY9O3g
/*
 * $Id: MushGLRuby.h,v 1.1 2006/12/11 13:28:24 southa Exp $
 * $Log: MushGLRuby.h,v $
 * Revision 1.1  2006/12/11 13:28:24  southa
 * Snapshot
 *
 */

#include "MushGLStandard.h"

#include "API/mushMushRuby.h"

class MushGLRuby : public MushRubyEmptyObj<7000>
{
public:
	static void MushGLInstall(void);
    static Mushware::tRubyValue ViewExtent(Mushware::tRubyValue inSelf);
private:
};

MUSHRUBYEMPTYOBJ_INSTALL(7000)(void)
{
	EmptyInstall("MushGL");
	MushGLRuby::MushGLInstall();
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
