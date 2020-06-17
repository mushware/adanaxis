//%includeGuardStart {
#ifndef TESTMUSHPIEPIECES_H
#define TESTMUSHPIEPIECES_H
//%includeGuardStart } m33WbJWvRZbCH8H/4tVjHg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushPie/TestMushPiePieces.h
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
//%Header } pXGBArRNprdIr4aDq1L2nQ
/*
 * $Id: TestMushPiePieces.h,v 1.3 2006/06/01 15:40:03 southa Exp $
 * $Log: TestMushPiePieces.h,v $
 * Revision 1.3  2006/06/01 15:40:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.1  2004/01/06 00:34:57  southa
 * MushPie testing
 *
 */

#include "TestMushPieStandard.h"

class TestMushPiePieces
{
public:
    static MushPiePosicity TestPosMake(Mushware::tVal inKey);
    static MushcoreScalar TestPieces(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
