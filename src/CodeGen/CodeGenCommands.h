//%includeGuardStart {
#ifndef CODEGENCOMMANDS_H
#define CODEGENCOMMANDS_H
//%includeGuardStart } FHHGpOF69Q6Xwq1bL4LKmA
//%Header {
/*****************************************************************************
 *
 * File: src/CodeGen/CodeGenCommands.h
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
//%Header } gybFbkxLK6zoA87guYx0pw
/*
 * $Id: CodeGenCommands.h,v 1.3 2006/06/01 15:38:49 southa Exp $
 * $Log: CodeGenCommands.h,v $
 * Revision 1.3  2006/06/01 15:38:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/05/19 13:01:57  southa
 * Mac release work
 *
 * Revision 1.1  2005/04/11 23:31:40  southa
 * Startup and registration screen
 *
 */

#include "mushMushcore.h"

class CodeGenCommands
{
public:
    static void Install(void);
    static MushcoreScalar CodeGenGenerate(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
