//%includeGuardStart {
#ifndef TESTMUSHMESH4TEXTURETILE_H
#define TESTMUSHMESH4TEXTURETILE_H
//%includeGuardStart } XeFFQ3aZ3yQxRY9GTyZ4CQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMesh4TextureTile.h
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
//%Header } GRCiCe6JIEbOQW3zsykbew
/*
 * $Id: TestMushMesh4TextureTile.h,v 1.1 2006/05/01 17:39:01 southa Exp $
 * $Log: TestMushMesh4TextureTile.h,v $
 * Revision 1.1  2006/05/01 17:39:01  southa
 * Texture generation
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMesh4TextureTile
{
public:
    static void TransformTest(const MushMesh4TextureTile& inTile,
                              const Mushware::t2Val& inTestVec,
                              const Mushware::t4Val& inExpectedVec);
    static MushcoreScalar Test4TextureTile(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
