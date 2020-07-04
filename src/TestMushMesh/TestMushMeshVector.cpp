//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshVector.cpp
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
//%Header } nUcjaOPfqyTtKl2Zi0BdAw
/*
 * $Id: TestMushMeshVector.cpp,v 1.10 2006/06/01 15:40:03 southa Exp $
 * $Log: TestMushMeshVector.cpp,v $
 * Revision 1.10  2006/06/01 15:40:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.8  2004/10/31 09:22:51  southa
 * Added MushMeshPreMatrix
 *
 * Revision 1.7  2004/01/05 20:13:15  southa
 * Target and test updates
 *
 * Revision 1.6  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.5  2003/10/17 12:27:20  southa
 * Line end fixes and more mesh work
 *
 * Revision 1.4  2003/10/15 12:23:10  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.3  2003/10/15 11:54:55  southa
 * MushMeshArray neighbour testing and subdivision
 *
 * Revision 1.2  2003/10/15 07:08:30  southa
 * MushMeshArray creation
 *
 */
#include "TestMushMeshVector.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshVectorInstaller(TestMushMeshVector::Install);

MushcoreScalar
TestMushMeshVector::TestVector(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    typedef MushMeshVector<tVal, 2> t2vecVal;
    // Basic operations
    t2vecVal a(1,2);
    t2vecVal b(1,2);

    if (a != b)
    {
        throw(MushcoreLogicFail("operator != failed"));
    }
    b = t2vecVal(2,2);
    if (a == b)
    {
        throw(MushcoreLogicFail("operator == failed"));
    }

    if (a + b != t2vecVal(3,4))
    {
        ostringstream message;
        message << "operator + failed : " << a << " + " << b << " != " << a+b;
        throw(MushcoreLogicFail(message.str()));
    }
    if (a - b != t2vecVal(-1,0))
    {
        throw(MushcoreLogicFail("operator - failed"));
    }
    if (a * b != 6)
    {
        ostringstream message;
        message << "operator * failed : " << a << " * " << b << " != " << a * b;
        throw(MushcoreLogicFail(message.str()));
    }
#if 0
    if (a / b != t2vecVal(0.5,1))
    {
        throw(MushcoreLogicFail("operator / failed"));
    }
#endif
    if (a * 2 != t2vecVal(2,4))
    {
        throw(MushcoreLogicFail("operator * 2 failed"));
    }
    if (a / 2 != t2vecVal(0.5,1))
    {
        throw(MushcoreLogicFail("operator / 2 failed"));
    }
    if (2 * a != t2vecVal(2,4))
    {
        throw(MushcoreLogicFail("operator 2 * failed"));
    }
    return MushcoreScalar(0);
}

void
TestMushMeshVector::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshvector", TestVector);
}
