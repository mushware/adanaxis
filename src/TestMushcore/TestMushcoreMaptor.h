//%includeGuardStart {
#ifndef TESTMUSHCOREMAPTOR_H
#define TESTMUSHCOREMAPTOR_H
//%includeGuardStart } HdWYC6EkuyTHKwHsOLsIGQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreMaptor.h
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
//%Header } qd3I+zAUeZixcRDwmPxSiA
/*
 * $Id: TestMushcoreMaptor.h,v 1.2 2006/06/01 15:40:04 southa Exp $
 * $Log: TestMushcoreMaptor.h,v $
 * Revision 1.2  2006/06/01 15:40:04  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/29 11:53:41  southa
 * MushcoreMaptor created
 *
 */

#include "TestMushcoreStandard.h"

class TestMushcoreMaptor
{
public:
    static MushcoreScalar TestMaptor(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
