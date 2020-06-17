//%includeGuardStart {
#ifndef TESTMUSHMESHARRAY_H
#define TESTMUSHMESHARRAY_H
//%includeGuardStart } nvK6t6OW0Lv8bF+/agTL8Q
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshArray.h
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
//%Header } ZZD9/CKlLhD04nbBp2Uygg
/*
 * $Id: TestMushMeshArray.h,v 1.8 2006/06/01 15:40:01 southa Exp $
 * $Log: TestMushMeshArray.h,v $
 * Revision 1.8  2006/06/01 15:40:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.6  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.5  2003/10/20 13:02:55  southa
 * Patch fixes and testing
 *
 * Revision 1.4  2003/10/17 19:33:11  southa
 * Mesh patches
 *
 * Revision 1.3  2003/10/15 12:23:10  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.2  2003/10/15 11:54:54  southa
 * MushMeshArray neighbour testing and subdivision
 *
 * Revision 1.1  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshArray
{
public:
    static MushcoreScalar TestArray(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
    enum
    {
        kXMax = 4,
        kYMax = 5
    };

    static void ArrayVerify(const MushMeshArray<Mushware::U32>& inArray, const std::string& inName);
    static Mushware::U32 ValueFunction(Mushware::U32 inX, Mushware::U32 inY);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
