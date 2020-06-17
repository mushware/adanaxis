//%includeGuardStart {
#ifndef TESTMUSHMESHQUATERNION_H
#define TESTMUSHMESHQUATERNION_H
//%includeGuardStart } QsO6VqLi2p68/1q8tHLJKQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshQuaternion.h
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
//%Header } y2Sh+xkLWdoWWG5jbD1izQ
/*
 * $Id: TestMushMeshQuaternion.h,v 1.5 2006/06/01 15:40:02 southa Exp $
 * $Log: TestMushMeshQuaternion.h,v $
 * Revision 1.5  2006/06/01 15:40:02  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/03 21:03:12  southa
 * Build fixes
 *
 * Revision 1.2  2004/12/12 10:55:37  southa
 * Quaternion conversions
 *
 * Revision 1.1  2004/12/06 20:44:18  southa
 * Quaternion and matrix operations
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshQuaternion
{
public:
    static void PseudoRandomRotationGet(Mushware::t4x4Val& outMatrix, Mushware::tVal inSeed);
    static void PseudoRandomVectorGet(Mushware::t4Val& outVector, Mushware::tVal inSeed);
    static MushcoreScalar TestQuaternion(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
