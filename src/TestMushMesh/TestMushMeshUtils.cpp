//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshUtils.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } EsPff1iypz7kZ/x6IDtmhA
/*
 * $Id: TestMushMeshUtils.cpp,v 1.1 2003/10/15 07:08:29 southa Exp $
 * $Log: TestMushMeshUtils.cpp,v $
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
    MushcoreInterpreter::Sgl().HandlerAdd("testutils", TestUtils);
}
