//%includeGuardStart {
#ifndef MUSHRUBYINSTALL_H
#define MUSHRUBYINSTALL_H
//%includeGuardStart } 3UeA3jhmLesW/JpzA9vyDA
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyInstall.h
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
//%Header } HKbd8pm7SdfJPUW05HY0Vg
/*
 * $Id: MushRubyInstall.h,v 1.2 2006/06/13 19:30:39 southa Exp $
 * $Log: MushRubyInstall.h,v $
 * Revision 1.2  2006/06/13 19:30:39  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/04/21 00:10:43  southa
 * MushGLFont ruby module
 *
 */

#include "MushRubyStandard.h"

class MushRubyInstall : public MushcoreSingleton<MushRubyInstall>
{
public:
    typedef void (*tpInstallFunction)(void);
    
    void Add(tpInstallFunction inFunction);
    void Execute(void);
private:
    
    std::vector<tpInstallFunction> m_installFunctions;
};

#define MUSHRUBY_INSTALL(a) \
namespace \
{ \
	void Install(void) \
	{ \
		MushRubyInstall::Sgl().Add(a::RubyInstall); \
	} \
	MushcoreInstaller install(Install); \
}


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
