//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshBox.cpp
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
//%Header } WYKHYge9jSr6aKWP3HX35A
/*
 * $Id: TestMushMeshBox.cpp,v 1.6 2006/05/01 17:39:01 southa Exp $
 * $Log: TestMushMeshBox.cpp,v $
 * Revision 1.6  2006/05/01 17:39:01  southa
 * Texture generation
 *
 * Revision 1.5  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/05 20:13:15  southa
 * Target and test updates
 *
 * Revision 1.3  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/17 19:33:11  southa
 * Mesh patches
 *
 * Revision 1.1  2003/10/17 12:27:20  southa
 * Line end fixes and more mesh work
 *
 */

#include "TestMushMeshBox.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshBoxInstaller(TestMushMeshBox::Install);

MushcoreScalar
TestMushMeshBox::TestBox(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    typedef MushMeshBox<U32> tTestBox;
    typedef t2U32 tPoint;

    tTestBox testBox(4,5,2,8);

    if (testBox.RegularIs())
    {
        ostringstream message;
        message << "RegularIs failed: " << testBox << " not regular";
        throw(MushcoreLogicFail(message.str()));
    }

    testBox.RegularMake();

    if (testBox != tTestBox(2,5,4,8))
    {
        ostringstream message;
        message << "RegularMake failed: " << testBox << " != " << tTestBox(2,5,4,8);
        throw(MushcoreLogicFail(message.str()));
    }

    if (!testBox.RegularIs())
    {
        ostringstream message;
        message << "RegularIs failed: " << testBox << " is regular";
        throw(MushcoreLogicFail(message.str()));
    }

    testBox = tTestBox(4,3,2,1);
    testBox.RegularMake();

    if (testBox != tTestBox(2,1,4,3))
    {
        ostringstream message;
        message << "RegularMake failed: " << testBox << " != " << tTestBox(2,1,4,3);
        throw(MushcoreLogicFail(message.str()));
    }

    testBox.StartSet(tPoint(testBox.Start().Y(), testBox.Start().X()));
    if (testBox != tTestBox(1,2,4,3))
    {
        ostringstream message;
        message << "StartSet/Get failed: " << testBox << " != " << tTestBox(1,2,4,3);
        throw(MushcoreLogicFail(message.str()));
    }

    if (testBox.SizeGet() != tPoint(3, 1))
    {
        ostringstream message;
        message << "SizeGet failed: " << testBox.SizeGet() << " != " << tPoint(3, 1);
        throw(MushcoreLogicFail(message.str()));
    }
    

    testBox.EndSet(tPoint(testBox.End().Y(), testBox.End().X()));
    if (testBox != tTestBox(1,2,3,4))
    {
        ostringstream message;
        message << "EndSet/Get failed: " << testBox << " != " << tTestBox(1,2,3,4);
        throw(MushcoreLogicFail(message.str()));
    }

    return MushcoreScalar(0);
}

void
TestMushMeshBox::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshbox", TestBox);
}
