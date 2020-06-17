//%includeGuardStart {
#ifndef MUSHMESHRUBYBASEPRISM_H
#define MUSHMESHRUBYBASEPRISM_H
//%includeGuardStart } GPdAkxs6oYpQ2BPyQpi3kA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyBasePrism.h
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
//%Header } 1th1r/RRsKZRmicJdu/lHA
/*
 * $Id: MushMeshRubyBasePrism.h,v 1.1 2006/06/16 01:02:33 southa Exp $
 * $Log: MushMeshRubyBasePrism.h,v $
 * Revision 1.1  2006/06/16 01:02:33  southa
 * Ruby mesh generation
 *
 */


#include "MushMeshRubyStandard.h"

class MushMeshRubyBasePrism : public MushRubyObj<MushMeshLibraryPrism>
{
public:
	static void RubyInstall(void);
	
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
