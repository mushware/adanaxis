//%includeGuardStart {
#ifndef MUSHGLRUBYSHADER_H
#define MUSHGLRUBYSHADER_H
//%includeGuardStart } WwbZBL15DrZVigx4xjmeCg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLRubyShader.h
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
//%Header } 3bgt6j0Fbg4/0lubu+kJ0Q
/*
 * $Id: MushGLRubyShader.h,v 1.1 2006/09/07 10:02:37 southa Exp $
 * $Log: MushGLRubyShader.h,v $
 * Revision 1.1  2006/09/07 10:02:37  southa
 * Shader interface
 *
 */

#include "MushGLStandard.h"

#include "MushGLShader.h"

#include "API/mushMushRuby.h"

class MushGLRubyShader : public MushRubyDataObj<MushGLShader>
{
public:
    static Mushware::tRubyValue Dump(Mushware::tRubyValue inSelf);

private:
};

MUSHRUBYDATAOBJ_INSTALL(MushGLShader)(void)
{
	DataObjInstall("MushGLShader");
    MushRubyUtil::MethodDefineNoParams(Klass(), "mDump", MushGLRubyShader::Dump);
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
