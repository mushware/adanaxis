//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshUtils.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 6iM0/2RNlKnkj/n1JHnIVQ
/*
 * $Id: TestMushMeshUtils.cpp,v 1.4 2004/01/02 21:13:17 southa Exp $
 * $Log: TestMushMeshUtils.cpp,v $
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
