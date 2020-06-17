//%includeGuardStart {
#ifndef MUSHMESHRUBYDISPLACEMENT_H
#define MUSHMESHRUBYDISPLACEMENT_H
//%includeGuardStart } wA/o7FTWPUZkSPtLetn3sA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyDisplacement.h
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
//%Header } AcHC4Oguc+1/UHNr3mjYfg
/*
 * $Id: MushMeshRubyDisplacement.h,v 1.2 2006/06/13 19:30:37 southa Exp $
 * $Log: MushMeshRubyDisplacement.h,v $
 * Revision 1.2  2006/06/13 19:30:37  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/06/12 16:01:23  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyStandard.h"

class MushMeshDisplacement;

class MushMeshRubyDisplacement : public MushRubyObj<MushMeshDisplacement>
{
public:
	static void RubyInstall(void);	
private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
