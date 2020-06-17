//%includeGuardStart {
#ifndef TESTMUSHMESHBOX_H
#define TESTMUSHMESHBOX_H
//%includeGuardStart } lj50ZsgWJBEaKPiuIrzn0Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshBox.h
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
//%Header } L+T1VBYFLmolh7Gpw7j3sw
/*
 * $Id: TestMushMeshBox.h,v 1.4 2006/06/01 15:40:01 southa Exp $
 * $Log: TestMushMeshBox.h,v $
 * Revision 1.4  2006/06/01 15:40:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.2  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/17 12:27:20  southa
 * Line end fixes and more mesh work
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshBox
{
public:
    static MushcoreScalar TestBox(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
