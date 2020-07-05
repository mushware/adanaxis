//%includeGuardStart {
#ifndef TESTMUSHMESHMATTRESS_H
#define TESTMUSHMESHMATTRESS_H
//%includeGuardStart } zG/ZHIUMoSmbfAAkHrI2OQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshMattress.h
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
//%Header } GV9MUyKGkUZ/sLdOMQAPBg
/*
 * $Id: TestMushMeshMattress.h,v 1.2 2006/06/01 15:40:01 southa Exp $
 * $Log: TestMushMeshMattress.h,v $
 * Revision 1.2  2006/06/01 15:40:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/02 00:42:39  southa
 * Conditioning tweaks
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshMattress
{
public:
    static MushcoreScalar TestMattress(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
