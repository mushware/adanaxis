//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshTools.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } Z5M+0kNmdF0ldv1BT2B0fQ
/*
 * $Id$
 * $Log$
 */

#include "TestMushMeshTools.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshToolsInstaller(TestMushMeshTools::Install);

bool
TestMushMeshTools::ApproxEquals(Mushware::t4Val inVec1, Mushware::t4Val inVec2)
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
TestMushMeshTools::TestTools(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
	const tVal limit=0.001;
	
    for (U32 i=0; i<100; ++i)
    {
		const t4Val initialVec1 = MushMeshTools::RandomVector(1, 10);

		tQValPair rotation1 = MushMeshTools::QuaternionRotateToXAxis(initialVec1);
		
		t4Val resultVec = rotation1.RotatedVector(initialVec1);
		
		if (std::fabs(resultVec.X()) < 1 ||
			std::fabs(resultVec.Y()) > limit ||
			std::fabs(resultVec.Z()) > limit ||
			std::fabs(resultVec.W()) > limit)
		{
			std::ostringstream message;
			message << "RotateToXAxis failed: input=" << initialVec1 << ", output=" << resultVec;
			throw MushcoreCommandFail(message.str());
		}
		
		t4Val initialVec2;
		
		// Find a non-colinear vector
		do
		{
			initialVec2 = MushMeshTools::RandomVector(1, 10);
		} while (initialVec1 * initialVec2 < 0.1);
		
	    t4Val otherVec = rotation1.RotatedVector(initialVec2);
		
		tQValPair rotation2 = MushMeshTools::QuaternionRotateToXYPlane(otherVec);
		
		resultVec = rotation2.RotatedVector(otherVec);
		
		if (std::fabs(resultVec.X()) + std::fabs(resultVec.Y()) < 1 ||
			std::fabs(resultVec.Z()) > limit ||
			std::fabs(resultVec.W()) > limit)
		{
			std::ostringstream message;
			message << "RotateToXYPlane failed: input=" << initialVec2 << ", output=" << resultVec;
			throw MushcoreCommandFail(message.str());
		}
	
		tQValPair finalR;
		
		if (i % 2 == 0)
		{
			finalR = rotation1;
			finalR.OuterMultiplyBy(rotation2);
		}
		else
		{
			finalR = MushMeshTools::QuaternionRotateVectorPairToXYPlane(initialVec1, initialVec2);
		}
		
		t4Val finalVec1 = finalR.RotatedVector(initialVec1);
		t4Val finalVec2 = finalR.RotatedVector(initialVec2);
		
		if (std::fabs(finalVec1.X()) < 1 ||
			std::fabs(finalVec1.Y()) > limit ||
			std::fabs(finalVec1.Z()) > limit ||
			std::fabs(finalVec1.W()) > limit)
		{
			std::ostringstream message;
			message << "RotateToPlane failed in x: input=" << initialVec1 << ", output=" << finalVec1;
			throw MushcoreCommandFail(message.str());
		}

		if (std::fabs(finalVec2.X()) + std::fabs(finalVec2.Y()) < 1 ||
			std::fabs(finalVec2.Z()) > limit ||
			std::fabs(finalVec2.W()) > limit)
		{
			std::ostringstream message;
			message << "RotateToPlane failed in xy: input=" << initialVec2 << ", output=" << finalVec2;
			throw MushcoreCommandFail(message.str());
		}
		
		for (U32 j=0; j<10; ++j)
		{
		    t4Val anotherVec = MushMeshTools::Random(-10,10) * initialVec1 +
				MushMeshTools::Random(-10,10) * initialVec2;
			
			t4Val finalAnotherVec = finalR.RotatedVector(anotherVec);

			if (std::fabs(finalAnotherVec.X()) + std::fabs(finalAnotherVec.Y()) < 1 ||
				std::fabs(finalAnotherVec.Z()) > limit ||
				std::fabs(finalAnotherVec.W()) > limit)
			{
				std::ostringstream message;
				message << "RotateToPlane failed for combination: input=" << anotherVec << ", output=" << finalAnotherVec;
				throw MushcoreCommandFail(message.str());
			}
		}
    }
	
    return MushcoreScalar(0);
}

void
TestMushMeshTools::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshtools", TestTools);
}
