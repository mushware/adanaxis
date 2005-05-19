//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshUtils.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } WLLwLp1qXNaKU0BYxUpcrg
/*
 * $Id: TestMushMeshUtils.cpp,v 1.5 2004/01/05 20:13:15 southa Exp $
 * $Log: TestMushMeshUtils.cpp,v $
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
