//%includeGuardStart {
#ifndef TESTMUSHMESH4LIBRARY_H
#define TESTMUSHMESH4LIBRARY_H
//%includeGuardStart } 6nGS0bbinuAivBnQPVy7sQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMesh4Library.h
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
//%Header } Qq68e+gS0R+jngy2WjgYVQ
/*
 * $Id: TestMushMesh4Library.h,v 1.2 2006/06/01 15:40:01 southa Exp $
 * $Log: TestMushMesh4Library.h,v $
 * Revision 1.2  2006/06/01 15:40:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/06/30 12:04:56  southa
 * Mesh work
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMesh4Library
{
public:
    static MushcoreScalar Test4Library(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
