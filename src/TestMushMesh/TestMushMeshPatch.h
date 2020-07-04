//%includeGuardStart {
#ifndef TESTMUSHMESHPATCH_H
#define TESTMUSHMESHPATCH_H
//%includeGuardStart } BFG5WurStwvR3cwySRKGUQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshPatch.h
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
//%Header } pyenMyk/mpGcZhBAxgU3lg
/*
 * $Id: TestMushMeshPatch.h,v 1.5 2006/06/01 15:40:02 southa Exp $
 * $Log: TestMushMeshPatch.h,v $
 * Revision 1.5  2006/06/01 15:40:02  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/26 10:05:30  southa
 * End patch testing
 *
 * Revision 1.1  2003/10/20 13:05:57  southa
 * Created
 *
 */


#include "TestMushMeshStandard.h"

class TestMushMeshPatch
{
public:
    static MushcoreScalar TestPatch(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
    enum
    {
        kXMax = 6,
        kYMax = 7
    };

    static void GeometryPrint(const Mushware::tGeometryArray& inArray);

    static bool ChangeVerify(const Mushware::tGeometryArray& inArray1,
                             const Mushware::tGeometryArray& inArray2,
                             Mushware::U32 inChanges);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
