//%includeGuardStart {
#ifndef TESTMUSHMESHTOOLS_H
#define TESTMUSHMESHTOOLS_H
//%includeGuardStart } Ev4y5T3GaryJ7MTZGbMJQg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshTools.h
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
//%Header } 3pQvo2AiX4YtX88nzu9n3Q
/*
 * $Id: TestMushMeshTools.h,v 1.2 2006/06/09 11:43:04 southa Exp $
 * $Log: TestMushMeshTools.h,v $
 * Revision 1.2  2006/06/09 11:43:04  southa
 * Facet to texture transformation
 *
 * Revision 1.1  2006/06/08 20:17:32  southa
 * Texture tile generation method 2
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshTools
{
public:
    static bool ApproxEquals(Mushware::t4Val inVec1, Mushware::t4Val inVec2);
	static void TestFacetTransform(void);
    static MushcoreScalar TestTools(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
