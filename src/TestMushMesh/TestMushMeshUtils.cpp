//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshUtils.cpp
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
//%Header } 7qxAKuAjD8uLd735Cx/ZIg
/*
 * $Id: TestMushMeshUtils.cpp,v 1.7 2006/05/01 17:39:01 southa Exp $
 * $Log: TestMushMeshUtils.cpp,v $
 * Revision 1.7  2006/05/01 17:39:01  southa
 * Texture generation
 *
 * Revision 1.6  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/05 20:13:15  southa
 * Target and test updates
 *
 * Revision 1.4  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.3  2003/10/15 12:23:10  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.2  2003/10/15 11:54:55  southa
 * MushMeshArray neighbour testing and subdivision
 *
 * Revision 1.1  2003/10/15 07:08:29  southa
 * MushMeshArray creation
 *
 */
#include "TestMushMeshUtils.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshUtilsInstaller(TestMushMeshUtils::Install);

bool
TestMushMeshUtils::ApproxEquals(Mushware::t4Val inVec1, Mushware::t4Val inVec2)
{
    bool retVal = true;
    for (U32 i=0; i<4; ++i)
    {
        if (std::fabs(inVec1[i] - inVec2[i]) > 1e-4)
        {
            retVal = false;   
        }
    }
    return retVal;
}

MushcoreScalar
TestMushMeshUtils::TestUtils(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    for (U32 i=1; i<8; ++i)
	{
	    // cout << MushMeshUtils::SubdivisionAlphaGet(i) << " == " << MushMeshUtils::SubdivisionAlphaCalculate(i) << endl;
        if (fabs(MushMeshUtils::SubdivisionAlphaGet(i) - MushMeshUtils::SubdivisionAlphaCalculate(i)) > 1e-4)
        {
            throw MushcoreLogicFail("SubdivisionAlphaGet != SubdivisionAlphaCalculate");
        }
	}
    return MushcoreScalar(0);
}

void
TestMushMeshUtils::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshutils", TestUtils);
}
