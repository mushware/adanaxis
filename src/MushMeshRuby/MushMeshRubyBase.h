//%includeGuardStart {
#ifndef MUSHMESHRUBYBASE_H
#define MUSHMESHRUBYBASE_H
//%includeGuardStart } 9MiiRzYXUcDq4xuXNoK2NQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyBase.h
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
//%Header } o3Kc680++YMhqP+KHzJ7oQ
/*
 * $Id: MushMeshRubyBase.h,v 1.2 2006/07/07 07:57:29 southa Exp $
 * $Log: MushMeshRubyBase.h,v $
 * Revision 1.2  2006/07/07 07:57:29  southa
 * Key translation
 *
 * Revision 1.1  2006/06/16 12:11:04  southa
 * Ruby subclasses
 *
 */

#include "MushMeshRubyStandard.h"

class MushMeshRubyBase : public MushRubyEmptyObj<1000>
{
public:
private:
};

MUSHRUBYEMPTYOBJ_INSTALL(1000)(void)
{
	EmptyInstall("MushBase");
    
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
