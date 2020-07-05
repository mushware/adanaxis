//%includeGuardStart {
#ifndef TESTMUSTLPOSTHANDLER_H
#define TESTMUSTLPOSTHANDLER_H
//%includeGuardStart } SJgpGuH7CQ341wYrg3Yerw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlPostHandler.h
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
//%Header } 452fd1wkz+b8xr2xo0R2wQ
/*
 * $Id: TestMustlPostHandler.h,v 1.7 2006/06/01 15:40:06 southa Exp $
 * $Log: TestMustlPostHandler.h,v $
 * Revision 1.7  2006/06/01 15:40:06  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:25  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:18  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:39  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/17 13:30:42  southa
 * Source conditioning and build fixes
 *
 * Revision 1.1  2003/01/14 20:46:12  southa
 * Post data handling
 *
 */

#include "TestMustlStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

class TestMustlPostHandler
{
public:
    static void Install(void);
    static MushcoreScalar PostHandler(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
