//%includeGuardStart {
#ifndef TESTMUSHMESHOPS_H
#define TESTMUSHMESHOPS_H
//%includeGuardStart } 4dGfAMR+uoe7iTaqb4c6XQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshOps.h
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
//%Header } pCLp9KFBNhVlD2I0+jgsdA
/*
 * $Id: TestMushMeshOps.h,v 1.4 2006/06/01 15:40:01 southa Exp $
 * $Log: TestMushMeshOps.h,v $
 * Revision 1.4  2006/06/01 15:40:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.2  2004/11/30 00:18:06  southa
 * Additional vector operations
 *
 * Revision 1.1  2004/11/17 23:43:48  southa
 * Added outer product
 *
 */
#include "TestMushMeshStandard.h"

class TestMushMeshOps
{
public:
    static MushcoreScalar TestInnerProduct(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar TestOuterProduct(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar TestNormalise(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar TestSlerp(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
